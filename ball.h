#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SFML/Graphics.hpp>

class Ball
{
private:
    float z0;
    bool is_jump;
public:
    float zb, uz;
    float xb, ux;
    Ball()
    {
        is_jump = 0;
        z0 = -2;
        zb = -2;
        uz = 0;
        ux = 0;
        xb = 0;
    }
    void app(float time, vector<float> xs, vector<float> zs)
    {
        //is_jump = 0;
        zb += uz*time;
        xb += ux*time;
        ux -= 0.3*ux*time;
        if (xb < -3) xb = -3;
        if (xb > 3) xb = 3;
        //if (zb > z0) {uz -= 1*time;} else {uz = 0; zb = z0;}
        //if (zb - z0 > 4) z0 += 4;
        int touch = -1;
        for (int i = 0; i < xs.size(); i ++)
        {
            if (zb < zs[i] && zb > zs[i] - 0.5 && uz <= 0 && xb > xs[i] - 1 && xb < xs[i] + 1) touch = i;
        }
        if (touch == -1) {uz -= 1*time;} else {uz = 0; zb = zs[touch]; if (is_jump == 1) {uz = 3; is_jump = 0;}}
        //cout<<(bool)(zb < zs[0])<<"  "<<(bool)(zb > zs[0] - 0.5)<<"  "<<(bool)(uz < 0)<<"  "<<(bool)(xb > xs[0] - 0.5)<<endl;
        //cout<<is_jump<<endl;
        //uz = 0;
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

       //if (uz == 0) uz = 3;
       is_jump = 1;
    }

    void set_ux(float UX)
    {
        ux = UX;
    }

    //void touch(float UX)
    //{
     //   ux = UX;
     //   uz = 0;
    //}
};

#endif // BALL_H_INCLUDED
