#include <csc486a/rigid_constraint.hpp>


namespace csc486a {
    
    rigid_constraint::rigid_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh deformed, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w) : rigid_similarity_constraint_base(mesh, deformed, std::move(vs), w,type::rigid, 0.0f) { }
    
    
}
