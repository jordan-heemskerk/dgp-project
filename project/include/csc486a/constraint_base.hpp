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
        
        
            /**
             *  The weight of the constraint.
             */
            float w_;
        
        
            /**
             *  Creates a new constraint_base.
             *
             *  \param [in] mesh
             *      The mesh upon which the derived class shall
             *      operate.  Must remain valid for the lifetime
             *      of this object or the behaviour is undefined.
             *  \param [in] w
             *      The strictly positive weight of the constraint.
             */
            constraint_base (const OpenGP::SurfaceMesh & mesh, float w);
        
        
        
    };
    
    
}
