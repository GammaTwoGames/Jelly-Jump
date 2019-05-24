#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

class Button_zero
{
public:
    int x, y;
    int l, h;
    int siz;
    string st;
Button_zero(int _x, int _y, int _l, int _h, string _st, int _siz)
{
    x = _x;
    y = _y;
    l = _l;
    h = _h;
    st = _st;
    siz = _siz;
}

void set_string(string _st)
{
    st = _st;
}

void drawing_button(RenderWindow* window, int alfa)
{
    //RectangleShape rectangle(sf::Vector2f(l, h));
    //rectangle.setPosition(x,y);
    //rectangle.setFillColor(Color(182, 92, 0));
    //window->draw(rectangle);

    Font rita;
    Text chi("",rita,siz);

    rita.loadFromFile("rita.ttf");
    chi.setFont(rita);
    //chi.setStyle(sf::Text::Bold | sf::Text::Regular);

    chi.setString(st);
    chi.setPosition(Vector2f(x + l/2 - chi.getLocalBounds().width/2 - siz/15, y + h/2 - siz/3.5 - chi.getLocalBounds().height/2));
    chi.setFillColor(Color(255,183,0,alfa));
    window->draw(chi);
}


};


#endif


