// File : SingletonView.h
// Author: Jarrett McCarty

#ifndef SINGLETONVIEW_H
#define SINGLETONVIEW_H

#include "View.h"
namespace mygllib
{
    class SingletonView
    {
    public:
        static mygllib::View * getInstance();
    private: static View * instance_;
    };
}

#endif
