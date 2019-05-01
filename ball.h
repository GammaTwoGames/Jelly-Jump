#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SFML/Graphics.hpp>

class Ball
{
private:
    float z0;
public:
    float zb, uz;
    float xb, ux;
    Ball()
    {
        z0 = -2;
        zb = 0;
        uz = 0.3;
        ux = 0;
        xb = 0;
    }
    void app(float time)
    {
        zb += uz*time;
        xb += ux*time;
        if (xb < -2) xb = -2;
        if (xb > 2) xb = 2;
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
       if (abs(zb - z0) < 0.05) uz = 3.5;
    }

    void set_ux(float UX)
    {
        ux = UX;
    }

    void touch(float UX)
    {
        ux = UX;
        uz = 0;
    }
};

#endif // BALL_H_INCLUDED
