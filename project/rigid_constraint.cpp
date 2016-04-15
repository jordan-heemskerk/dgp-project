#include <csc486a/rigid_constraint.hpp>
#include <utility>


namespace csc486a {
    
    
    rigid_constraint::rigid_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh original, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w) : rigid_similarity_constraint_base(mesh, std::move(original), std::move(vs), w,type::rigid, 0.0f) { }
    
    
}
