/**
* \file
*/


#pragma once


#include <csc486a/rigid_similarity_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {

    class rigid_constraint : public rigid_similarity_constraint_base {
    
        
        public:
        
        
            rigid_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh original, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w);
            
        
    };    
    
    
}
