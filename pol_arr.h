#ifndef POL_ARR_H_INCLUDED
#define POL_ARR_H_INCLUDED

#include "triangle3d.h"

class Pol_struct
{
private:
public:
    float z;
    vector<Triangle3D> polygons;
    Pol_struct()
    {
        z = 0;
    }
    void draw(RenderWindow* window, float Z)
    {
        z = Z;
        sort(polygons.begin(), polygons.end(), [&] (Triangle3D a, Triangle3D b) mutable -> bool {return a.get_distance(z) > b.get_distance(z);});

        for (int j = 0; j < polygons.size(); j ++) polygons[j].draw(window, z);
        for (int j = 0; j < polygons.size(); j ++) if (polygons[j].vis == 0) polygons.erase(polygons.begin() + j);
    }
    int size()
    {
        return polygons.size();
    }


};

#endif // POL_ARR_H_INCLUDED
