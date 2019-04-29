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

float colum[5][5] =
{
    {0.5, 0.5,0.5,0.5,0.5},
    {0.5, 2  ,1  ,1  ,1  },
    {0.5, 1  ,1  ,1  ,1  },
    {0.5, 1  ,1  ,2  ,1  },
    {0.5, 1  ,1  ,1  ,1  }
};




void push_rect( vector <Triangle3D> *scene, float x, float y, float z, float dx, float dy, float dz, bool orient)
{
    for (int i = 0; i < 24 - 4; i ++)
    {
        Color c;
        if (i > -1) c = Color(200,200,200);
        if (i > 7 - 4) c = Color(227,227,227);
        if (i > 15 - 4) c = Color(255,255,255);
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

void push_column( vector <Triangle3D> *scene, int y, int z)
{
   for (int i = 0; i < 5; i ++)
        for (int j = 0; j < 5; j ++)
            push_rect(scene, -4, i + 5*y, j/2.0 + 5 + 5*z, 0.5 + colum[i][j], 1, 0.5, 0);
}


#endif // RECTANGLE_H_INCLUDED
