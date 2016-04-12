/**
 *  \file
 */


#pragma once


#include <csc486a/line_plane_constraint_base.hpp>


namespace csc486a {
    
    
    class plane_constraint : public line_plane_constraint_base {
        
        
        public:
        
        
            plane_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w);
        
        
    };
    
    
}
