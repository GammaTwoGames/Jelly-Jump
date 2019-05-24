#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <fstream>
#include <string>


#include "triangle3d.h"

bool sorter(Triangle3D a, Triangle3D b)
{
    return a.get_distance(z) > b.get_distance(z);
}


#include "rectangle.h"
#include "pol_arr.h"
#include "walls.h"
#include "ball.h"
#include "button.h"

using namespace std;
using namespace sf;

class Game
{
public:
float Time;
int end_game;
Game()
    {
        Time = 0;
        end_game = 0;
    }
void start()
{
    end_game = 0;
    z = 2;
    sea_level = -4;
}
void do_game()
{
    //cout<<(int)'0';
    RenderWindow window(sf::VideoMode(432, 668),"Jelly Jump 0.3.5",  Style::Titlebar );
    Clock clock;

    STL_file stl(0,-2,0,2,1,1,"buffer0.txt", 262);
    STL_file stl_n2(0,3,9,2,6,1,"buffer2.txt", 262);
    STL_file stl_cat(0,0,0,2,3,1,"buffer2.txt", 262);
    stl_cat.change_sise(0,0,0,1.1, 0);
    Walls wall(2);
    Sea sea(2);
    Jelly_stl jelly(stl_cat);
    Barrier barrier(0, 0);
    Button_zero score(0,0,200,100,"40",70);

    vector<Platform> plats;
    plats.push_back(Platform(-1,0,stl));
    plats.push_back(Platform(0,0,stl));
    plats.push_back(Platform(1,0,stl));

    cout<<plats[0].zi<<endl;
    int z_gen_plats = 2;

    float zi = 0;

    float speed = 1;

    while (window.isOpen())
    {
        window.clear(Color(255, 255, 255));


        double time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        Time += time/1e6;

        //cout<<1e6/time<<"\n";
        time = time/1.8e5*0.6*1*speed;
        time = (time > 0.5)?0.5:time;

        speed += 0.001*time;

        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        sea.app(time);
        sea.draw(&window, z);

        wall.app(&zi);
        wall.draw(&window, z);

        stl_n2.draw(&window, z);

        if (z_gen_plats*4 - z < 4) {plats.push_back(Platform(z_gen_plats,rand()%5 - 2,stl)); z_gen_plats ++;}

        for (int i = 0; i < plats.size(); i ++)
            plats[i].draw(&window, z);

        z += 3*(2.5 + jelly.get_z() - z)*time;

        vector<float> xs, zs;

        for (int i = 0; i < plats.size(); i ++)
        {
            xs.push_back(plats[i].x);
            zs.push_back(plats[i].zi);
        }


        jelly.draw(&window, z);


        if (jelly.get_z() + 0.5 > sea_level)
        {
            jelly.app(time, xs, zs);
            //zi += jelly.get_speed()*time;
            if (z > 2.1) sea_level += time/1.2;
            if (z-sea_level > 6) sea_level = z - 6;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                    end_game = 2;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    jelly.jump();
                }
            }
            if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
                if (event.key.code == Mouse::Left)//а именно левая
                {
                    end_game = 1;
                }
        }
        if (end_game == 1) break;

		if (Keyboard::isKeyPressed(Keyboard::Right)) { jelly.set_ux(1.2); } //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
		if (Keyboard::isKeyPressed(Keyboard::Left)) { jelly.set_ux(-1.2); }


        window.setMouseCursorVisible(1);
        window.display();
    }


    //cout << "Hello world!" << endl;
    if (end_game != 2) end_game = 1;
}
};

#endif // GAME_H_INCLUDED
