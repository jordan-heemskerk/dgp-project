/**
 *  \file
 */


#pragma once


#include <csc486a/vertices_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {
    
    
    /**
     *  A base class which encapsulates the shared logic
     *  of plane and line constraints.
     */
    class line_plane_constraint_base : public vertices_constraint_base {
        
        
        protected:
        
        
            /**
             *  An enumeration of the types of constraints
             *  this base class supports.
             */
            enum class type {
                
                line,   /**<    Pulls points to the best fitting line   */
                plane   /**<    Pulls points to the best fitting plane  */
                
            };
        
        
        private:
        
        
            type t_;
        
        
        protected:
        
        
            /**
             *  Creates a new line_plane_constraint_base.
             *
             *  \param [in] mesh
             *      A reference to the mesh upon which to operate.
             *      Must remain valid for the lifetime of the object
             *      or the behaviour is undefined.
             *  \param [in] vs
             *      A collection of vertices upon which to operate.
             *      All contained vertices must be from \em mesh or
             *      the behaviour is undefined.
             *  \param [in] w
             *      The strictly positive weight of this constraint.
             *  \param [in] t
             *      The type of constraint this object shall represent.
             */
            line_plane_constraint_base (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, type t);
        
        
        public:
        
        
            virtual points_type project (points_type ps=points_type{}) const override;
        
        
    };
    
    
}

