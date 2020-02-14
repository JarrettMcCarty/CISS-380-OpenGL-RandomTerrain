// File   : main.cpp
// Author : Jarrett McCarty

#include <iostream>
#include "myglm.h"
#include "View.h"
#include "gl3d.h"
#include "Material.h"
#include "Light.h"
#include "SingletonView.h"
#include <list>
#include <cmath>
#include "mesh.h"
#include "heightmap.h"
#include <stdlib.h>
#include <cstdlib>


float left;
float right;
float top;
float bottom;
bool wireframe = false;

mygllib::Light light;


#define RANDOM (10-20*((double)rand()/RAND_MAX))
float max(int l, int r) { return (r > l ? r : l); }
float min(int l, int r) { return (r < l ? r : l); }

int random_size()
{
    int r = rand() % 6 + 1;
    return (pow(2, r) + 1);
}
int s = random_size();
const int width=64;//128;
const int height=64;//128;//64, 32
const int featuresize=10; //10

double values[width*height];
std::vector<GLfloat> heightdata;

double get(int x, int y)
{
    return values[(x & (width - 1)) + (y & (height - 1))*width];
}

void set(int x, int y, double value)
{
    values[(x & (width - 1)) + (y & (height - 1)) * width] = value;
}

void square_step(int x, int y, int size, double value)
{
    int hs = size / 2;

    // a     b
    //
    //    x
    //
    // c     d

    double a = get(x - hs, y - hs);
    double b = get(x + hs, y - hs);
    double c = get(x - hs, y + hs);
    double d = get(x + hs, y + hs);

    set(x, y, ((a + b + c + d) / 4.0) + value);

}

void diamond_step(int x, int y, int size, double value)
{
    int hs = size / 2;

    //   c
    //
    //a  x  b
    //
    //   d

    double a = get(x - hs, y);
    double b = get(x + hs, y);
    double c = get(x, y - hs);
    double d = get(x, y + hs);

    set(x, y, ((a + b + c + d) / 4.0) + value);
}
void diamond_square(int stepsize, double scale)
{

    int halfstep= stepsize / 2;



    for (int i = halfstep; i < height + halfstep; i += stepsize)
    {
        for (int j = halfstep; j < width + halfstep; j += stepsize)
        {
            square_step(j, i, stepsize, RANDOM * scale);
        }
    }

    for (int i = 0; i < height; i += stepsize)
    {
        for (int j = 0; j < width; j += stepsize)
        {
            diamond_step(j + halfstep, i, stepsize, RANDOM * scale);
            diamond_step(j, i + halfstep, stepsize, RANDOM * scale);

        }
    }

}

