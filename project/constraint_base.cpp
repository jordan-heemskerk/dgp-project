#include <csc486a/constraint_base.hpp>
#include <stdexcept>


namespace csc486a {
    
    
    constraint_base::constraint_base (const OpenGP::SurfaceMesh & mesh, float w) : has_mesh<true,true>(mesh), w_(w) {
        
        if (w_<=0.0f) throw std::logic_error("Weight is not strictly positive");
        
    }
    
    
}
