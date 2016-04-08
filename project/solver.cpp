#include <csc486a/solver.hpp>
#include <Eigen/Dense>
#include <cstddef>
#include <stdexcept>
#include <utility>


namespace csc486a {
    
    
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
        ps_=row;
        
        sparse_type q(row,n);
        q.setFromTriplets(ts.begin(),ts.end());
        
        q_.emplace(q);
        if (q_->info()!=Eigen::Success) throw std::runtime_error("Failed to create Cholesky factorization");
        
    }
    
    
    solver::solver (OpenGP::SurfaceMesh & mesh) : mesh_(mesh), vpoints_(mesh_.vertex_property<constraint::point_type>("v:point")) {    }
    
    
    void solver::add (const constraint & c) {
        
        if (q_) throw std::logic_error("Cannot add constraints after solver has run");
        
        cs_.push_back(&c);
        
    }
    
    
    void solver::operator () () {
        
        if (!q_) create_q();
        
        //  First get the projections by performing
        //  the local solves
        Eigen::MatrixX3f p(ps_,3);
        std::size_t num(0);
        for (auto && ptr : cs_) {
            
            b_.clear();
            b_=ptr->project(std::move(b_));
            
            for (auto && p : b_) {
                
                if (num==ps_) throw std::logic_error("Too many projections");
                
                p(num,0)=p(0);
                p(num,1)=p(1);
                p(num++,2)=p(2);
                
            }
            
        }
        if (num<ps_) throw std::logic_error("Insufficient projections");
        
        //  Perform the global solve
        Eigen::MatrixX3f v(q_->solve(p));
        if (v.rows()!=mesh_.n_vertices()) throw std::logic_error("Wrong number of entries in matrix V");
        std::size_t row(0);
        for (auto && vec : mesh_.vertices()) {
            
            Eigen::Vector3f npos(v(row,0),v(row,1),v(row,2));
            ++row;
            vpoints_[vec]=npos;
            
        }
        
    }
    
    
}
