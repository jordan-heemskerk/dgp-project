/**
 *  \file
 */


#pragma once


#include <csc486a/constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>


namespace csc486a {
    
    
    /**
     *  A convenience base class for constraints which applies
     *  to only a single vertex.
     */
    class vertex_constraint_base : public constraint_base {
        
        
        protected:
        
        
            /**
             *  The vertex upon which the constraint operates.
             */
            OpenGP::SurfaceMesh::Vertex v_;
        
        
            /**
             *  Creates a new vertex_constraint_base.
             *
             *  \param [in] mesh
             *      The mesh upon which the constraint shall
             *      operate.  Must remain valid for the lifetime
             *      of the newly created object or the behaviour
             *      is undefined.
             *  \param [in] v
             *      The vertex upon which the constraint shall
             *      operate.  If this vertex is not from \em mesh
             *      the behaviour is undefined.
             *  \param [in] w
             *      The strictly positive weight of the constraint.
             */
            vertex_constraint_base (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh::Vertex v, float w);
            
            
        public:
        
        
            virtual triplets_type add (triplets_type ts=triplets_type{}) const override;
        
        
    };
    
    
}
