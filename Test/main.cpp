#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;




int main()
{
    Game game;
    //Game1.InitPlayers();
    //Game1.Print();

    ifstream ifs("Player1.txt");


    std::string name1;
    std::string name2;
    std::string str;
    int score1;
    int score2;

    std::getline(ifs, name1,';');
    std::getline(ifs, str,'\n');
    score1 = atoi(str.c_str());

    std::getline(ifs, name2,';');
    std::getline(ifs, str,'\n');
    score2 = atoi(str.c_str());

    game.play(name1, score1, name2, score2);
    game.disp();
    return 0;
}
