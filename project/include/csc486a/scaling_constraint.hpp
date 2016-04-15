/**
 *  \file
 */


#pragma once


#include <csc486a/vertex_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {
    
    
    /**
     *  A constraint which pulls vertices to a position which
     *  is their current position multiplied by some scalar.
     */
    class scaling_constraint : public vertex_constraint_base {
        
        
        private:
        
        
            float s_;
        
        
        public:
        
        
            /**
             *  Creates a scaling_constraint.
             *
             *  \param [in] mesh
             *      The mesh upon which this constraint shall
             *      operate.  Must remain valid for the lifetime
             *      of the object or the behaviour is undefined.
             *  \param [in] v
             *      The vertex which this constraint shall scale.
             *      Must be from \em mesh or the behaviour is
             *      undefined.
             *  \param [in] s
             *      The scalar by which this constraint shall scale
             *      the position of \em v on each iteration.
             *  \param [in] w
             *      The strictly positive weight of this constraint.
             */
            scaling_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh::Vertex v, float s, float w);
        
        
            virtual points_type project (points_type ps=points_type{}) const override;
        
        
    };
    
    
}
