#ifndef PLAYER_H
#define PLAYER_H
#include <string.h>
#include <string>

class Player
{
    public:
        Player();
        virtual ~Player();
        void setName(std::string n);
        void setScore(int s);
        std::string getName();
        int getScore();
        //void ReadFile(std::string Filename);
        //void PrintDetails();

    protected:

    private:
        int score;
        std::string name;
};

#endif // PLAYER_H
