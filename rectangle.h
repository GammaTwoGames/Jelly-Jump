#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

using namespace std;
using namespace sf;


int map_ret[20][3][3] = {
    {{0,0,0}, {1,0,0}, {0,1,0}},
    {{1,0,0}, {0,1,0}, {1,1,0}},
    //{{0,0,1}, {1,0,1}, {0,1,1}},
    //{{1,0,1}, {0,1,1}, {1,1,1}},

    {{0,0,0}, {1,0,0}, {1,1,0}},
    {{0,0,0}, {0,1,0}, {1,1,0}},
    //{{0,0,1}, {1,0,1}, {1,1,1}},
    //{{0,0,1}, {0,1,1}, {1,1,1}},

    {{0,0,0}, {1,0,0}, {0,0,1}},
    {{1,0,0}, {0,0,1}, {1,0,1}},
    {{0,1,0}, {1,1,0}, {0,1,1}},
    {{1,1,0}, {0,1,1}, {1,1,1}},

    {{0,0,0}, {0,0,1}, {1,0,1}},
    {{0,0,0}, {1,0,0}, {1,0,1}},
    {{0,1,0}, {0,1,1}, {1,1,1}},
    {{0,1,0}, {1,1,0}, {1,1,1}},

    {{0,0,0}, {0,0,1}, {0,1,0}},
    {{0,0,1}, {0,1,0}, {0,1,1}},
    {{1,0,0}, {1,0,1}, {1,1,0}},
    {{1,0,1}, {1,1,0}, {1,1,1}},

    {{0,0,0}, {0,0,1}, {0,1,1}},
    {{0,0,0}, {0,1,0}, {0,1,1}},
    {{1,0,0}, {1,0,1}, {1,1,1}},
    {{1,0,0}, {1,1,0}, {1,1,1}},

};

float colum[3][5][5] = {
{
    {0.5, 0.5,0.5,0.5,0.5},
    {0.5, 1  ,1  ,1  ,1  },
    {0.5, 1  ,2  ,2  ,1  },
    {0.5, 1  ,1  ,1  ,1  },
    {0.5, 1  ,2  ,2  ,1  }
},
{
    {0.5, 0.5,0.5,0.5,0.5},
    {0.5, 2  ,1  ,1  ,1  },
    {0.5, 1  ,1  ,1  ,3  },
    {0.5, 1  ,1  ,2  ,1  },
    {0.5, 1  ,1  ,1  ,1  }
},
{
    {0.5, 0.5,0.5,0.5,0.5},
    {0.5, 1  ,1  ,1  ,1  },
    {0.5, 1  ,1  ,1  ,2  },
    {0.5, 1  ,1  ,1  ,1  },
    {0.5, 1  ,3  ,1  ,1  }
}
};




void push_rect(vector<Triangle3D> *scene, float x, float y, float z, float dx, float dy, float dz, bool orient)
{
    for (int i = 0; i < 24 - 4; i ++)
    {
        Color c;
        if (i > -1) c = Color(235*0.95,235*0.95,235);
        if (i > 7 - 4) c = Color(245*0.95,245*0.95,245);
        if (i > 15 - 4) c = Color(255*0.95,255*0.95,255);
        if ((i != 12) && (i != 13) && (i != 16) && (i != 17) && (orient == 0))
            scene->push_back(Triangle3D(Point3D(x+dx*map_ret[i][0][0],y+dy*map_ret[i][0][1],z+dz*map_ret[i][0][2],c),
                                        Point3D(x+dx*map_ret[i][1][0],y+dy*map_ret[i][1][1],z+dz*map_ret[i][1][2],c),
                                        Point3D(x+dx*map_ret[i][2][0],y+dy*map_ret[i][2][1],z+dz*map_ret[i][2][2],c)
                                        ));
        if (i != 14 && i != 15 && i != 18 && i != 19 && orient == 1)
            scene->push_back(Triangle3D(Point3D(x+dx*map_ret[i][0][0],y+dy*map_ret[i][0][1],z+dz*map_ret[i][0][2],c),
                                        Point3D(x+dx*map_ret[i][1][0],y+dy*map_ret[i][1][1],z+dz*map_ret[i][1][2],c),
                                        Point3D(x+dx*map_ret[i][2][0],y+dy*map_ret[i][2][1],z+dz*map_ret[i][2][2],c)
                                        ));
    }
}

