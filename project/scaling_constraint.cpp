#include <csc486a/scaling_constraint.hpp>
#include <stdexcept>
#include <vector>


namespace csc486a {
    
    
    static std::vector<OpenGP::SurfaceMesh::Vertex> vertices (const OpenGP::SurfaceMesh & mesh) {
        
        std::vector<OpenGP::SurfaceMesh::Vertex> vs;
        vs.reserve(mesh.n_vertices());
        
        for (auto && v : mesh.vertices()) vs.push_back(v);
        
        return vs;
        
    }
    
    
    scaling_constraint::scaling_constraint (const OpenGP::SurfaceMesh & mesh, float s) : constraint_base(mesh,vertices(mesh),1.0f), s_(s), vpoints_(mesh.get_vertex_property<point_type>("v:point")) {
        
        if (!vpoints_) throw std::logic_error("Mesh does not have \"v:point\" property");
        
    }
    
    
    scaling_constraint::points_type scaling_constraint::project (points_type ps) const {
        
        //  Make sure buffer is empty
        ps.clear();
        
        for (auto && v : vs_) {
            
            auto npos=vpoints_[v];
            npos*=s_;
            npos*=w_;
            ps.push_back(npos);
            
        }
        
        return ps;
        
    }
    
    
}
