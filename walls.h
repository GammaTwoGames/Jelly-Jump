#ifndef WALLS_H_INCLUDED
#define WALLS_H_INCLUDED

#include <cmath>

using namespace std;
using namespace sf;

#include "triangle3d.h"
#include "rectangle.h"
#include "pol_arr.h"
#include "ball.h"
#include <fstream>
#include <string>

class Walls : public Pol_struct
{
private:
    int z_gen;
public:
    Walls(int jj)
    {
        for (int i = - 1; i < 3; i ++)
            push_walls_of_level(&polygons, i);
        z_gen = 3;
    }
    void app(float *zi)
    {
        if (z_gen*5 - z < 10) {push_walls_of_level(&polygons, z_gen); z_gen++;}
    }

};

class Sea : public Pol_struct
{
private:
    float Time;
public:
    Sea(int jj)
    {
        polygons.clear();
        Time = 0;
    }
    float d_z(int y)
    {
        return sin(2*(float)(y) + Time)/2.0;
    }
    void app(float time)
    {
        Time += time;
        polygons.clear();
        for (int i = - 4; i < 4; i ++)
        for (int j = 1; j < 16; j ++)
        {
            int c = j*18;
            polygons.push_back(Triangle3D(Point3D(i,sea_level + d_z(j),j,Color(255*j/15,162 + (255-162)*j/15,232 + (255 - 232)*j/15)),
                                        Point3D(i + 1,sea_level + d_z(j),j,Color(c*0.9,c*0.9,c)),
                                        Point3D(i,sea_level + d_z(j+1),j + 1,Color(c*0.9,c*0.9,c))
                                        ));
            polygons.push_back(Triangle3D(Point3D(i+1,sea_level + d_z(j+1),j+1,Color(136 + (255 - 153)*j/15,219 + (255-219)*j/15,255 + (255 - 255)*j/15)),
                                        Point3D(i + 1,sea_level + d_z(j),j,Color(c*0.8,c*0.8,c)),
                                        Point3D(i,sea_level+ d_z(j+1),j + 1,Color(c*0.8,c*0.8,c))
                                        ));
        }
    }

};

class Jelly : public Pol_struct
{
private:
    Ball ball;
public:
    Jelly(int jj)
    {

    }
    void app(float time)
    {
        ball.app(time);
        polygons.clear();
        float d_l = ball.uz/25*(1 - sin(ball.uz*7));
        if (d_l < 0) d_l = 0;
        push_rect_orange(&polygons, -0.5 + d_l , ball.zb , 4 + d_l, 1 - 2*d_l, 1 + 2*d_l, 0.5 - 2*d_l, 0);
    }
    void jump()
    {
        ball.jump();
    }

    float get_speed()
    {
        return ball.uz;
    }
    float get_z()
    {
        return ball.zb;
    }

};

class Barrier : public Pol_struct
{
private:
    float Time;
    float open, u, t_start, zp;
public:
    Barrier(float T_start, int Z)
    {
        t_start = T_start;
        Time = 0;
        open = 5;
        u =  (0.5 + (rand()%10)/5.0)/2;
        zp = Z;
    }
    void app(float time)
    {
        Time += time;
        if (Time > t_start) if (open > 0) open -= time*u;
        polygons.clear();
        if (sea_level < -2)
        {
            push_rect_contr(&polygons, -5,    -2.5 + zp, 4 , 5 - open, 0.5, 1, 0);
            push_rect_contr(&polygons,  open, -2.5 + zp, 4 , 5 - open, 0.5, 1, 1);
        }
    }

};

class STL_file : public Pol_struct
{

public:
    float norm_z;
    STL_file(int zz, string file_name)
    {
        ifstream fin(file_name);

        float ff;


        norm_z = 100;

        for (int i = 0; i < 91+1; i ++)
        {
            float nor[3];
            for (int j = 0; j < 3; j ++)
            {
                fin >> nor[j];
            }
            float col;
            col = ((0.9 + 0.1*nor[1]));

            float x1[3], x2[3], x3[3];

            for (int j = 0; j < 3; j ++)
            {
                fin >> x1[j];
                x1[j] = (float)(x1[j] / 1.0);
            }
            for (int j = 0; j < 3; j ++)
            {
                fin >> x2[j];
                x2[j] = x2[j] / 1.0;
            }
            for (int j = 0; j < 3; j ++)
            {
                fin >> x3[j];
                x3[j] = x3[j] / 1.0;
            }
            polygons.push_back(Triangle3D(Point3D(-2+x1[0],7+x1[1],(8+x1[2])/2.0,Color(255,203*col,0*col)),
                                          Point3D(-2+x2[0],7+x2[1],(8+x2[2])/2.0,Color(col,col,col)),
                                          Point3D(-2+x3[0],7+x3[1],(8+x3[2])/2.0,Color(col,col,col))
                                         ));
        }
    }

    int get_size()
    {
        return polygons.size();
    }
};

#endif // WALLS_H_INCLUDED