void init()
{
    //heightMap.print();
    //const double t = glutGet(GLUT_ELAPSED_TIME) ;
    srand(time(NULL));


    for(int i = 0; i < height; i += featuresize)
    {
        for (int j = 0; j < width; j += featuresize)
        {
            set(j, i, RANDOM);
        }
    }
    int samplesize = featuresize;
    
    double scale = 1.2;
    
    while (samplesize > 1)
    {
        
        diamond_square(samplesize, scale);
        
        samplesize /= 2;
        scale /= 2.0;
    }


    left = -1;
    right = 1;
    bottom = -1;
    top = 1;

    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    view.eye(10.0f, 25.0f, 10.0f);
    view.ref(0.0f, 0.0f, 0.0f);
  
    view.zNear() = 1;
    view.zFar() = 1000;
    view.set_projection();
    view.lookat();

    glViewport(0, 0, 700, 700);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);
    //mygllib::Material mat(mygllib::Material::BRASS);
    //mat.set();

    light.set();
    mygllib::Light::all_on();
    light.on(); 

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glFrontFace(GL_CCW);
    mygllib::Light::all_off();
    mygllib::draw_xz_plane();
    mygllib::draw_axes();
    mygllib::Light::all_on();

    
    //glTranslatef(-15, 0, -15);
    glTranslatef(25, 0, 25);
    glRotatef(90, 1, 0, 0);
    glScalef(-1.0, -1.0, -1.0);
    //glColor3f(0,0,0);
    double H = 0.0;
    double h = 0.0;
    for(int i = 0; i < height*width; ++i)
    {
        //std::cout << values[i] << '\n';
        H = max(values[i], H);
        h = min(values[i], h);
    }
    std::cout << "max: " << H << ", min: " << h <<'\n';
    glm::vec3 colors(0.9, 0.9, 0.9);
    //glm::vec3 colors2(0.3,0.59,0.11);
    float c = 0.5;
    float m = 0;
    for(int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (wireframe) { glBegin(GL_LINE_LOOP); }
            else { glBegin(GL_TRIANGLES); }
            m = ((y - h)/(H - h));
            m = 0 + (m-h)*(1-0)/(H-h);//(1 + m / (1 + abs(m)) * 0.5) << '\n';
            //std::cout << m << '\n';
            glm::vec3 tem = colors * m;
            //std::cout << tem << '\n';
            glColor3f(tem.x, tem.y, tem.z);//finalc, finalc, finalc);
            glVertex3f(x,y,get(x,y));
            
            m = ((y - h)/(H - h));
            m = 0 + (m-h)*(1-0)/(H-h);
            tem = colors * m;
            //std::cout << tem << '\n';
            glColor3f(tem.x, tem.y, tem.z);
            glVertex3f(x+1,y,get(x+1,y));
            
            m = (((y + 1) - h)/(H - h));
            m = 0 + (m-h)*(1-0)/(H-h);
            tem = colors * m;
            glColor3f(tem.x, tem.y, tem.z); //c*m
            glVertex3f(x,y+1,get(x,y+1));
            
            glEnd();
            if (wireframe) { glBegin(GL_LINE_LOOP); }
            else { glBegin(GL_TRIANGLES); }
            m = (((y + 1) - h)/(H - h));
            m = 0 + (m-h)*(1-0)/(H-h);
            //tem = colors * m;
            glColor3f(c*m, c*m, c*m);
            glVertex3f(x+1,y+1,get(x+1,y+1));
            
            m = ((y - h)/(H - h));
            m = 0 + (m-h)*(1-0)/(H-h);
            //tem = colors * m;
            glColor3f(c*m, c*m, c*m);
            glVertex3f(x+1,y,get(x+1,y));
            
            m = (((y + 1) - h)/(H - h));
            m = 0 + (m-h)*(1-0)/(H-h);
            //tem = colors * m;
            glColor3f(c*m, c*m, c*m);
            glVertex3f(x,y+1,get(x,y+1));
            
            glEnd();
        }
    }
    
  
    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    mygllib::View & view = *(mygllib::SingletonView::getInstance());
    switch(key)
    {
        case 'x': view.eyex() -= 1.0; break;
        case 'X': view.eyex() += 1.0; break;
        case 'y': view.eyey() -= 1.0; break;
        case 'Y': view.eyey() += 1.0; break;
        case 'z': view.eyez() -= 1.0; break;
        case 'Z': view.eyez() += 1.0; break;
        case 'v': view.fovy() -= 1.0; break;
        case 'V': view.fovy() += 1.0; break;
        case 'a': view.aspect() -= 0.1; break;
        case 'A': view.aspect() += 0.1; break;
        case 'n': view.zNear() -= 1.0; break;
        case 'N': view.zNear() += 1.0; break;
        case 'f': view.zFar() -= 1.0; break;
        case 'F': view.zFar() += 1.0; break;

        case '+': init(); break;// change to generate new terrain
        case 'w': wireframe = true; break;
        case 's': wireframe = false; break;
        case 'l': left -= 0.1; break;
        case 'L': left += 0.1; break;
        case 'r': right -= 0.1; break;
        case 'R': right += 0.1; break;
        case 't': top -= 0.1; break;
        case 'T': top += 0.1; break;
        case 'b': bottom -= 0.1; break;
        case 'B': bottom += 0.1; break;
            
        // light position
        case '!': light.x() -= 1.0; break;
        case '@': light.x() += 1.0; break;
        case '#': light.y() -= 1.0; break;
        case '$': light.y() += 1.0; break;
        case '%': light.z() -= 1.0; break;
        case '^': light.z() += 1.0; break;
        // Turning light on and off
        case '&': light.on(); break;
        case '*': light.off(); break;
    }

    view.set_projection();
    view.lookat();
    light.set_position();
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, 700, 700);
}

int main(int argc, char ** argv)
{
    // Initialize with a window of size 700-by-700
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 700);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("TERRAIN");
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    //glutTimerFunc(10, animate, 1);
    glutMainLoop();
    
    return 0;
}

