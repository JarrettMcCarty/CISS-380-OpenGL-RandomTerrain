// File   : mesh.cpp
// Author : Jarrett McCarty

#include "mesh.h"

Mesh::Mesh()
    : hms_(0), ms_(0)
{}

Mesh::Mesh(int height_map_size, int mesh_size)
    : hms_(height_map_size), ms_(mesh_size)
{}

void Mesh::set_hms(int hms) { hms_ = hms; }
void Mesh::set_ms(int ms) { ms_ = ms; }

void Mesh::generate_triangle_mesh(std::vector<GLfloat> height_map_info)
{
    
    float side_num = hms_;
    
    GLfloat xspot = -1;
    GLfloat zspot = -1;
    GLfloat squaresize = (float)ms_ / side_num; 
    
    for (int z = 0; z != side_num; z++)
    {
        for (int x = 0; x != side_num; x++)
        {
            float myarray [] = { xspot, 0.0f, zspot };
            mesh.insert(mesh.end(), myarray, myarray+3);
            float myarray2 []  = { xspot, 0.0f, zspot + squaresize };
            mesh.insert(mesh.end(), myarray2, myarray2+3);
            mesh.insert(mesh.end(), { xspot + squaresize, 0.0f, zspot });
            
            xspot += squaresize;
        }
        xspot = -1;
        for (int x = 0; x != side_num; x++)
        {
            mesh.insert(mesh.end(), { xspot + squaresize, 0.0f, zspot + squaresize });
            mesh.insert(mesh.end(), { xspot + squaresize, 0.0f, zspot });
            mesh.insert(mesh.end(), { xspot, 0.0f, zspot + squaresize });
            
            xspot += squaresize;
        }
        xspot = -1;
        zspot += squaresize;
    }
    
    for (int i = 1; i < mesh.size(); i += 3)
    {
        mesh[i] = height_map_info[(mesh[i - 1] + 1) / squaresize + (side_num + 1)*(mesh[i + 1] + 1) / squaresize];
    }
    
    mesh = height_map_info;
}

void Mesh::generate_triangle_normals()
{
    for (int i = 0; i < mesh.size(); i += 9)
    {
        glm::vec3 first(mesh[i + 3] - mesh[i],
                        mesh[i + 4] - mesh[i + 1],
                        mesh[i + 5] - mesh[i + 2]);
        glm::vec3 second(mesh[i + 6] - mesh[i],
                         mesh[i + 7] - mesh[i + 1],
                         mesh[i + 8] - mesh[i + 2]);
        
        glm::vec3 normal = glm::cross(first, second);//first.cross(second);
        normal = glm::normalize(normal);
        
        triangle_normals.push_back(normal);
        triangle_normals.push_back(normal);
        triangle_normals.push_back(normal);
    }
    
    normals.resize(mesh.size());
    
    for (int i = 0; i < triangle_normals.size(); ++i)
    {
        normals[i * 3] = triangle_normals[i].x;
        normals[i * 3 + 1] = triangle_normals[i].y;
        normals[i * 3 + 2] = triangle_normals[i].z;
    }
}

void Mesh::vertex_array()
{
 
    glEnableClientState(GL_VERTEX_ARRAY);
    //glVertexPointer(3, GL_FLOAT, 0, &Triangle[0]);
    glEnableClientState(GL_NORMAL_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &mesh[0]);
    glNormalPointer(GL_FLOAT, 0, &normals[0]);
    //glColorPointer(3, GL_FLOAT, 0, vertices_colors + 2); // note offset
    ///glColor3f(0.9,0.9,0.9);
    //std::cout << "here\n";
    glColor3f(.5,.5,.5);
    glScalef(20,20,20);
    
    glDrawArrays(GL_TRIANGLES, 0, mesh.size()/3);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);
    //glFlush();
    //glutSwapBuffers();
}

//mesh.size()6*sizeof(GLfloat)
