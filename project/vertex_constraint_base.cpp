#include <csc486a/vertex_constraint_base.hpp>
#include <utility>


namespace csc486a {
    
    
    vertex_constraint_base::vertex_constraint_base (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh::Vertex v, float w) : constraint_base(mesh,w), v_(std::move(v)) { }
    
    
        vertex_constraint_base::triplets_type vertex_constraint_base::add (triplets_type ts) const {
        
            ts.clear();
            ts.emplace_back(0,v_.idx(),w_);
            
            return ts;
            
        }
    
    
}
