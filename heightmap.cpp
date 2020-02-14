// File   : heightmap.cpp
// Author : Jarrett McCarty

#include "heightmap.h"

HeightMap::HeightMap()
    : x_(0), y_(0)
{}

HeightMap::HeightMap(int x, int y)
{
    x_ = x;
    y_ = y;
    size_ = (x_ * y_);
    std::vector<float> temp;

    for (int i = 0; i < y_; ++i)
    {
        items_.push_back(temp);
        for (int j = 0; j < x_; ++j)
        {
            items_[i].push_back(0);
        }
    }
}

HeightMap::~HeightMap()
{
    for (int i = 0; i < y_; ++i)
        for (int j = 0; j < x_; ++j)
            items_[i][j] = 0;
}

void HeightMap::clear()
{
    for (int i = 0; i < y_; ++i)
        for (int j = 0; j < x_; ++j)
            items_[i][j] = 0;
}

void HeightMap::print()
{
    for (int i = 0; i < y_; ++i)
    {
        for (int j = 0; j < x_; ++j)
        {
            if (j % 3 == 0)
                std::cout << items_[i][j] << "\n";
            else
                std::cout << items_[i][j] << " ";
        }
        std::cout << "\n\n\n";
    }
}

bool HeightMap::is_edge(int x, int y)
{
    return (x == x_ - 1 || y == y_ - 1 || x == 0 || y == 0);
}

bool HeightMap::over_edge(int x, int y)
{
    return (x > x_ - 1 || y > y_ - 1 || x < 0 || y < 0);
}

void HeightMap::set_x(int x) { x_ = x; }
void HeightMap::set_y(int y) { y_ = y; }

int HeightMap::get_x()
{
    return x_;
}

int HeightMap::get_y()
{
    return y_;
}

int HeightMap::get_size()
{
    return size_;
}

std::vector<std::vector<float>> HeightMap::get_items()
{
    return items_;
}

void HeightMap::set_item(int x, int y, int val)
{
    items_[y][x] = val;
}

float HeightMap::get_item(int x, int y)
{
    return items_[y][x];
}

void HeightMap::square(int x, int y, int size, int os)
{

    items_[y][x] = (items_[y + size][x + size] +
                      items_[y - size][x - size] +
                      items_[y + size][x - size] +
                      items_[y - size][x + size]) / 4 + os;
}

void HeightMap::diamond(int x, int y, int size, int os)
{
    if (x - size < 0)
    {
        items_[y][x] = (items_[y][x + size] +
                          items_[y + size][x] +
                          items_[y - size][x]) / 3 + os;
    }
    else if (x + size > x_ - 1)
    {
        items_[y][x] = (items_[y][x - size] +
                          items_[y + size][x] +
                          items_[y - size][x]) / 3 + os;
    }
    else if (y - size < 0)
    {
        items_[y][x] = (items_[y][x + size] +
                          items_[y][x - size] +
                          items_[y + size][x]) / 3 + os;
    }
    else if (y + size > y_ - 1)
    {
        items_[y][x] = (items_[y][x + size] +
                          items_[y][x - size] +
                          items_[y - size][x]) / 3 + os;
    }
    else
    {
        items_[y][x] = (items_[y][x + size] +
                          items_[y][x - size] +
                          items_[y + size][x] +
                          items_[y - size][x]) / 4 + os;
    } 
}

void HeightMap::generate_map(int size, int roughness)
{
    srand(time(NULL));
    int squaresize = (size - 1) / 2;
    
    while(squaresize > 0)
    {
        for (int y= 0; y < size/(squaresize*2); y++)
        {
            for (int x = 0; x < size / (squaresize * 2 ); x++)
            {
                square((x*squaresize * 2) + squaresize, 
                       (y*squaresize * 2 ) + squaresize, 
                       squaresize, 
                       rand() % roughness*squaresize*2 - squaresize*roughness);
            }
        }
	
        int rowtype = 1;
        
        for (int y = 0; y < size; y += squaresize)
        {
            if (rowtype == 1)
            {
                for (int x = squaresize; x < size; x += 2*squaresize)
                {
                    diamond(x, y, squaresize, rand() % roughness*squaresize * 2 - squaresize);
                }
            }
            if (rowtype == -1)
            {
                for (int x = 0; x < size; x += squaresize*2)
                {
                    diamond(x, y, squaresize, rand() % roughness*squaresize * 2 - squaresize);
                }
            }
            rowtype *= -1;
        }
        
        squaresize *= 0.5;
    }
}

void HeightMap::generate_map(int size, float mag, float roughness) //size is just x but make x better first, sidelength
{
    srand(time(NULL));
    int squaresize = (size - 1) / 2;
    
    while (squaresize > 0)
    {
        for (int y = 0; y < size / (squaresize * 2); y++)
        {
            for (int x = 0; x < size / (squaresize * 2); x++)
            {
                square((x*squaresize * 2) + squaresize,
                       (y*squaresize * 2) + squaresize,
                       squaresize,
                       rand() % int(2 * mag) - mag);
            }
        }
        
        int rowtype = 1;
        
        for (int y = 0; y < size; y += squaresize)
        {
            if (rowtype == 1)
            {
                for (int x = squaresize; x < size; x += 2 * squaresize)
                {
                    diamond(x, y, squaresize, rand() % int(2 * mag) - mag);
                }
            }
            if (rowtype == -1)
            {
                for (int x = 0; x < size; x += squaresize * 2)
                {
                    diamond(x, y, squaresize, rand() % int(2 * mag) - mag);
                }
            }
            rowtype *= -1;
        }
        
        mag *= roughness;
        squaresize *= 0.5;
    }
}

void HeightMap::cap(int l, int u)
{
    for (int i = 0; i < y_; ++i)
    {
        for (int j = 0; j < x_; ++j)
        {
            if (items_[i][j] > u) items_[i][j] = u;
            if (items_[i][j] < l) items_[i][j] = l;
        }
    }
}

void HeightMap::smooth(int filterSize, int passes)
{
    std::vector<std::vector<float>> newelements = items_;
    
    for (int i = 0; i != passes; i++)
    {
        for (int Y = 0; Y != this->y_; Y++)
        {
            for (int X = 0; X != this->x_; X++)
            {
                float surroundingTotal = -items_[Y][X];
                int aroundNum = -1;

                for (int y = -filterSize; y <= filterSize; y++)
                {
                    for (int x = -filterSize; x <= filterSize; x++)
                    {
                        if (X + x > -1 && X + x < this->x_ && Y + y > -1 && Y + y < this->y_)
                        {
                            surroundingTotal += items_[Y + y][X + x];
                            aroundNum++;
                        }
                    }
                }			
                newelements[Y][X] = (items_[Y][X] + (surroundingTotal / aroundNum)) / 2;
            }
        }
        items_ = newelements;
    }
}
