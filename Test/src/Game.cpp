#include "Game.h"
#include "Player.h"

Player Player1;
Player Player2;

Game::Game()
{

}

Game::~Game()
{
    //dtor
}
void Game::play(std::string n1, int s1, std::string n2, int s2)
{
    Player1.setName(n1);
    Player2.setName(n2);
    Player1.setScore(s1);
    Player2.setScore(s2);

}
void Game::disp()
{
    std::string Play1;
    std::string Play2;
    std::string Score1;
    std::string Score2;

    Play1 = Player1.getName();
    Play2 = Player2.getName();
    Score1 = Player1.getScore();
    Score2 = Player2.getScore();

    std::cout<< "Player 1: " + Play1 + " Score: " + Score1 + "\n";
    std::cout<< "Player 2: " + Play2 + " Score: " + Score2 + "\n";
}
