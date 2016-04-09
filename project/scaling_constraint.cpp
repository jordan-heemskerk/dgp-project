#include <csc486a/scaling_constraint.hpp>


namespace csc486a {
    
    
    scaling_constraint::scaling_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh::Vertex v, float s, float w) : vertex_constraint_base(mesh,std::move(v),w), s_(s) { }
    
    
    scaling_constraint::points_type scaling_constraint::project (points_type ps) const {
        
        ps.clear();
        ps.push_back(vpoints_[v_]*s_*w_);
        
        return ps;
        
    }
    
    
}
