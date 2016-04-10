get_filename_component(EXERCISENAME ${CMAKE_CURRENT_LIST_DIR} NAME)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SHADERS "*.glsl")
file(GLOB_RECURSE SHADERS "*.hpp")

add_executable(${EXERCISENAME} ${SOURCES} ${HEADERS} ${SHADERS})
target_link_libraries(${EXERCISENAME} ${LIBRARIES})
include_directories(internal)
include_directories(include)

#--- Deploy data files
file(COPY ${PROJECT_SOURCE_DIR}/data/quad1.obj DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/data/quad2.obj DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/data/quad3.obj DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