void push_rect_orange(vector<Triangle3D> *scene, float x, float y, float z, float dx, float dy, float dz, bool orient)
{
    for (int i = 0; i < 24 - 4; i ++)
    {
        Color c;
        if (i > -1) c = Color(255,183,0);
        if (i > 7 - 4) c = Color(255,203,0);
        if (i > 15 - 4) c = Color(255,193,0);
        if ((i != 12) && (i != 13) && (i != 16) && (i != 17) && (orient == 0))
            scene->push_back(Triangle3D(Point3D(x+dx*map_ret[i][0][0],y+dy*map_ret[i][0][1],z+dz*map_ret[i][0][2],c),
                                        Point3D(x+dx*map_ret[i][1][0],y+dy*map_ret[i][1][1],z+dz*map_ret[i][1][2],c),
                                        Point3D(x+dx*map_ret[i][2][0],y+dy*map_ret[i][2][1],z+dz*map_ret[i][2][2],c)
                                        ));
        if (i != 14 && i != 15 && i != 18 && i != 19 && orient == 1)
            scene->push_back(Triangle3D(Point3D(x+dx*map_ret[i][0][0],y+dy*map_ret[i][0][1],z+dz*map_ret[i][0][2],c),
                                        Point3D(x+dx*map_ret[i][1][0],y+dy*map_ret[i][1][1],z+dz*map_ret[i][1][2],c),
                                        Point3D(x+dx*map_ret[i][2][0],y+dy*map_ret[i][2][1],z+dz*map_ret[i][2][2],c)
                                        ));
    }
}

void push_rect_contr(vector<Triangle3D> *scene, float x, float y, float z, float dx, float dy, float dz, bool orient)
{
    for (int i = 0; i < 24 - 4; i ++)
    {
        Color c;
        if (i > -1) c = Color(200*0.95,200*0.95,200);
        if (i > 7 - 4) c = Color(220*0.95,220*0.95,220);
        if (i > 15 - 4) c = Color(220*0.95,220*0.95,220);
        if ((i != 12) && (i != 13) && (i != 16) && (i != 17) && (orient == 0))
            scene->push_back(Triangle3D(Point3D(x+dx*map_ret[i][0][0],y+dy*map_ret[i][0][1],z+dz*map_ret[i][0][2],c),
                                        Point3D(x+dx*map_ret[i][1][0],y+dy*map_ret[i][1][1],z+dz*map_ret[i][1][2],c),
                                        Point3D(x+dx*map_ret[i][2][0],y+dy*map_ret[i][2][1],z+dz*map_ret[i][2][2],c)
                                        ));
        if (i != 14 && i != 15 && i != 18 && i != 19 && orient == 1)
            scene->push_back(Triangle3D(Point3D(x+dx*map_ret[i][0][0],y+dy*map_ret[i][0][1],z+dz*map_ret[i][0][2],c),
                                        Point3D(x+dx*map_ret[i][1][0],y+dy*map_ret[i][1][1],z+dz*map_ret[i][1][2],c),
                                        Point3D(x+dx*map_ret[i][2][0],y+dy*map_ret[i][2][1],z+dz*map_ret[i][2][2],c)
                                        ));
    }
}

void push_column(vector <Triangle3D> *scene, int y, int z)
{

    int r = rand()%3;

    for (int i = 0; i < 5; i ++)
        for (int j = 0; j < 5; j ++)
        {
            push_rect(scene, -4, i + 5*y, j/2.0 + 5 + 5*z, 0.5 + colum[r][i][j], 1, 0.5, 0);
            r = rand()%3;
            push_rect(scene, 4 - colum[r][i][j] - 0.5, i + 5*y, j/2.0 + 5 + 5*z, 0.5 + colum[r][i][j], 1, 0.5, 1);
        }
}

void push_walls_of_level(vector <Triangle3D> *scene, int y)
{
    push_column(scene,y,0);
    push_column(scene,y,1);
}


#endif // RECTANGLE_H_INCLUDED
