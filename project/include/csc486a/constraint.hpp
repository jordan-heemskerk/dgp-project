/**
 *  \file
 */


#pragma once


#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <vector>


namespace csc486a {
    
    
    /**
     *  A base class which represents a Shape
     *  Op constraint.
     */
    class constraint {
        
        
        public:
        
        
            /**
             *  The type of triplets which shall be used
             *  when adding a constraint to the matrix
             *  Q.
             */
            using triplet_type=Eigen::Triplet<float>;
            /**
             *  The type of a collection of triplets which
             *  shall be returned when adding a constraint
             *  to the matrix Q.
             */
            using triplets_type=std::vector<triplet_type>;
            /**
             *  The type of a point.
             */
            using point_type=Eigen::Vector3f;
            /**
             *  A collection of points.
             */
            using points_type=std::vector<point_type>;
        
        
            constraint () = default;
            constraint (const constraint &) = delete;
            constraint (constraint &&) = delete;
            constraint & operator = (const constraint &) = delete;
            constraint & operator = (constraint &&) = delete;
        
        
            /**
             *  Allows derived classes to be cleaned up
             *  through pointer or reference to base.
             */
            virtual ~constraint () noexcept;
        
        
            /**
             *  Obtains the information necessary to add
             *  the constraint to the solver's Q matrix.
             *
             *  \param [in] ts
             *      A vector whose allocated space may optionally
             *      be used to hold the returned triplets.  This
             *      vector should be empty.
             *
             *  \return
             *      A vector of triplets.  The first and
             *      second members of the triplet represent
             *      the location of the third member inside
             *      a sparse matrix.  The row should be zero
             *      relative and will be offset as necessary
             *      by the solver to insert the values into
             *      unique rows.  The columns should be equal
             *      to the number of the vertex-in-question.
             */
            virtual triplets_type add (triplets_type ts=triplets_type{}) const = 0;
            /**
             *  Obtains the projections of the points upon which
             *  the constraint operates.
             *
             *  Used to generate the matrix p in the solver.
             *
             *  \param [in] ps
             *      A vector whose allocated space may optionally
             *      be used to hold the returned points.  This vector
             *      should be empty.
             *
             *  \return
             *      A vector of points.  The projected points should
             *      be in the same order as the vertices from which
             *      they have been projected.
             */
            virtual points_type project (points_type ps=points_type{}) const = 0;
        
        
    };
    
    
}
