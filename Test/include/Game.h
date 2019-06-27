#ifndef GAME_H
#define GAME_H
#include <string>
#include <string.h>
#include "Player.h"
#include <iostream>

class Game
{
    public:
        Game();
        virtual ~Game();
        void play();
        void play(std::string n1, int s1, std::string n2, int s2);
        void disp();

    protected:

    private:
        Player player1;
        Player player2;
};

#endif // GAME_H
