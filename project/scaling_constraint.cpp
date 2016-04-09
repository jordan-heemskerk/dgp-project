#include <csc486a/scaling_constraint.hpp>


namespace csc486a {
    
    
    scaling_constraint::scaling_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float s, float w) : constraint_base(mesh,std::move(vs),w), s_(s) { }
    
    
    scaling_constraint::points_type scaling_constraint::project (points_type ps) const {
        
        //  Make sure buffer is empty
        ps.clear();
        
        for (auto && v : vs_) {
            
            auto npos=vpoints_[v];
            npos*=s_;
            npos*=w_;
            ps.push_back(npos);
            
        }
        
        return ps;
        
    }
    
    
}
