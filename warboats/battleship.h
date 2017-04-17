#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std;

//Class definition for the ship object
class Ship {
public:
    
    //initialization of the health, coordinate, and size values for the ship object
    int health[5];
    string chunk[5];
    int length;
    
    //Constructor for the ship object
    Ship(int shipNumber, string position, int l, string orientation);
};

//Class definition for the map object
class map {
public:
    
    //Constructor for the map object
    map();
    
    //Size of the map array's length and height
    const static int size = 10;
    
    //2D array that contains the ship objects and guesses for each player
    char mapArray[10][10];
};

//Class definition for player
class Player {
public:
    
    //Initialization of an array of ships, the shipMap map, the guessMap map, and the name of the player
    Ship* ship[5];
    map shipMap;
    map guessMap;
    string name;
    
    //Method that sets the players name based on user input
    void getName();
    //Method that creates the ship based on a user's choice of a coordinate
    void createShip(int shipNumber, int length, map* map);
    //Method that creates a ship based on a ran
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
    void createShip(int shipNumber, int length, map* map);
    bool takeTurn(Player* p2);
    void getName();
    void setDifficulty(string difficulty);
    void initializeAIShips();
};

//Checks return TRUE if there is an error, and2 false if there is NO error
bool coordinateCheck(string position);
bool intersectionCheck(string position, string orientation, int length, map *map);
bool boundaryCheck(string position, string orientation, int length);
void printMap(Player p1);
void placeShip(Ship *ship, map *shipMap, char counter);
void sinkShip(Ship *ship, map *shipMap);
char printMenu();
bool validateInput(char playerOption);
void startGame(Player* p2);
void startGameAI(AI* p2);
void showCredits();
int showSubMenu();
void clearScreen();
bool endGame(Player* winner, int turnsElapsed);
bool difficultyChecker(string difficulty);
