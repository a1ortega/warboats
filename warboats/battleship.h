#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

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
    char mapArray[10][10];
};

class Player {
public:
    Ship* ship[5];
    map shipMap;
    map guessMap;
    string name;
    int getGuessX();
    int getGuessY();
    void getName();
    void playerCreateShip(int shipNumber, int length, map* map);
    void autoCreateShip(int shipNumber, int length, map* map);
    void initializeShips();
    void autoInitializeShips();
    bool takeTurn(Player* otherPlayer);
    int hitCheck(Player* otherPlayer, int coordinate[]);
    bool guessCheck(string position);
};

class AI: public Player{
private:
    string difficulty;
public:
    Ship* aiCreateShip(int shipNumber, int length, map* map);
    void takeTurn(map enemyShipMap);
    void getName();
    void setDifficulty(string difficulty);
};

//Checks return TRUE if there is an error, and false if there is NO error
bool coordinateCheck(string position);
bool intersectionCheck(string position, string orientation, int length, map *map);
bool boundaryCheck(string position, string orientation, int length);
//int* generateGuess(string difficulty, char** guessMap);
void printMap(Player p1);
void placeShip(Ship *ship, map *shipMap, char counter);
void sinkShip(Ship *ship, map *shipMap);
char printMenu();
bool validateInput(char playerOption);
void startGame(Player* p2);
void startGameAI(Player* p2);
void showCredits();
int showSubMenu();
void clearScreen();
bool endGame(Player* winner);
