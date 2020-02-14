// File   : mesh.h
// Author : Jarrett McCarty

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include <iostream>

class Mesh
{
public:
    Mesh();
    Mesh(int, int);
    void set_hms(int);
    void set_ms(int);
    void generate_triangle_mesh(std::vector<GLfloat>);
    void generate_triangle_normals();
    void vertex_array();
private:
    std::vector<glm::vec3> triangle_normals;
    std::vector<GLfloat> mesh, normals;
    int hms_, ms_;
};


#endif

