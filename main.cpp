#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <fstream>
#include <string>

float z = 2;
float sea_level = -10;

#include "triangle3d.h"

bool sorter(Triangle3D a, Triangle3D b)
{
    return a.get_distance(z) > b.get_distance(z);
}

#include "rectangle.h"
#include "pol_arr.h"
#include "walls.h"
#include "ball.h"

using namespace std;
using namespace sf;


int main()
{
    cout<<(int)'0';
    RenderWindow window(sf::VideoMode(432, 668),"Jelly Jump 0.3.5",  Style::Titlebar );
    Clock clock;

    Walls wall(2);
    Sea sea(2);
    Jelly jelly(2);
    Barrier barrier(0, 0);
    //STL_file object(-2,2,8.5,2,1,1,"buffer.txt");
    Platform plat(0,0);
    vector<Platform> plats;
    plats.push_back(Platform(-1,0));
    for (int i = 0; i < 2; i ++)
        plats.push_back(Platform(i,rand()%4 - 1));

    float zi = 0;

    while (window.isOpen())
    {
        window.clear(Color(255, 255, 255));


        double time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        //cout<<1e6/time<<"\n";
        time = time/1.8e5*0.6*1;
        time = (time > 0.5)?0.5:time;

        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        sea.app(time);
        sea.draw(&window, z);

        wall.app(&zi);
        wall.draw(&window, z);

        //barrier.app(time);
        //barrier.draw(&window, z);

        //object.app(0);
        //object.draw(&window, z);
        for (int i = 0; i < plats.size(); i ++)
            plats[i].draw(&window, z);

        //z = jelly.get_z() + 3;
        z += 3*(2.5 + jelly.get_z() - z)*time;

        vector<float> xs, zs;

        for (int i = 0; i < plats.size(); i ++)
        {
            xs.push_back(plats[i].x);
            zs.push_back(plats[i].zi);
        }

        jelly.app(time, xs, zs);
        jelly.draw(&window, z);

        sea_level += time/1.7;
        if (z-sea_level > 7) sea_level = z - 7;

        zi += jelly.get_speed()*time;

        if (jelly.get_z() + 0.5 < sea_level) break;


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    jelly.jump();
                }
            }
            if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
                if (event.key.code == Mouse::Left)//а именно левая
                {

                }
            if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
                if (event.key.code == Mouse::Right)//а именно левая
                {
                }
        }

		//if (Keyboard::isKeyPressed(Keyboard::Up)) { z += time; zi += time; } //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
		//if (Keyboard::isKeyPressed(Keyboard::Down)) { z -= time; zi -= time; }

		//jelly.set_ux(0);
		if (Keyboard::isKeyPressed(Keyboard::Right)) { jelly.set_ux(1); } //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
		if (Keyboard::isKeyPressed(Keyboard::Left)) { jelly.set_ux(-1); }


        window.setMouseCursorVisible(1);
        window.display();
    }


    cout << "Hello world!" << endl;
    return 0;
}
