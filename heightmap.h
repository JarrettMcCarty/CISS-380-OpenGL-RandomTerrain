// File   : heightmap.h
// Author : Jarrett McCarty

#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <vector>
#include <iostream>
#include <time.h>

class HeightMap
{
public:
    HeightMap();
    HeightMap(int, int);
    ~HeightMap();
    void clear();
    void print();
    bool is_edge(int, int);
    bool over_edge(int, int);
    void set_x(int);
    void set_y(int);
    int get_x();
    int get_y();
    int get_size();
    float get_item(int, int);
    std::vector<std::vector<float>> get_items();
    void set_item(int, int, int);
    void load(std::vector<std::vector<float>>);
    void generate_map(int, int, int, int);
    void generate_map(int, int);
    void generate_map(int, float);
    void generate_map(int, float, float);

    void square(int, int, int, int);
    void diamond(int, int, int, int);

    void cap(int, int);
    void smooth(int, int);
private:
    int size_, x_, y_;
    std::vector<std::vector<float>> items_;
};


#endif

