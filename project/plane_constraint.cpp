#include <csc486a/plane_constraint.hpp>


namespace csc486a {
    
    
    plane_constraint::plane_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w) : line_plane_constraint_base(mesh,std::move(vs),w,type::plane) {    }
    
    
}
