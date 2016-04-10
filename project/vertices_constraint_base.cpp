#include <csc486a/vertices_constraint_base.hpp>
#include <cstddef>
#include <stdexcept>


namespace csc486a {
    
    
    vertices_constraint_base::vertices_constraint_base (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w) : constraint_base(mesh,w), vs_(std::move(vs)) {
        
        if (vs_.empty()) throw std::logic_error("Expected at least one vertex");
        
    }
    
    
    vertices_constraint_base::triplets_type vertices_constraint_base::add (triplets_type ts) const {
        
        //  Don't assume the provided vector is empty
        //  even though it should be
        ts.clear();
        
        auto vss=vs_.size();
        ts.reserve(vss*vss);
        float v=1.0f/float(vss);
        v*=w_;
        for (std::size_t i=0;i<vss;++i) for (std::size_t j=0;j<vss;++j) {
            
            ts.emplace_back(i,vs_[j].idx(),((i==j) ? w_ : 0.0f)-v);
            
        }
        
        return ts;
        
    }
    
    
}
