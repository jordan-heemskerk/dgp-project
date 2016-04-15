/**
 *  \file
 */


#pragma once


#include <csc486a/circle_sphere_constraint_base.hpp>
#include <OpenGP/SurfaceMesh/SurfaceMesh.h>
#include <vector>


namespace csc486a {


    /**
     *  Represents a Shape Op constraint which projects
     *  points onto the plane of best fit, and then projects
     *  them onto the circle of best fit which lies in that
     *  plane.
     */
    class circle_constraint : public circle_sphere_constraint_base {


        public:


            /**
             *  Creates a new circle_constraint.
             *
             *  \param [in] mesh
             *      The mesh upon which the constraint shall
             *      operate.  Must remain valid for the lifetime
             *      of the newly created object or the behaviour
             *      is undefined.
             *  \param [in] vs
             *      A collection of vertices from \em mesh upon
             *      which this constraint shall operate.  If all
             *      vertices in \em vs are not from \em mesh the
             *      behaviour is undefined.
             *  \param [in] w
             *      The weight of this constraint.  Must be strictly
             *      positive.
             */
            circle_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w);

        points_type project(points_type ps) const;
    };


}
