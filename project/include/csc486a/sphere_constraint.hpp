/**
 *  \file
 */


#pragma once


#include <csc486a/circle_sphere_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {


    /**
     *  A Shape Op constraint which pulls vertices to their
     *  best fitting sphere.
     */
    class sphere_constraint : public circle_sphere_constraint_base {
        

        public:


            /**
             *  Creates a new sphere_constraint.
             *
             *  \param [in] mesh
             *      The mesh upon which the constraint shall
             *      operate.  Must remain valid for the lifetime
             *      of the newly created object or the behaviour
             *      is undefined.
             *  \param [in] vs
             *      A collection of vertices upon which the constraint
             *      shall operate.  All contained vertices must be from
             *      \em mesh or the behaviour is undefined.
             *  \param [in] w
             *      The strictly positive weight of the constraint.
             */
            sphere_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w);
            

        points_type project(points_type ps) const;

    };
    

}

