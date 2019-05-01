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
        push_rect_orange(&polygons, -0.5 + d_l + ball.xb, ball.zb , 4 + d_l, 1 - 2*d_l, 1 + 2*d_l, 0.5 - 2*d_l, 0);
        push_rect_orange(&polygons, -0.5 + d_l + ball.xb, ball.zb , 4 + d_l, 1 - 2*d_l, 1 + 2*d_l, 0.5 - 2*d_l, 1);
    }
    void jump()
    {
        ball.jump();
    }

    void set_ux(float ux)
    {
        ball.ux = ux;
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
        if (sea_level < zp)
        {
            push_rect_contr(&polygons, -5,    -2.5 + zp, 4 , 5 - open, 0.5, 1, 0);
            push_rect_contr(&polygons,  open, -2.5 + zp, 4 , 5 - open, 0.5, 1, 1);
        }
    }

};

class STL_file : public Pol_struct
{
private:
    float Time;
    float x0, y0, z0;
public:
    float norm_z;
    vector<Triangle_transformable> pre_tri;
    STL_file(float X0, float Y0, float Z0, int zz, string file_name)
    {
        Time = 0;
        x0 = X0;
        y0 = Y0;
        z0 = Z0;

        ofstream fout;
        fout.open("buffer.txt", ios::trunc);

        FILE *fp;
        fp = fopen("platform3.stl", "r");

        char ch, ch_p;
        ch = getc(fp);
        ch = getc(fp);
        ch_p = ch;

        int num_pol = 0;

        while (ch != 's')
        {
            ch = getc(fp);
            if (((ch > 47) && (ch < 58)) || (ch == '.') || (ch == '+') || (ch == '-') || (ch == 'E') || ((ch == 'e') && ((ch_p > 47) && (ch_p < 58))) || (ch == '\n'))
            {
                if (ch == '\n')
                    num_pol++;
                fout << ch;
            }
            else
                fout << ' ';
            ch_p = ch;
        }

        num_pol--;
        num_pol /= 7;

        fout.close();
        //return 0;

        ifstream fin("buffer.txt");

        for (int i = 0; i < num_pol + 1; i ++)
        {
            float nor[3];
            for (int j = 0; j < 3; j ++)
            {
                fin >> nor[j];
            }
            //float col;
            //col = ((0.9 + 0.1*nor[2]));

            float x[3][3];
            for (int k = 0; k < 3; k ++)
                for (int j = 0; j < 3; j ++)
                {
                    fin >> x[k][j];
                    x[k][j] = (float)(x[k][j] / 1.0);
                }

            float col = ((0.9 + 0.1*nor[2]));
            polygons.push_back(Triangle3D(Point3D(x0+x[0][0],y0+x[0][2],(z0+x[0][1])/2.0,Color(255,203*col,0*col)),
                                          Point3D(x0+x[1][0],y0+x[1][2],(z0+x[1][1])/2.0,Color(col,col,col)),
                                          Point3D(x0+x[2][0],y0+x[2][2],(z0+x[2][1])/2.0,Color(col,col,col)), nor[2]
                                          ));
        }
    }

    void app(float time)
    {
        Time += time;
        for (int i = 0; i < polygons.size(); i ++)
        {
            polygons[i].abel_transformation(-2,7,8,1,Time);
            polygons[i].culc_color(Color(240,240,255));
        }
    }

    int get_size()
    {
        return polygons.size();
    }
};

#endif // WALLS_H_INCLUDED
