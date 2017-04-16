//
//  battleship.cpp
//  battle_ship_1
//
//  Created by Victor Fan, Adam Hochberger, Marcus Mills, Andrew Ortega, Andrew Showen, Exan Waxman, and Connor Watson on 4/8/17.
//  Copyright © 2017 Victor Fan, Adam Hochberger, Marcus Mills, Andrew Ortega, Andrew Showen, Exan Waxman, and Connor Watson. All rights reserved.
//
// All checks return TRUE if there is an error/miss (boundaryCheck, intersectionCheck, coordinateCheck, missedHitCheck, guessMapCheck)

// For differentiating between player1 and player2 screens in terminal, you can opt to ask the player to pass it to the other and
// have a blank input through cin then clear the screen of all previous maps, etc.

/*
 LATEST CHANGES: Evan Waxman - 4/15/17
 1. Used Marcus's show
 
 Julian Showen - 4/15/17 5:15 PM
 - Changed the takeTurn and checkCoordinate function to fix bugs where entering coordinates outside of the range wouldn't register as outside and mess other stuff up
 */


#include "battleship.h"

using namespace std;

/*** MAIN ***/
int main() {
    //Player player1;
    //Player player2;
    
    bool endGame = false;
    char playerOption;
    
    while(!endGame) {
        playerOption = printMenu();
        string difficulty = "";
        switch(playerOption) {
            case '1':{
                AI* p2 = new AI();
                cout << endl << "Enter a difficulty for the computer player('HARD' 'MEDIUM' or 'EASY'):";
                cin >> difficulty;
                p2->setDifficulty(difficulty);
                startGame(p2);
            }
                break;
            case '2':{
                Player *p2 = new Player();
                startGame(p2);
            }
                break;
            case '3':{
                showCredits();
            }
                break;
            case '4':{
                endGame = true;
                break;
            }
        }
    }
    cout << "Thanks for playing Warboats!" << endl;
    exit(9);
    
    return 0;
}
/***********/

/*******************/
/**  FUNCTIONS  **/
/*******************/
//Method that returns true if a coordinate is no longer valid, but false if the coordinate is a valid option
bool coordinateCheck(string position) {
    /* CHANGELOG
     After running through the edge cases, I added a check for whether or not the position string given was
     less than length two, if there letters in the first prt, and if the resulting letter to ASCII conversion was something outside
     of the range of the letters
     */
    int coordinate[2];
    char column, row;
    
    if (position.length() < 2) {
        return true;
    }
    column = position.at(0);
    row = position.at(1);
    
    //Sets the positions of the coordinate
    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;
    
    if (isalpha(column) != 0) {
        if ((coordinate[0] > 9 || coordinate[0] < 0) || (coordinate[1] > 9 || coordinate[1] < 0)){
            return true;
        }else {
            return false;
        }
    }
    else {
        return true;
    }
}

//
bool intersectionCheck(string position, string orientation, int length, map *map) {
    /* CHANGELOG
     Edited the intersectionCheck method by including the left, down, and up as directions to check for intersection of one
     ship object with that of another
     */
    int coordinate[2];
    char column, row;
    
    column = position.at(0);
    row = position.at(1);
    
    coordinate[1] = toupper(column) - 0x41;   // First argument must be a char A-J. Subtract
    // 0x41 to get int value for array indexing.
    // Refer to ASCII table.
    coordinate[0] = row - 0x30;    // Second argument must be a char 1-10. Subtract
    // 0x31 to get int value for array indexing.
    // Refer to ASCII table.
    if (orientation == "right") {
        for(int i=0; i<length; i++) {
            if(map->mapArray[coordinate[0]][coordinate[1]] != '~') {
                return true;
            }
            coordinate[1]++;
        }
    }
    if (orientation == "left") {
        for(int i=0; i<length; i++) {
            if(map->mapArray[coordinate[0]][coordinate[1]] != '~') {
                return true;
            }
            coordinate[1]--;
        }
    }
    if (orientation == "down") {
        for(int i=0; i<length; i++) {
            if(map->mapArray[coordinate[0]][coordinate[1]] != '~') {
                return true;
            }
            coordinate[0]++;
        }
    }
    if (orientation == "up") {
        for(int i=0; i<length; i++) {
            if(map->mapArray[coordinate[0]][coordinate[1]] != '~') {
                return true;
            }
            coordinate[0]--;
        }
    }
    return false;
}

