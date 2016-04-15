#include <csc486a/similarity_constraint.hpp>
#include <utility>

namespace csc486a {
    
    similarity_constraint::similarity_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh original, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, float clamp) : rigid_similarity_constraint_base(mesh, std::move(original), std::move(vs), w,type::rigid, clamp) { }
    
    
}