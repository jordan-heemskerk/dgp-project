/**
 *  \file
 */


#pragma once


#include <csc486a/vertex_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>


namespace csc486a {
    
    
    /**
     *  A constraint which requires that vertices do not
     *  move from their current position.
     */
    class closeness_constraint : public vertex_constraint_base {
        
        
        public:
        
        
            /**
             *  Creates a new closeness_constraint.
             *
             *  \param [in] mesh
             *      The mesh upon which this constraint shall operate.
             *      Must remain valid for the lifetime of this object
             *      or the behaviour is undefined.
             *  \param [in] v
             *      The vertex which this constraint shall cause to
             *      resist movement.  Must be a vertex from \em mesh
             *      or the behaviour is undefined.
             *  \param [in] w
             *      The strictly positive weight of this constraint.
             */
            closeness_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh::Vertex v, float w);
        
        
            virtual points_type project (points_type ps=points_type{}) const override;
        
        
    };
    
    
}
