#include <csc486a/closeness_constraint.hpp>
#include <utility>


namespace csc486a {
    
    
    closeness_constraint::closeness_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh::Vertex v, float w) : has_mesh<true,true>(mesh), v_(std::move(v)), p_(vpoints_[v_]*w), w_(w) {    }
    
    
    closeness_constraint::triplets_type closeness_constraint::add (triplets_type ts) const {
        
        ts.clear();
        ts.emplace_back(0,v_.idx(),w_);
        
        return ts;
        
    }
    
    
    closeness_constraint::points_type closeness_constraint::project (points_type ps) const {
        
        ps.clear();
        ps.push_back(p_);
        
        return ps;
        
    }
    
    
}
