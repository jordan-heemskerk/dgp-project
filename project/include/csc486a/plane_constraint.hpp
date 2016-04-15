/**
 *  \file
 */


#pragma once


#include <csc486a/line_plane_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {
    
    
    /**
     *  Represents a Shape Op constraint which pulls all
     *  associated points to the plane of best fit.
     */
    class plane_constraint : public line_plane_constraint_base {
        
        
        public:
        
        
            /**
             *  Creates a new plane_constraint.
             *
             *  \param [in] mesh
             *      The mesh upon which the constraint shall operate.
             *      Must remain valid for the lifetime of the object or
             *      the behaviour is undefined.
             *  \param [in] vs
             *      A collection of vertices upon which the constraint shall
             *      operate.  All contained vertices must be from \em mesh or
             *      the behaviour is undefined.
             *  \param [in] w
             *      The strictly positive weight of the constraint.
             */
            plane_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w);
        
        
    };
    
    
}
