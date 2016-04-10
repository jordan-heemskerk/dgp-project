#include <csc486a/similarity_constraint.hpp>

namespace csc486a {
    
    similarity_constraint::similarity_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh deformed, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, float clamp) : rigid_similarity_constraint_base(mesh, deformed, std::move(vs), w,type::rigid, clamp) { }
    
    
}