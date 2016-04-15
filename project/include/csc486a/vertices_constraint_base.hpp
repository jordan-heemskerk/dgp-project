/**
 *  \file
 */


#pragma once


#include <csc486a/constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {
    
    
    /**
     *  A convenience base class for constraints which
     *  operate on multiple vertices.
     */
    class vertices_constraint_base : public constraint_base {
        
        
        protected:
        
        
            /**
             *  The vertices upon which the constraint operates.
             */
            std::vector<OpenGP::SurfaceMesh::Vertex> vs_;
        
        
            /**
             *  Creates a new vertices_constraint_base.
             *
             *  \param [in] mesh
             *      The mesh upon which the constraint shall
             *      operate.  Must remain valid for the lifetime
             *      of the object or the behaviour is undefined.
             *  \param [in] vs
             *      A collection of vertices upon which the constraint
             *      shall operate.  All vertices must be from \em mesh
             *      or the behaviour is undefined.
             *  \param [in] w
             *      The strictly positive weight of the constraint.
             */
            vertices_constraint_base (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w);
            
            
        public:
        
        
            virtual triplets_type add (triplets_type ts=triplets_type{}) const override;
        
        
    };
    
    
}
