/**
 *  \file
 */


#pragma once


#include <csc486a/constraint.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {
    
    
    /**
     *  A convenience base class for Shape Op
     *  constraints which implements common
     *  operations.
     */
    class constraint_base : public constraint {
        
        
        protected:
        
        
            const OpenGP::SurfaceMesh & mesh_;
            std::vector<OpenGP::SurfaceMesh::Vertex> vs_;
            float w_;
            OpenGP::SurfaceMesh::Vertex_property<point_type> vpoints_;
        
        
        public:
        
        
            constraint_base () = delete;
        
        
            /**
             *  Creates a constraint_base.
             *
             *  \param [in] mesh
             *      A reference to the mesh on which the
             *      constraint shall operate.  The reference
             *      must remain valid for the duration of this
             *      object's lifetime or the behaviour is
             *      undefined.
             *  \param [in] vs
             *      A vector of vertices upon which the constraint
             *      operates.  Must have at least one entry.
             *  \param [in] w
             *      The weight of this constraint.  Must be positive.
             */
            constraint_base (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w);
        
        
            virtual triplets_type add (triplets_type ts=triplets_type{}) const override;
        
        
    };
    
    
}
