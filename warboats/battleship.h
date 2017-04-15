#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

//int main();
class Ship {
public:
    int health[5];
    string chunk[5];
    int length;
    Ship(int shipNumber, string position, int l, string orientation);
    bool shot(string coord);
    bool isAlive();
};

class map {
public:
    map();
    const static int size = 10;     // Size won't ever change
    //void printMap(map *player1ships, map *player1guesses);
    bool hitCheck(map *guessMap, int coordinate[]);
    bool guessCheck(int coordinate[]);
    void placeShip(Ship *ship, map *shipMap, char counter);
    char mapArray[10][10];
};

class Player {
public:
    Ship* ship1;
    Ship* ship2;
    Ship* ship3;
    Ship* ship4;
    Ship* ship5;
    map shipMap;
    map guessMap;
    string name;
    int getGuessX();
    int getGuessY();
    void getName();
    Ship* createShip(int shipNumber, int length, map* map);
    void initializeShips();
    void takeTurn(Player otherPlayer);
};

class AI: public Player{
private:
    string difficulty;
public:
    Ship* createShip(int shipNumber, int length, map* map);
    void takeTurn(map enemyShipMap);
    void getName();
    void setDifficulty(string difficulty);
};

//Checks return TRUE if there is an error, and false if there is NO error
bool coordinateCheck(string position);
bool guessMapCheck(string position, map* map);
bool missedHitCheck(string position, map* map);
bool intersectionCheck(string position, string orientation, int length, map *map);
bool boundaryCheck(string position, string orientation, int length);
int* generateGuess(string difficulty, char** guessMap);

bool endGame(string winner);
int showSubMenu();
void printMap(Player p1);
void placeShip(Ship *ship, map *shipMap, char counter);
char printMenu();
bool validateInput(char playerOption);
void startGame(Player* p2);
void showCredits();
