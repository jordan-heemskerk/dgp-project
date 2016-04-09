/**
 *  \file
 */


#pragma once


#include <csc486a/constraint.hpp>
#include <csc486a/has_mesh.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>


namespace csc486a {
    
    
    /**
     *  A convenience base class for Shape Op
     *  constraints which holds a reference to the
     *  mesh, the "v:points" property, and a
     *  weight.
     */
    class constraint_base : public constraint, protected has_mesh<true,true> {
        
        
        protected:
        
        
            float w_;
        
        
            constraint_base (const OpenGP::SurfaceMesh & mesh, float w);
        
        
        
    };
    
    
}
