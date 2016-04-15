/**
* \file
*/


#pragma once


#include <csc486a/rigid_similarity_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {

    class similarity_constraint : public rigid_similarity_constraint_base {
        
            
        public:
        
            
            similarity_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh original, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, float clamp=0.7f);
            
            
    };
    
    
    
}
