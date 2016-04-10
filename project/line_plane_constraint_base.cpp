#include <csc486a/line_plane_constraint_base.hpp>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <cstddef>
#include <utility>


namespace csc486a {
    
    
    line_plane_constraint_base::line_plane_constraint_base (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, type t) : vertices_constraint_base(mesh,std::move(vs),w), t_(t) {    }
    
    
    line_plane_constraint_base::points_type line_plane_constraint_base::project (points_type ps) const {
        
        //  Just in case
        ps.clear();
        
        auto h=vs_.size();
        Eigen::Matrix3Xf obs(3,h);
        std::size_t row(0);
        for (auto && v : vs_) obs.col(row++)=vpoints_[v];
        
        auto c=(obs.colwise()-obs.rowwise().mean()).eval();
        
        Eigen::JacobiSVD<Eigen::Matrix3Xf> jsvd(c,Eigen::ComputeFullU);
        auto u=jsvd.matrixU().eval();
        c=u.transpose()*c;
        auto z=Eigen::Matrix<float,1,Eigen::Dynamic>::Constant(c.cols(),0.0f);
        if (t_==type::line) c.row(1)=z;
        c.row(2)=z;
        
        auto result=(u*c).eval();
        std::size_t num(vs_.size());
        for (std::size_t i=0;i<num;++i) ps.emplace_back(c.col(i)*w_);
        
        return ps;
        
    }
    
    
}
