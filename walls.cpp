Walls::Walls(int jj)
{
    for (int i = - 1; i < 3; i ++)
        push_walls_of_level(&polygons, i);
    z_gen = 3;
}

void Walls::app(float *zi)
{
    if (z_gen*5 - z < 10) {push_walls_of_level(&polygons, z_gen); z_gen++;}
}

int Walls::get_size()
{
    return polygons.size();
}

