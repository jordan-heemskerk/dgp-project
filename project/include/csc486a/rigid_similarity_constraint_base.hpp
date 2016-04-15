/**
* \file
*/

#pragma once

#include <csc486a/vertices_constraint_base.hpp>
#include <Eigen/Dense>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {
    
    
    /**
     *  A base class which encapsulates the common logic of
     *  rigid and similarity constraints.
     */
    class rigid_similarity_constraint_base : public vertices_constraint_base {
        
        
        protected:
            
            
            /**
             *  An enumeration of the various constraints
             *  which this class may represent.
             */
            enum class type {
                
                rigid,  /**<    A rigid constraint  */
                similarity  /**<    A similarity constraint */
                
            };
            
            
        private:
            
            
            type t_;
            OpenGP::SurfaceMesh deformed_;
            OpenGP::SurfaceMesh original_;
            float clamp_;
            
            
        protected:
        
            
            /**
             *  Creates a new rigid_similarity_constraint_base.
             *
             *  \param [in] mesh
             *      The mesh upon which the constraint shall operate.
             *      Must remain valid for the lifetime of the object
             *      or the behaviour is undefined.
             *  \param [in] original
             *      A copy of \em mesh prior to any deformation.
             *      If this mesh was not originally created from the
             *      same mesh as \em mesh the behaviour is undefined.
             *      If any vertices have been added to or removed from
             *      either this copy or \em mesh since they were created
             *      from their common ancestor the behaviour is undefined.
             *  \param [in] vs
             *      The collection of vertices upon which to
             *      operate.  Must be from either \em mesh or
             *      \em original or the behaviour is undefined.
             *  \param [in] w
             *      The strictly positive weight of the constraint.
             *  \param [in] t
             *      The type of constraint which this object shall represent.
             *  \param [in] clamp
             *      Limits the scaling which the vertices in \em vs are permitted
             *      to undergo to \em 1±clamp.
             */
            rigid_similarity_constraint_base (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh original, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, type t, float clamp);
        
            
        public:
        
            
            virtual points_type project (points_type ps=points_type{}) const override;
            
        
    };
    
    
}
