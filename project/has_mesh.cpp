#include <csc486a/has_mesh.hpp>
#include <stdexcept>


namespace csc486a {
    
    
    has_vertices::has_vertices (const OpenGP::SurfaceMesh & mesh) : vpoints_(mesh.get_vertex_property<constraint::point_type>("v:point")) {
        
        if (!vpoints_) throw std::logic_error("Mesh does not have \"v:point\" property");
        
    }
    
    
}
