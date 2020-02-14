// File:  Light.h
// Author: Jarrett McCarty

#ifndef LIGHT_H
#define LIGHT_H
#include <GL/freeglut.h>

namespace mygllib
{
    class LightError // TODO
    {};
    
    class Light
    {
    public:
    Light() // same as light0
        
        : ambR_(0.0), ambG_(0.0), ambB_(1.0), ambA_(0.0),
            diffR_(1.0), diffG_(1.0), diffB_(1.0), diffA_(1.0),
            specR_(1.0), specG_(1.0), specB_(1.0), specA_(1.0),
            x_(0.0), y_(0.0), z_(1.0), w_(0.0),
            shininess_(1.0)
        {
            light_ambient[0] = ambR_;
            light_ambient[1] = ambG_;
            light_ambient[2] = ambB_;
            light_ambient[3] = ambA_;
 
            light_diffuse[0] = diffR_;
            light_diffuse[1] = diffG_;
            light_diffuse[2] = diffB_;
            light_diffuse[3] = diffA_;
            
            light_specular[0] = specR_;
            light_specular[1] = specG_;
            light_specular[2] = specB_;
            light_specular[3] = specA_;
            
            light_position[0] = x_;
            light_position[1] = y_;
            light_position[2] = z_;
            light_position[3] = w_;
        }
    Light(float ambR, float ambG, float ambB, float ambA,
          float diffR, float diffG, float diffB, float diffA,
          float specR, float specG, float specB, float specA,
          float x, float y, float z, float w,
          float shininess=0.0)
        
        : ambR_(ambR), ambG_(ambG), ambB_(ambB), ambA_(ambA),
            diffR_(diffR), diffG_(diffG), diffB_(diffB), diffA_(diffA),
            specR_(specR), specG_(specG), specB_(specB), specA_(specA),
            x_(x), y_(y), z_(z), w_(w),
            shininess_(shininess)
        {
            light_ambient[0] = ambR_;
            light_ambient[1] = ambG_;
            light_ambient[2] = ambB_;
            light_ambient[3] = ambA_;
 
            light_diffuse[0] = diffR_;
            light_diffuse[1] = diffG_;
            light_diffuse[2] = diffB_;
            light_diffuse[3] = diffA_;
            
            light_specular[0] = specR_;
            light_specular[1] = specG_;
            light_specular[2] = specB_;
            light_specular[3] = specA_;
            
            light_position[0] = x_;
            light_position[1] = y_;
            light_position[2] = z_;
            light_position[3] = w_;
        }
        static void all_on() { glEnable(GL_LIGHTING); }
        static void all_off() { glDisable(GL_LIGHTING); }
        void on() { glEnable(GL_LIGHT0); }
        void off() { glDisable(GL_LIGHT0); }
        void set()
        {
             glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
             glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
             glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
             glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        }
        float x() const { return x_; }
        float & x() { return x_; }
        float y() const { return y_; }
        float & y() { return y_; }
        float z() const { return z_; }
        float & z() { return z_; }
        void set_position()
        {
            light_position[0] = x_;
            light_position[1] = y_;
            light_position[2] = z_;
            light_position[3] = w_;
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        }
    private:
        float ambR_, ambG_, ambB_, ambA_,
            diffR_, diffG_, diffB_, diffA_,
            specR_, specG_, specB_, specA_,
            x_, y_, z_, w_;
        GLfloat light_ambient[4];
        GLfloat light_diffuse[4];
        GLfloat light_specular[4]; 
        GLfloat light_position[4]; 
        float shininess_; 
    };
}
extern mygllib::Light light;

#endif


