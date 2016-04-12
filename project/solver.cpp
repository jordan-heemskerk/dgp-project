#include <csc486a/solver.hpp>
#include <Eigen/Dense>
#include <algorithm>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>


namespace csc486a {
    
    
    static const std::string & message (Eigen::ComputationInfo i) {
        
        switch (i) {
            
            case Eigen::Success:{
                static const std::string retr;
                return retr;
            }
            case Eigen::NumericalIssue:{
                static const std::string retr("The provided data did not satisfy the prerequisites");
                return retr;
            }
            case Eigen::NoConvergence:{
                static const std::string retr("Iterative procedure did not converge");
                return retr;
            }
            case Eigen::InvalidInput:{
                static const std::string retr("The inputs are invalid, or the algorithm has been improperly called");
                return retr;
            }
            default:{
                static const std::string retr("Unknown");
                return retr;
            }
            
        }
        
    }
    
    
    void solver::create_q () {
        
        constraint::triplets_type buffer;
        constraint::triplets_type ts;
        std::size_t row=0;
        std::size_t n(mesh_.n_vertices());
        for (auto && ptr : cs_) {
            
            buffer.clear();
            buffer=ptr->add(std::move(buffer));
            
            std::size_t max(0);
            for (auto && t : buffer) {
                
                std::size_t curr(t.row());
                if (curr>max) max=curr;
                
                std::size_t c(t.col());
                if ((c>=n) || (c<0)) throw std::logic_error("Vertex ID out of bounds");
                
                ts.emplace_back(t.row()+row,t.col(),t.value());
                
            }
            row+=max;
            ++row;
            
        }
        
        q_.emplace(row,n);
        q_->setFromTriplets(ts.begin(),ts.end());
        
        auto t=(q_->transpose()**q_).eval();
        solver_.emplace(std::move(t));
        auto info=solver_->info();
        if (info==Eigen::Success) return;
        
        std::ostringstream ss;
        ss << "Failed to create Cholesky factorization: " << message(info);
        throw std::runtime_error(ss.str());
        
    }
    
    
    solver::solver (OpenGP::SurfaceMesh & mesh) : has_mesh<>(mesh) {    }
    
    
    void solver::add (const constraint & c) {
        
        q_=std::nullopt;
        
        cs_.push_back(&c);
        
    }
    
    
    void solver::remove (const constraint & c) noexcept {
        
        auto end=cs_.end();
        auto iter=std::find(cs_.begin(),end,&c);
        if (iter!=end) cs_.erase(iter);
        
    }
    
    
    void solver::operator () () {
        
        if (!q_) create_q();
        
        //  First get the projections by performing
        //  the local solves
        std::size_t ps(q_->rows());
        Eigen::MatrixX3f p(ps,3);
        std::size_t num(0);
        for (auto && ptr : cs_) {
            
            b_.clear();
            b_=ptr->project(std::move(b_));
            
            for (auto && point : b_) {
                
                if (num==ps) throw std::logic_error("Too many projections");
                
                p(num,0)=point(0);
                p(num,1)=point(1);
                p(num++,2)=point(2);
                
            }
            
        }
        if (num<ps) throw std::logic_error("Insufficient projections");
        
        //  Perform the global solve
        Eigen::MatrixX3f v(solver_->solve(q_->transpose()*p));
        auto info=solver_->info();
        if (info!=Eigen::Success) {
            
            std::ostringstream ss;
            ss << "Cholesky solve failed: " << message(info);
            throw std::runtime_error(ss.str());
            
        }
        if (v.rows()!=mesh_.n_vertices()) throw std::logic_error("Wrong number of entries in matrix V");
        std::size_t row(0);
        for (auto && vec : mesh_.vertices()) {
            
            Eigen::Vector3f npos(v(row,0),v(row,1),v(row,2));
            ++row;
            vpoints_[vec]=npos;
            
        }
        
    }
    
    
}
