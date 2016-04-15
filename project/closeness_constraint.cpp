#include <csc486a/closeness_constraint.hpp>
#include <utility>


namespace csc486a {
    
    
    closeness_constraint::closeness_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh::Vertex v, float w) : vertex_constraint_base(mesh,std::move(v),w) {   }
    
    
    closeness_constraint::points_type closeness_constraint::project (points_type ps) const {
        
        ps.clear();
        ps.push_back(vpoints_[v_]*w_);
        
        return ps;
        
    }
    
    
}
