# Specify project and identify languages used.
project(assignment1 LANGUAGES CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)

# Find OpenGL GLUT library
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(CGAL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${CGAL_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

# Execute project.
add_executable(a1 assignment1_ZhenmaiHu.cpp)

# Link project with libraries.
target_link_libraries(a1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CGAL_LIBRARY} ${GMP_LIBRARIES})
