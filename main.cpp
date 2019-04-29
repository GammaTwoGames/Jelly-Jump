#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include "triangle3d.h"
#include "rectangle.h"

using namespace std;
using namespace sf;


float z = 0;

bool sorter(Triangle3D a, Triangle3D b)
{
    return a.get_distance(z) > b.get_distance(z);
}

int main()
{
    RenderWindow window(sf::VideoMode(432, 768),"2048 - Balls",  Style::None );
    Clock clock;
    //float z = 0;

    vector<Triangle3D> scene;
    //for (int j = 0; j < 10; j ++)
        //push_rect(&scene,rand()%10-5,rand()%20,3, 1, 1, 0.5);

    float zi = 0;

    while (window.isOpen())
    {
        window.clear(Color(255, 255, 0));
        sort(scene.begin(), scene.end(), sorter);

        if (zi > 5) {push_column(&scene,z/5 + 4,0); push_column(&scene,z/5 + 4,1); zi = 0;}

        for (int j = 0; j < scene.size(); j ++) scene[j].draw(&window, z);
        for (int j = 0; j < scene.size(); j ++) if (scene[j].vis == 0) scene.erase(scene.begin() + j);



        double time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        cout<<1e6/time<<"  "<<scene.size()<<"\n";
        time = time/1.8e5*0.6;
        time = (time > 0.5)?0.5:time;


        Vector2i pixelPos = Mouse::getPosition(window);
        Vector2f pos = window.mapPixelToCoords(pixelPos);

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

		if (Keyboard::isKeyPressed(Keyboard::Up)) { z += time; zi += time;} //вторая координата (У) отрицательна =>идём вверх (вспоминаем из предыдущих уроков почему именно вверх, а не вниз)
		if (Keyboard::isKeyPressed(Keyboard::Down)) { z -= time; zi += time; }


        window.setMouseCursorVisible(1);
        window.display();
    }



    cout << "Hello world!" << endl;
    return 0;
}
