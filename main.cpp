#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

float z = 2;
float sea_level = -5;

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
    RenderWindow window(sf::VideoMode(432, 768),"2048 - Balls",  Style::None );
    Clock clock;

    Walls wall(2);
    Sea sea(2);
    Jelly jelly(2);

    float zi = 0;

    while (window.isOpen())
    {
        window.clear(Color(255, 255, 255));


        double time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        cout<<z<<"\n";
        time = time/1.8e5*0.6;
        time = (time > 0.5)?0.5:time;

        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

        sea.app(&zi);
        sea.draw(&window, z);

        wall.app(&zi);
        wall.draw(&window, z);

        jelly.app(time);
        jelly.draw(&window, z);


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
                if (event.key.code == sf::Keyboard::Space)
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

        sea_level += time/2;

        z = jelly.get_z() + 3;
        zi += jelly.get_speed()*time;

		if (Keyboard::isKeyPressed(Keyboard::Up)) { z += time; zi += time; } //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
		if (Keyboard::isKeyPressed(Keyboard::Down)) { z -= time; zi -= time; }


        window.setMouseCursorVisible(1);
        window.display();
    }


    cout << "Hello world!" << endl;
    return 0;
}