//
bool boundaryCheck(string position, string orientation, int length) {
    /* CHANGELOG
     Added the small while loop at line 300 to ensure that the length is not below 2 before it separates the components of the string
     */
    int coordinate[2];
    char column, row;
    
    if (position.length() < 2) {
        return true;
    }
    column = position.at(0);
    row = position.at(1);
    
    coordinate[1] = toupper(column) - 0x41;   // First argument must be a char A-J. Subtract
    // 0x41 to get int value for array indexing.
    // Refer to ASCII table.
    coordinate[0] = row - 0x30;    // Second argument must be a char 1-10. Subtract
    // 0x31 to get int value for array indexing.
    // Refer to ASCII table.
    
    
    if(orientation == "left")
    {
        if ((coordinate[1] - length + 1) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(orientation == "right")
    {
        if ((coordinate[1] + length - 1) > 9)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(orientation == "up")
    {
        if ((coordinate[0] - length + 1) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if(orientation == "down")
    {
        if ((coordinate[0] + length - 1) > 9)
        {
            return true;
        }
        else
        {
            return false;
        }
    }else {
        return true;
    }
}

// Print mapArray of map
void printMap(Player p1) {
    
    cout << p1.name << endl;
    cout << "   -------Ships-------  -------Guess-------" << endl;
    cout << "   A B C D E F G H I J  A B C D E F G H I J" << endl;
    
    char row_count = '0';
    for (int i = 0; i < p1.guessMap.size; i++) {
        cout << row_count << "  ";
        for (int j = 0; j < p1.guessMap.size; j++) {
            cout << p1.shipMap.mapArray[i][j] << " " ;
        }
        cout << " ";
        for(int j=0; j< p1.guessMap.size; j++){
            cout << p1.guessMap.mapArray[i][j]<< " ";
        }
        cout << endl;
        row_count++;
    }
}

//
void sinkShip(Ship *ship, map *shipMap) {
    int coordinate[2];
    for(int i=0; i<ship->length; i++) {
        coordinate[1] = toupper(ship->chunk[i].at(0)) - 0x41;   // First argument must be a char A-J. Subtract
        // 0x41 to get int value for array indexing.
        // Refer to ASCII table.
        coordinate[0] = ship->chunk[i].at(1) - 0x30;    // Second argument must be a char 1-10. Subtract
        // 0x31 to get int value for array indexing.
        // Refer to ASCII table.
        shipMap->mapArray[coordinate[0]][coordinate[1]] = '*';
    }
}

//
void placeShip(Ship *ship, map *shipMap, char counter) {
    int coordinate[2];
    for(int i=0; i<ship->length; i++) {
        coordinate[1] = toupper(ship->chunk[i].at(0)) - 0x41;   // First argument must be a char A-J. Subtract
        // 0x41 to get int value for array indexing.
        // Refer to ASCII table.
        coordinate[0] = ship->chunk[i].at(1) - 0x30;    // Second argument must be a char 1-10. Subtract
        // 0x31 to get int value for array indexing.
        // Refer to ASCII table.
        shipMap->mapArray[coordinate[0]][coordinate[1]] = counter + 0x30;
    }
}

//
char printMenu() {
    
    char playerOption;
    cout << "==========================================" << endl;
    cout << "========== Welcome to Warboats! ==========" << endl;
    cout << "==========================================" << endl;
    cout << "1. Single Player Game" << endl;
    cout << "2. Multi Player Game" << endl;
    cout << "3. Credits" << endl;
    cout << "4. Exit\n" << endl;
    cout << "Enter the number that corresponds to the game mode: " << endl;
    cin >> playerOption;
    bool isValid = validateInput(playerOption);
    while(!isValid) {
        cout << "Incorrect game mode input. Please try again. " << endl;
        cout << "Enter the number that corresponds to the game mode: " << endl;
        cin >> playerOption;
        isValid = validateInput(playerOption);
    }
    return playerOption;
}

//
bool validateInput(char input) {
    if (input >= '1' && input <= '4') {
        return true;
    }
    else {
        return false;
    }
}

//
void startGame(Player* p2) {
    
    Player* p1 = new Player();
    p1->getName();
    p2->getName();
    cout << endl;
    
    //int turn = 1;
    bool gameOver = false;
    bool turn = false;
    
    char selection;
    bool validSelection = true;
    cout << p1->name << " how do you want to set your ships?" << endl;
    cout << "1. Manual setup" << endl;
    cout << "2. Auto setup" << endl;
    cin >> selection;
    while(validSelection) {
        switch (selection) {
            case '1':
                printMap(*p1);
                cout << endl << "Player 1 Enter Ships: " << endl;
                p1->initializeShips();
                clearScreen();
                validSelection = false;
                break;
            case '2':
                p1->autoInitializeShips();
                validSelection = false;
                break;
            default:
                cout << "Invalid selection, try again." << endl << endl;
                cout << p1->name << " how do you want to set your ships?" << endl;
                cout << "1. Manual setup" << endl;
                cout << "2. Auto setup" << endl;
                cin >> selection;
                break;
        }
    }
    validSelection = true;
    cout << p2->name << " how do you want to set your ships?" << endl;
    cout << "1. Manual setup" << endl;
    cout << "2. Auto setup" << endl;
    cin >> selection;
    while(validSelection) {
        switch (selection) {
            case '1':
                printMap(*p2);
                cout << endl << "Player 2 Enter Ships: " << endl;
                p2->initializeShips();
                clearScreen();
                validSelection = false;
                break;
            case '2':
                p2->autoInitializeShips();
                validSelection = false;
                break;
            default:
                cout << "Invalid selection, try again." << endl << endl;
                cout << p2->name << " how do you want to set your ships?" << endl;
                cout << "1. Manual setup" << endl;
                cout << "2. Auto setup" << endl;
                cin >> selection;
                break;
        }
    }
    
    cout << endl << endl << "BATTLE TO THE DEATH GO!" << endl;
    while(!gameOver){
        if(turn == false){  //p1 turn
            cout << "\n" << p1->name << " make your move." << endl;
            switch (showSubMenu()) {
                case 1:
                    printMap(*p1);
                    break;
                case 2:
                    if(!p1->takeTurn(p2)) {
                        gameOver = endGame(p2);
                    }
                    turn = true;
                    break;
                case 3:
                    cout << "Thanks for playing Warboats!" << endl;
                    gameOver = endGame(p2);
                    exit(9);
                    break;
                default:
                    cout << "Invalid selection, try again." << endl;
                    break;
            }
        }
        else{               //AIturn
            cout << "\n" << p2->name << " make your move." << endl;
            switch (showSubMenu()) {
                case 1:
                    printMap(*p2);
                    break;
                case 2:
                    if(!p2->takeTurn(p1)) {
                        gameOver = endGame(p1);
                    }
                    turn = false;
                    break;
                case 3:
                    cout << "Thanks for playing Warboats!" << endl;
                    gameOver = endGame(p1);
                    exit(9);
                    break;
                default:
                    cout << "Invalid selection, try again." << endl;
                    break;
            }
        }
    }
} //end of 2P game

//
void showCredits() {
    cout << endl;
    cout << "Warboats contributors:" << endl;
    cout << "Evan Waxman" << endl;
    cout << "Andrew Ortega" << endl;
    cout << "Marcus Mills" << endl;
    cout << "Adam Hochberger" << endl;
    cout << "Victor Fan" << endl;
    cout << "Andrew Showen" << endl;
    cout << "Snoop Dogg" << endl;
    cout << endl;
}

//
int showSubMenu() {
    bool goodInput = false;
    int selection = 0;
    string temp = "";
    
    while (!goodInput) {
        
        selection = 0;
        temp = "";
        cout << "1. Show Map" << endl;
        cout << "2. Take Turn" << endl;
        cout << "3. Give Up" << endl;
        cin >> temp;
        cout << endl;
        if (temp.length() < 1 || temp.length() > 1) {
            cout << "Invalid selection! (Input too long)" << endl;
            continue;
        }
        if(isalpha(temp.at(0))) {
            cout << "Invalid selection! (Input was a letter) " << endl;
            continue;
        }
        else {
            selection = atoi(&temp.at(0));
        }
        if(selection < 1 || selection > 3) {
            cout << "Invalid selection! (Input was a number out of the range)" << endl;
            continue;
        }
        else {
            goodInput = true;
        }
    }
    return selection;
}

void clearScreen() {
    cout << string(100, '\n');
}

void startGameAI(Player* p2) {
    
    Player* p1 = new Player();
    p1->getName();
    p2->getName();
    
    int turn = 1;
    bool gameOver = false;
    int turnRand = rand()%2;
    
    while(!gameOver){
        if(turnRand == 0){  //player 1 first
            if(turn % 2 == 0){  //p1 turn
                p1->takeTurn(p2);
            }
            else{               //AIturn
                p2->takeTurn(p1);
            }
            turn++;               //increment turn
        } //end of player1 first
        else{                   //AI 2 first
            if(turn % 2 == 0){  //AI turn
                p2->takeTurn(p1);
            }
            else{               //p1 turn
                p1->takeTurn(p2);
            }
            turn++;             //increment online
        }   //end of AIfirst
    }   //end of gameActive
    
    
    
} //end of 1P game

bool endGame(Player* winner) {
    cout << winner->name << " wins!" << endl;
    cout << "Returning to main menu..." << endl;
    return true;
}


/*******************/
/** PLAYER CLASS **/
/*******************/

//
void Player::playerCreateShip(int shipNumber, int length, map* map) { //Allows user to input ship and checks input
    /* CHANGELOG
     Added in the initial check for whether or not the position is of the right length. (This relenvace of this mainly being
     because a position with length 1 will crash the program out of terminal) After this, it goes through ahd verifies other stipulations
     of the coordinateCheck method. If it does fail, it outputs what the problem was to the user and continues to take input
     */
    
    cout << "What position do you want to put your " << length <<" length ship at? (enter a capital letter and a digit ex: D7): "<< endl;
    string position;
    cin >> position;
    
    while(position.length() > 2 || position.length() < 2 || coordinateCheck(position)) {
        int coordinate[2];
        char column, row;
        
        if (position.length() > 2) {
            cout << "Incorrect Coordinate Input (coordinate too long)" << endl;
        }
        else if (position.length() < 2) {
            cout << "Incorrect Coordinate Input (coordinate too short)" << endl;
        }
        if (coordinateCheck(position) && position.length() == 2) {
            column = position.at(0);
            row = position.at(1);
            
            coordinate[1] = toupper(column) - 0x41;
            coordinate[0] = row - 0x30;
            
            if (isalpha(position.at(0)) == 0 && isdigit(position.at(1)) == 0) {
                cout << "Incorrect Coordinate Input (no letter in the first position, no number in the second position)" << endl;
            }
            else if (isalpha(position.at(0) != 0)) {
                cout << "Incorrect Coordinate Input (no letter in the first position)" << endl;
            }
            else if (isdigit(position.at(1)) == 0) {
                cout << "Incorrect Coordinate Input (no number in the second position)" << endl;
            }
            else if ((coordinate[0] > 9 || coordinate[0] < 0) || (coordinate[1] > 9 || coordinate[1] < 0)) {
                cout << "Incorrect Coordinate Input (letter not found on the map)" << endl;
            }
            else {
                break;
            }
        }
        cout << "What position do you want to put your " << length <<" length ship at? (enter a capital letter and a digit ex: D7): "<< endl;
        cin >> position;
    }
    
    cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
    string orientation;
    cin >> orientation;
    
    while(orientation != "right" && orientation != "left" && orientation != "up" && orientation != "down") {
        cout << "Incorrect Orientation Input" << endl;
        
        cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
        cin >> orientation;
    }
    
    while(intersectionCheck(position, orientation, length, map) || boundaryCheck(position, orientation, length)){
        if (boundaryCheck(position, orientation, length)) {
            cout << "Incorrect Placement (outside of map boundary)" << endl;
        }else if (intersectionCheck(position, orientation, length, map)) {
            cout << "Incorrect Placement (intersection with ship)" << endl;
        }
        cout << "What position do you want to put your " << length <<" length ship at? (enter a capital letter and a digit ex: 'D7'): "<< endl;
        cin >> position;
        
        while(position.length() > 2 || position.length() < 2) {
            cout << "Incorrect Coordinate Input (coordinate too long)" << endl;
            
            cout << "What position do you want to put your " << length <<" length ship at? (Enter a capital letter and a digit ex: 'D7'): "<< endl;
            cin >> position;
        }
        
        //Coordinate check
        
        cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
        cin >> orientation;
        
        while(orientation != "right" && orientation != "left" && orientation != "up" && orientation != "down") {
            cout << "Incorrect Orientation Input" << endl;
            
            cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
            cin >> orientation;
        }
        
    }
    
    ship[shipNumber-1] = new Ship(shipNumber, position, length, orientation);
    placeShip(ship[shipNumber-1], map, shipNumber);
    
}

void Player::autoCreateShip(int shipNumber, int length, map* map) {
    srand((unsigned)time(0));
    int randX = rand() % 9 +1;
    int randY = rand() % 9 +1;
    int randPos = rand() % 3 +1;
    
    
    //DEBUG
    //cout << "pos: " << randX << randY << "dir: " << randPos << endl;
    
    
    string orientation = "up";
    string cord = "";
    switch (randPos) {
        case 0:
            orientation = "up";
            break;
        case 1:
            orientation = "down";
            break;
        case 2:
            orientation = "left";
            break;
        case 3:
            orientation = "right";
            break;
        default:
            break;
    }
    switch (randX) {
        case 0:
            cord = "A";
            break;
        case 1:
            cord = "B";
            break;
        case 2:
            cord = "C";
            break;
        case 3:
            cord = "D";
            break;
        case 4:
            cord = "E";
            break;
        case 5:
            cord = "F";
            break;
        case 6:
            cord = "G";
            break;
        case 7:
            cord = "H";
        case 8:
            cord = "I";
            break;
        case 9:
            cord = "J";
            break;
        default:
            break;
    }
    
    
    
    cord += to_string(randY);
    
    //DEBUG
    //cout << "cord: " << cord << "orientation: " << orientation;
    
    while(intersectionCheck(cord, orientation, length, map) || boundaryCheck(cord, orientation, length)){
        int randX = rand() % 9 +1;
        int randY = rand() % 9 +1;
        int randPos = rand() % 3 +1;
        
        switch (randPos) {
            case 0:
                orientation = "up";
                break;
            case 1:
                orientation = "down";
                break;
            case 2:
                orientation = "left";
                break;
            case 3:
                orientation = "right";
                break;
            default:
                break;
        }
        switch (randX) {
            case 0:
                cord = "A";
                break;
            case 1:
                cord = "B";
                break;
            case 2:
                cord = "C";
                break;
            case 3:
                cord = "D";
                break;
            case 4:
                cord = "E";
                break;
            case 5:
                cord = "F";
                break;
            case 6:
                cord = "G";
                break;
            case 7:
                cord = "H";
            case 8:
                cord = "I";
                break;
            case 9:
                cord = "J";
                break;
            default:
                break;
        }
        cord += to_string(randY);
    }
    
    ship[shipNumber-1] = new Ship(shipNumber, cord, length, orientation);
    placeShip(ship[shipNumber-1], map, shipNumber);
    
}

//Allows each player to individually place their ships
void Player::initializeShips() {
    int sizeArray[5] = {2, 3, 3, 4, 5};
    for(int i = 1; i < 6; i++) {
        playerCreateShip(i, sizeArray[i-1], &shipMap);
        printMap(*this);
    }
}

void Player::autoInitializeShips() {
    int sizeArray[5] = {2, 3, 3, 4, 5};
    for(int i = 1; i < 6; i++) {
        autoCreateShip(i, sizeArray[i-1], &shipMap);
        //printMap(*this);
    }
}

bool Player::takeTurn(Player* otherPlayer) {
    int hit;
    /* CHANGELOG
     Added the small while loop at line 242 to ensure that the length is not below 2 before it separates the components of the string
     Changed the While loop at 671 to fix guessCheck issues
     */
    
    cout << "Enter a coordinate to guess (ex: 'D7'):" << endl;
    
    string position;
    cin >> position;
    
    int coordinate[2];
    char column, row;
    
    while (position.size() < 2) {
        if (position.length() < 2) {
            cout << "Coordinate too short. Enter a coordinate to guess (ex: 'D7'):" << endl;
            cin >> position;
            continue;
        }
    }
    
    column = position.at(0);
    row = position.at(1);
    
    while (position.length() != 2 || coordinateCheck(position) == true || this->guessCheck(position) == true) {
        
        if (position.length() < 2) {
            cout << "Coordinate too short. Enter a coordinate to guess (ex: 'D7'):" << endl;
            cin >> position;
            continue;
        }
        
        else if (position.length() > 2) {
            cout << "Coordinate too long. Enter a coordinate to guess (ex: 'D7'):" << endl;
            cin >> position;
        }
        
        else if (coordinateCheck(position) == true) {
            cout << "Coordinate not in range." << endl;
            
            cout << "Enter a coordinate to guess (ex: 'D7'):" << endl;
            cin >> position;
            
            column = position.at(0);
            row = position.at(1);
        }
        
        else if (this->guessCheck(position) == true) {
            cout << "This coordinate has already been checked." << endl;
            cout << "Enter a coordinate to guess (ex: 'D7'):" << endl;
            
            cin >> position;
        }
        
        else {
            break;
        }
        
    }
    
    column = position.at(0);
    row = position.at(1);
    
    //Sets the positions of the coordinate
    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;
    
    hit = otherPlayer->hitCheck(this, coordinate);
    
    if (hit == 0) {
        clearScreen();
        cout << "You missed :'(" << endl;
    }
    else if (hit == 1) {
        clearScreen();
        cout << "You got a hit!" << endl;
    }
    else if (hit == 2) {
        clearScreen();
        cout << "YOU SUNK A BATTLESHIP!!" << endl;
    }
    else if (hit == 3) {
        clearScreen();
        cout << "YOU WIN!!!" << endl;
    }
    return true;
}


//Method to get player name from console
void Player::getName() {
    cout << "Enter your name: " << endl;
    string placeholder;
    cin >> name;
    std::getline(cin, placeholder);
    name = name + placeholder;
}

// Checks if coordinate was already guessed
bool Player::guessCheck(string position) {
    
    int column = position.at(0);
    int row = position.at(1);
    //Sets the positions of the coordinate
    int coordinate[2];
    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;
    
    if (guessMap.mapArray[coordinate[0]][coordinate[1]] == 'X' || guessMap.mapArray[coordinate[0]][coordinate[1]] == 'O') {    // Only other values for guess map
        return true;
    }
    else {
        return false;
    }
}

// Checks if ship was hit
int Player::hitCheck(Player* otherPlayer, int coordinate[2]) {
    char shot = shipMap.mapArray[coordinate[0]][coordinate[1]];
    bool hasShips = false;
    if (shot == '1' || shot == '2' || shot == '3' || shot == '4' || shot == '5') {
        otherPlayer->guessMap.mapArray[coordinate[0]][coordinate[1]] = 'X';     // Update guess map
        shipMap.mapArray[coordinate[0]][coordinate[1]] = 'X';   // Update guess map
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                char tempPos = shipMap.mapArray[i][j];
                if (tempPos == shot) {
                    return 1; //1 corresponds to hit but not sunk
                }
                if (tempPos == '1' || tempPos == '2' || tempPos == '3' || tempPos == '4' || tempPos == '5') {
                    hasShips = true;
                }
            }
        }
        if (hasShips) {
            int intShot = (int) shot - 49; //get rid of ascii value
            sinkShip(ship[intShot], &shipMap);
            return 2; //sunk
        }
        else {
            return 3; //no more ships (game over)
        }
        
    }
    else {
        otherPlayer->guessMap.mapArray[coordinate[0]][coordinate[1]] = 'O';
        return 0;
    }
}

/*******************/
/**   AI CLASS   **/
/*******************/

//Allows AI to auto place ships
Ship* AI::aiCreateShip(int shipNumber, int length, map* map) {
    
    int randX = rand() % 9 +1;
    int randY = rand() % 9 +1;
    int randPos = rand() % 3 +1;
    
    
    //DEBUG
    //cout << "pos: " << randX << randY << "dir: " << randPos << endl;
    
    
    string orientation = "up";
    string cord = "";
    switch (randPos) {
        case 0:
            orientation = "up";
            break;
        case 1:
            orientation = "down";
            break;
        case 2:
            orientation = "left";
            break;
        case 3:
            orientation = "right";
            break;
        default:
            break;
    }
    switch (randX) {
        case 0:
            cord = "A";
            break;
        case 1:
            cord = "B";
            break;
        case 2:
            cord = "C";
            break;
        case 3:
            cord = "D";
            break;
        case 4:
            cord = "E";
            break;
        case 5:
            cord = "F";
            break;
        case 6:
            cord = "G";
            break;
        case 7:
            cord = "H";
        case 8:
            cord = "I";
            break;
        case 9:
            cord = "J";
            break;
        default:
            break;
    }
    
    
    
    cord += to_string(randY);
    
    //DEBUG
    //cout << "cord: " << cord << "orientation: " << orientation;
    
    while(intersectionCheck(cord, orientation, length, map) || boundaryCheck(cord, orientation, length)){
        int randX = rand() % 9 +1;
        int randY = rand() % 9 +1;
        int randPos = rand() % 3 +1;
        
        switch (randPos) {
            case 0:
                orientation = "up";
                break;
            case 1:
                orientation = "down";
                break;
            case 2:
                orientation = "left";
                break;
            case 3:
                orientation = "right";
                break;
            default:
                break;
        }
        switch (randX) {
            case 0:
                cord = "A";
                break;
            case 1:
                cord = "B";
                break;
            case 2:
                cord = "C";
                break;
            case 3:
                cord = "D";
                break;
            case 4:
                cord = "E";
                break;
            case 5:
                cord = "F";
                break;
            case 6:
                cord = "G";
                break;
            case 7:
                cord = "H";
            case 8:
                cord = "I";
                break;
            case 9:
                cord = "J";
                break;
            default:
                break;
        }
        cord += to_string(randY);
    }
    
    Ship* ship = new Ship(shipNumber, cord, length, orientation);
    placeShip(ship, map, shipNumber);
    
    return ship;
}

//Allows player to choose AI difficulty
void AI::setDifficulty(string difficulty) {
    this->difficulty = difficulty;
}

/*
 //Method for the computer to 'take a turn' automatically
 void AI::takeTurn(map enemyShipMap) {
 int guess[2];
 int coordinateX;
 int coordinateY;
 
 if (difficulty == "Easy") {
 coordinateX = rand() % 10;
 coordinateY = rand() % 10;
 while (guessMap.mapArray[coordinateX][coordinateY] != '~') {
 coordinateX = rand() % 10;
 coordinateY = rand() % 10;
 }
 guess[0] = coordinateX;
 guess[1] = coordinateY;
 
 }
 if (difficulty == "Medium") {
 int potentialList[15][2] = {};
 int c = 0;
 for (int i = 0; i < 10; i++) {
 for (int j = 0; j < 10; j++) {
 if (guessMap.mapArray[i][j] == '*') {
 if (guessMap.mapArray[i][j + 1] == '~') {
 potentialList[c][0] = i;
 potentialList[c][1] = j + 1;
 c++;
 }
 if (guessMap.mapArray[i][j - 1] == '~') {
 potentialList[c][0] = i;
 potentialList[c][1] = j - 1;
 c++;
 }
 if (guessMap.mapArray[i + 1][j] == '~') {
 potentialList[c][0] = i + 1;
 potentialList[c][1] = j;
 c++;
 }
 if (guessMap.mapArray[i - 1][j] == '~') {
 potentialList[c][0] = i - 1;
 potentialList[c][1] = j;
 c++;
 }
 
 }
 }
 }
 
 
 if (potentialList[0][0] == 0) {
 coordinateX = rand() % 10;
 coordinateY = rand() % 10;
 while (guessMap.mapArray[coordinateX][coordinateY] != '~') {
 coordinateX = rand() % 10;
 coordinateY = rand() % 10;
 }
 guess[0] = coordinateX;
 guess[1] = coordinateY;
 
 }
 else {
 int counter=0;
 for (int k = 0; k <= 14; k++) {
 if (potentialList[k][0] != 0) {
 counter++;
 }
 }
 int q = rand() % counter;
 guess[0] = potentialList[q][0];
 guess[1] = potentialList[q][1];
 }
 }
 if (difficulty == "Hard") {
 int potentialList[15][2];
 int hiPotentialList[15][2];
 int c = 0;
 int d = 0;
 for (int i = 0; i < 10; i++) {
 for (int j = 0; j <10; j++) {
 if (guessMap.mapArray[i][j] == '*') {
 if (guessMap.mapArray[i][j + 1] == '~') {
 potentialList[c][0] = i;
 potentialList[c][1] = j + 1;
 c++;
 }
 if (guessMap.mapArray[i][j - 1] == '~') {
 potentialList[c][0] = i;
 potentialList[c][1] = j - 1;
 c++;
 }
 if (guessMap.mapArray[i + 1][j] == '~') {
 potentialList[c][0] = i + 1;
 potentialList[c][1] = j;
 c++;
 }
 if (guessMap.mapArray[i - 1][j] == '~') {
 potentialList[c][0] = i - 1;
 potentialList[c][1] = j;
 c++;
 }
 
 
 if (guessMap.mapArray[i][j + 1] == '*') {
 hiPotentialList[c][0] = i;
 hiPotentialList[c][1] = j - 1;
 d++;
 }
 if (guessMap.mapArray[i][j - 1] == '*') {
 hiPotentialList[c][0] = i;
 hiPotentialList[c][1] = j + 1;
 d++;
 }
 if (guessMap.mapArray[i + 1][j] == '*') {
 hiPotentialList[c][0] = i - 1;
 hiPotentialList[c][1] = j;
 d++;
 }
 if (guessMap.mapArray[i - 1][j] == '*') {
 hiPotentialList[c][0] = i + 1;
 hiPotentialList[c][1] = j;
 d++;
 }
 
 }
 }
 }
 if (potentialList[0][0] == 0 && hiPotentialList[0][0] == 0) {
 coordinateX = rand() % 10;
 coordinateY = rand() % 10;
 while (guessMap.mapArray[coordinateX][coordinateY] != '~'&& coordinateX + coordinateY % 2 != 0) {
 coordinateX = rand() % 10;
 coordinateY = rand() % 10;
 }
 guess[0] = coordinateX;
 guess[1] = coordinateY;
 
 }
 else if (hiPotentialList[0][0] != 0) {
 guess[0] = hiPotentialList[0][0];
 guess[1] = hiPotentialList[0][1];
 }
 
 else {
 int counter=0;
 for (int k = 0; k <= 14; k++) {
 if (potentialList[k][0] != 0) {
 counter++;
 }
 }
 int q = rand() % counter;
 guess[0] = potentialList[q][0];
 guess[1] = potentialList[q][1];
 
 
 }
 }
 enemyShipMap.hitCheck(&guessMap, guess);
 }
 */


//Allows the player to set a name for the AI
void AI::getName() {
    name = "Jonathan Liu";
}


/*******************/
/**   MAP CLASS  **/
/*******************/

// Constructor for map object
map::map() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mapArray[i][j] = '~';       // Default map element value is ~
        }
    }
}


