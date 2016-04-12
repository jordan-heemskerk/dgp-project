#include <csc486a/circle_constraint.hpp>


namespace csc486a {

    circle_constraint::circle_constraint (const OpenGP::SurfaceMesh & mesh, std::vector<OpenGP::SurfaceMesh::Vertex> vs, float w) : circle_sphere_constraint_base(mesh, std::move(vs), w, type::circle) { }



}
