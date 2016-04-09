/**
 *  \file
 */


#pragma once


#include <csc486a/constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {
    
    
    class vertices_constraint_base : public constraint_base {
        
        
        protected:
        
        
            std::vector<OpenGP::SurfaceMesh::Vertex> vs_;
        
        
            vertices_constraint_base (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w);
        
        
            virtual triplets_type add (triplets_type ts=triplets_type{}) const override;
        
        
    };
    
    
}
