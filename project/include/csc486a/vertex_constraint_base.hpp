/**
 *  \file
 */


#pragma once


#include <csc486a/constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>


namespace csc486a {
    
    
    class vertex_constraint_base : public constraint_base {
        
        
        protected:
        
        
            OpenGP::SurfaceMesh::Vertex v_;
        
        
            vertex_constraint_base (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh::Vertex v, float w);
        
        
            virtual triplets_type add (triplets_type ts=triplets_type{}) const override;
        
        
    };
    
    
}
