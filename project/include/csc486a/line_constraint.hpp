/**
 *  \file
 */


#pragma once


#include <csc486a/line_plane_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {
    
    
    /**
     *  A constraint which pulls the vertices with which
     *  it is associated to the line of best fit.
     */
    class line_constraint : public line_plane_constraint_base {
        
        
        public:
        
        
            /**
             *  Creates a new line_constraint.
             *
             *  \param [in] mesh
             *      A reference to the mesh upon which to
             *      operate.  Must remain valid for the lifetime
             *      of the object or the behaviour is undefined.
             *  \param [in] vs
             *      A collection of vertices upon which the
             *      constraint shall operate.  All contained vertices
             *      must be in \em mesh or the behaviour is undefined.
             *  \param [in] w
             *      The strictly positive weight of this constraint.
             */
            line_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w);
        
        
    };
    
    
}