/*******************/
/**  SHIP CLASS  **/
/*******************/

//
Ship::Ship(int shipNumber, string position, int l, string orientation)
{
    //Sets the length and initial chunk variable (first position) equal to the respective parameters
    length = l;
    chunk[0] = position;
    
    //Condition of if the orientation of the ship is to be up
    if(orientation.compare("up") == 0)
    {
        //Increments the ship upwards
        char number = position.at(1);
        for(int i = 1; i < length; i++)
        {
            number--;
            chunk[i] = string(1,position.at(0)) + number;
        }
    }
    
    //Condition of if the orientation of the ship is to be down
    if(orientation.compare("down") == 0)
    {
        //Increments the ship downwards
        char number = position.at(1);
        for(int i = 1; i < length; i++)
        {
            number++;
            chunk[i] = string(1,position.at(0)) + number;
        }
    }
    
    //Condition of if the orientation of the ship is to be right
    if(orientation.compare("right") == 0)
    {
        //Increments the ship to the right
        char number = position.at(0);
        for(int i = 1; i < length; i++)
        {
            number++;
            chunk[i] = number + string(1,position.at(1));
        }
    }
    
    //Condition of if the orientation of the ship is to be left
    if(orientation.compare("left") == 0)
    {
        //Increments the ship to the left
        char number = position.at(0);
        for(int i = 1; i < length; i++)
        {
            number--;
            chunk[i] = number + string(1,position.at(1));
        }
    }
    
    //Fills the health array with values equal to the corresponding ship nuber
    for(int i = 0; i < length; i++)
    {
        health[i] = shipNumber;
    }
}

//Method that attempts to shoot a ship at a given coordinate
bool Ship::shot(string coord)
{
    //Searches through the all of theclear ship coordinates of the class
    for(int i = 0; i < length; i++)
    {
        //Compares the coordinates that are being shot with those of where the ship is located
        if(coord.compare(chunk[i]) && health[i] != 0)
        {
            //Health of ship at that point is set to 0 (essentially a dead variable)
            health[i] = 0;
            return true;
        }
    }
    return false;
}

//Statement to see if the ship is still alive
bool Ship::isAlive()
{
    //Sets a count variable
    int count = 0;
    for(int i = 0; i < length; i++)
    {
        //Compounds the count variable based on the values of the health index at that point
        count += health[i];
    }
    
    //After all of the compounding, if the count variable is equal to 0, the ship is confirmed to not be alive
    if(count == 0)
        return false;
    
    //It's alive
    else
        return true;
}
