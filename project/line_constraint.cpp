#include <csc486a/line_constraint.hpp>
#include <utility>


namespace csc486a {
    
    
    line_constraint::line_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w) : line_plane_constraint_base(mesh,std::move(vs),w,type::line) {   }
    
    
}
