#================================
# DGP Project Config.
#================================
# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.0)

# Guess project name from folder name (!wipes CMAKE_MODULE_PATH)
get_filename_component(PROJECTNAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJECTNAME})

# Directory of cmake config files
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "-fsanitize=float-divide-by-zero")
#================================
# Find required packages.
#================================
set(CMAKE_FIND_QUIETLY TRUE)
include(cmake/ConfigureEigen.cmake)
include(cmake/ConfigureGLEW.cmake)
include(cmake/ConfigureOpenGL.cmake)
include(cmake/ConfigureGLFW3.cmake)
include(cmake/ConfigureOpenGP.cmake)
include(cmake/ConfigureCompiler.cmake)

#================================
# Subdirectories.
#================================
add_subdirectory(data)
#add_subdirectory(lab01_eigen)
#add_subdirectory(lab01_triangle)
#add_subdirectory(lab02_reconstruction)
#add_subdirectory(lab03_curvature)
#add_subdirectory(lab04_decimation)
#add_subdirectory(lab05_smoothing)
#add_subdirectory(lab06_remeshing)
#add_subdirectory(lab07_deformation)

add_subdirectory(project)
add_subdirectory(rigid_similarity_prototype)
add_subdirectory(circle_sphere_prototype)

