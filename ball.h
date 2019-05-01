#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SFML/Graphics.hpp>

class Ball
{
private:
    float z0;
public:
    float zb, uz;
    Ball()
    {
        z0 = -2;
        zb = 0;
        uz = 0.3;
    }
    void app(float time)
    {
        zb += uz*time;
        if (zb > z0) {uz -= time;} else {uz = 0; zb = z0;}
        if (zb - z0 > 4) z0 += 3;
    }
    void draw(RenderWindow* window)
    {
        CircleShape cir(50);
        cir.setFillColor(Color(255,0,0));
        cir.setPosition(432/2 - 50, 768 - zb*200 - 50);
        window->draw(cir);
    }

    void jump()
    {
       if (abs(zb - z0) < 0.05) uz = 3;
    }
};

#endif // BALL_H_INCLUDED
