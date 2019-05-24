#include <iostream>

float z = 2;
float sea_level = -8;

#include "game.h"

using namespace std;
using namespace sf;

int main()
{
    Game game;
    do
    {
        game.start();
        game.do_game();
    } while (game.end_game == 1);
    return 0;
}
