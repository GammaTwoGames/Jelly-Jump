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
    Walls(int jj);
    void app(float *zi);
    int get_size();

};
#include "walls.cpp"


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
    float d_z(float y, float x)
    {
        return sin(3*y + 3*Time)*sin(5*x + 1.5*Time)/1.5; //+ ((float)(rand()%10 - 5))/10;
    }
    void app(float time)
    {
        Time += time;
        polygons.clear();
        for (float i = - 4; i < 4; i += 1)
        for (float j = 1; j < 12.5; j += 0.5)
        {
            int c = j*18;

            polygons.push_back(Triangle3D(Point3D(i    ,sea_level + d_z(j    ,i    ),j      ,Color(255*j/12, 255*j/12, 255*j/12)),
                                          Point3D(i + 1,sea_level + d_z(j    ,i + 1),j      ),
                                          Point3D(i    ,sea_level + d_z(j+0.5,i    ),j + 0.5)
                                         ));
            polygons.push_back(Triangle3D(Point3D(i + 1,sea_level + d_z(j+0.5,i + 1),j + 0.5,Color(255*j/12, 255*j/12, 255*j/12)),
                                          Point3D(i + 1,sea_level + d_z(j    ,i + 1),j      ),
                                          Point3D(i    ,sea_level + d_z(j+0.5,i    ),j + 0.5)
                                         ));
        }
    }

};

class Jelly : public Pol_struct
{
private:
    Ball ball;
    bool is_jump;
public:
    Jelly(int jj)
    {
        is_jump = 0;
    }
    void app(float time, vector<float> xs, vector<float> zs)
    {
        ball.app(time, xs, zs);
        if (is_jump == 1) {ball.jump(); is_jump = 0;}
        //cout<<is_jump;
        polygons.clear();
        float d_l = ball.uz/25*(1 - sin(ball.uz*7));
        if (d_l < 0) d_l = 0;
        push_rect_orange(&polygons, -0.5 + d_l + ball.xb, ball.zb , 4 + d_l, 1 - 2*d_l, 1 + 2*d_l, 0.5 - 2*d_l, 0);
        push_rect_orange(&polygons, -0.5 + d_l + ball.xb, ball.zb , 4 + d_l, 1 - 2*d_l, 1 + 2*d_l, 0.5 - 2*d_l, 1);
    }
    void jump()
    {
        is_jump = 1;
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
    //vector<Triangle_transformable> pre_tri;
    STL_file()
    {

    }
    STL_file(float X0, float Y0, float Z0, vector<Triangle3D> new_polygons)
    {
        polygons = new_polygons;
        x0 = X0;
        y0 = Y0;
        z0 = Z0;
        Time = 0;
    }
    STL_file(float X0, float Y0, float Z0, int zz, int name_stl, bool create_buffer, string buffer, int n_no)
    {
        Time = 0;
        x0 = X0;
        y0 = Y0;
        z0 = Z0;

        int num_pol = 0;

        if (create_buffer)
        {

        ofstream fout;
        fout.open(buffer, ios::trunc);

        FILE *fp;
        char name[] = "1.stl";
        name[0] = (char)(name_stl + 48);
        fp = fopen(name, "r");

        char ch, ch_p;
        ch = getc(fp);
        ch = getc(fp);
        ch_p = ch;

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
        }

        ifstream fin(buffer);

        if (!create_buffer) num_pol = n_no;

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

            float col = ((0.8 + 0.2*nor[2]));
            if (nor[1] < 0.2)
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
            polygons[i].culc_color(Color(255,255,245));
        }
    }

    int get_size()
    {
        return polygons.size();
    }
    void change(float X0, float Y0, float Z0)
    {
        x0 = X0;
        y0 = Y0;
        z0 = Z0;
        for (int i = 0; i < polygons.size(); i ++)
        {
            polygons[i].change(X0,Y0,Z0);
        }
    }
    void change_sise(float xs, float ys, float zs, float k, float angle)
    {
        for (int i = 0; i < polygons.size(); i ++)
        {
            polygons[i].jelly_transformation(xs,ys,zs,k,angle);
        }
    }

};

class Platform
{
public:
    float zi, x;
    STL_file pls;
    Platform(int zi_, float x_, bool is_first)
    {
        zi = 2 + 4*zi_;
        x = x_;
        pls = STL_file(x_,2 + 4*zi_,8.5,2,1,is_first,"buffer.txt", 262);
    }
    Platform(float zi_, float x_, STL_file stl)
    {
        zi = 2 + 4*zi_;
        x = x_;
        stl.change(x,zi+2,4.25);
        pls = stl;
    }
    void draw(RenderWindow* window, float z)
    {
        pls.draw(window, z);
        pls.app(0);
    }

};

class Jelly_stl : public Pol_struct
{
private:
    STL_file stl;
    Ball ball;
    bool is_jump;
public:
    Jelly_stl(STL_file stl_)
    {
        stl = stl_;
        is_jump = 0;
        //polygons = stl.polygons;
    }
    void app(float time, vector<float> xs, vector<float> zs)
    {
        ball.app(time, xs, zs);
        if (is_jump == 1) {ball.jump(); is_jump = 0;}
        float d_l = ball.uz/25*(1 - sin(ball.uz*7));
        if (d_l < 0) d_l = 0;

        STL_file buf_stl = stl;
        buf_stl.change(ball.xb ,  ball.zb + 0.5  , 4);
        buf_stl.change_sise(ball.xb ,  ball.zb + 0.5  , 4 , 1 + 0 , ball.xb);
        buf_stl.change_sise(ball.xb ,  ball.zb + 0.5  , 4 , 1 + 2*d_l , 0);
        polygons = buf_stl.polygons;
    }
    void jump()
    {
        is_jump = 1;
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

#endif // WALLS_H_INCLUDED
