/**
* \file
*/


#pragma once


#include <csc486a/rigid_similarity_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {


    /**
     *  A Shape Op constraint which applies a rigid constraint
     *  but the transformation the vertices may undergo is
     *  conformal rather than isometric.
     *
     *  \sa csc486a::rigid_constraint
     */
    class similarity_constraint : public rigid_similarity_constraint_base {
        
            
        public:
        
            
            /**
             *  Creates a new similarity_constraint.
             *
             *  \param [in] mesh
             *      The mesh upon which the constraint shall
             *      operate.  Must remain valid for the lifetime
             *      of the newly created object or the behaviour
             *      is undefined.
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
             *  \param [in] clamp
             *      Limits the scaling which the vertices of \em vs may
             *      undergo to \em 1±clamp.  Defaults to 0.7.
             */
            similarity_constraint (const OpenGP::SurfaceMesh & mesh, OpenGP::SurfaceMesh original, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w, float clamp=0.7f);
            
            
    };
    
    
    
}
