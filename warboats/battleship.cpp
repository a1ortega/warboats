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





#include "battleship.h"
using namespace std;



/*** MAIN ***/
int main() {
    //Player player1;
    //Player player2;
    
    bool endGame = false;
    
    while(!endGame) {
        int playerOption = printMenu();
        string difficulty = "";
        switch(playerOption) {
            case 1:{
                AI* p2 = new AI();
                cout << endl << "Enter a difficulty for the computer player('HARD' 'MEDIUM' or 'EASY'):";
                cin >> difficulty;
                p2->setDifficulty(difficulty);
                startGame(p2);
            }
                break;
            case 2:{
                Player *p2 = new Player();
                startGame(p2);
            }
                break;
            case 3:{
                showCredits();
            }
                break;
            case 4:{
                endGame = true;
            }
                break;
                
        }
    }
    cout << "Thanks for playing Warboats!" << endl;
    cout << "Press enter to exit." << endl;
    exit(9);
    
    return 0;
}
/***********/

//
int printMenu() {
    
    int playerOption;
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
bool validateInput(int input) {
    if (input >= 1 && input <= 4) {
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
    
    int turn = 1;
    bool gameOver = false;
    int turnRand = rand()%2;
    
    
    cout << endl << endl << "Player 1 Enter Ships: " << endl;
    
    
    p1->initializeShips(p1->shipMap,p1->guessMap);
    
    cout << endl << endl << endl << endl << endl << endl << endl << "Player 2 Enter Ships: " << endl << endl << endl << endl;
    
    p2->initializeShips(p2->shipMap,p2->guessMap);
    
    
    
    
    while(!gameOver){
        if(turnRand == 0){  //player 1 first
            if(turn % 2 == 0){  //p1 turnm
                
                p1->takeTurn(p1->guessMap, p2->shipMap);
            }
            else{               //AIturn
                p2->takeTurn(p2->guessMap, p1->shipMap);
            }
            turn++;               //increment turn
        } //end of player1 first
        else{                   //AI 2 first
            if(turn % 2 == 0){  //AI turn
                p2->takeTurn(p1->guessMap, p2->shipMap);
            }
            else{               //p1 turn
                p1->takeTurn(p2->guessMap, p1->shipMap);
            }
            turn++;             //increment online
        }   //end of AIfirst
    }   //end of gameActive
    
    
    
} //end of 2P game

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
                p1->takeTurn(p1->guessMap, p2->shipMap);
            }
            else{               //AIturn
                p2->takeTurn(p2->guessMap, p1->shipMap);
            }
            turn++;               //increment turn
        } //end of player1 first
        else{                   //AI 2 first
            if(turn % 2 == 0){  //AI turn
                p2->takeTurn(p1->guessMap, p2->shipMap);
            }
            else{               //p1 turn
                p1->takeTurn(p2->guessMap, p1->shipMap);
            }
            turn++;             //increment online
        }   //end of AIfirst
    }   //end of gameActive
    
    
    
} //end of 1P game

//
void showCredits() {
    cout << "Evan Waxman" << endl;
    cout << "Andrew Ortega" << endl;
    cout << "Marcus Mills" << endl;
    cout << "Adam Hochberger" << endl;
    cout << "Victor Fan" << endl;
    cout << "Andrew Showen" << endl;
    cout << "Snoop Dogg" << endl;
}



/*******************/
/** PLAYER CLASS **/
/*******************/

//
Ship* Player::createShip(int shipNumber, int length, map* map) { //Allows user to input ship and checks input
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
        if (intersectionCheck(position, orientation, length, map)) {
            cout << "Incorrect Placement (intersection with ship)" << endl;
        }
        else if (boundaryCheck(position, orientation, length)) {
            cout << "Incorrect Placement (outside of map boundary)" << endl;
        }
        else {
            
        }
        cout << "What position do you want to put your " << length <<" length ship at? (Enter a capital letter and a digit ex: 'D7'): "<< endl;
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
    
    Ship* ship = new Ship(shipNumber, position, length, orientation);
    placeShip(ship, map, shipNumber);
    
    return ship;
}

//Allows each player to individually place their ships
void Player::initializeShips(map playerShips, map playerGuesses) {
    int sizeArray[5] = {2, 3, 3, 4, 5};
    for(int i = 1; i < 6; i++) {
        createShip(i, sizeArray[i-1], &playerShips);
        printMap(playerShips, playerGuesses);
    }
}


/* void Player::placeShips(Player player, map playerShipMap) {
     for(int i=1; i<6; i++) {
         player1.createShip(i, sizeArray[i-1], &player1ships);
         printMap(&player1ships, &player1guesses);
     }
     for(int i=1; i<6; i++) {
         player2.createShip(i, sizeArray[i-1], &player2ships);
         printMap(&player2ships, &player2guesses);
     }
 }
*/

void Player::takeTurn(map playerGuessMap, map enemyShipMap) {
    /* CHANGELOG
     Added the small while loop at line 242 to ensure that the length is not below 2 before it separates the components of the string
     */
    
    printMap(playerGuessMap, enemyShipMap);
    cout << "Enter a coordinate to guess (ex: 'D7'): ";
    
    string position;
    cin >> position;
    
    int coordinate[2];
    char column, row;
    while (position.length() < 2) {
        if (position.length() < 2) {
            cout << "Coordinate too short. Enter a coordinate to guess (ex: 'D7'): " << endl;
            cin >> position;
            continue;
        }
    }
    column = position.at(0);
    row = position.at(1);
    
    while(position.length() > 2) {
        cout << "Incorrect Coordinate Input" << endl;
        
        cout << "Enter a coordinate to guess (ex: 'D7'):  ";
        cin >> position;
        
        while(coordinateCheck(position) == true){
            cout << "Coordinate not in range." << endl;
            
            cout << "Enter a coordinate to guess (ex: 'D7'): ";
            cin >> position;
            
            column = position.at(0);
            row = position.at(1);
            
            //Sets the positions of the coordinate
            coordinate[1] = toupper(column) - 0x41;
            coordinate[0] = row - 0x30;
            
            while (playerGuessMap.guessCheck(coordinate) == true){
                cout << "This coordinate has already been checked. " << endl;
                cout << "Enter a coordinate to guess (ex: 'D7'): " << endl;
                
                cin >> position;
            }
        }
    }
    
    column = position.at(0);
    row = position.at(1);
    
    //Sets the positions of the coordinate
    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;
    
    enemyShipMap.hitCheck(&playerGuessMap, coordinate);
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
        if ((coordinate[1] + length) > 9)
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
        if ((coordinate[0] + length) > 9)
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
        return true;
    }
    else if ((coordinate[0] > 9 || coordinate[0] < 0) || (coordinate[1] > 9 || coordinate[1] < 0)){
        return true;
    }
    else {
        return false;
    }
}

//Method that checks whether or not the guess is on the map. If the guess is already on the map, it returns true
bool guessMapCheck(string position, map* playerGuesses) {
    /* CHANGELOG
     Changed before the meeting of 4-12-17
     Properly checked whether or not a ship was hit without needing to go into double for-loops
     */
    int coordinate[2];
    char column=0;
    char row=0;
    
    if (position.length() < 2) {
        column = position.at(0);
        row = position.at(1);
        return true;
    }
    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;
    int y = coordinate[0];
    int x = coordinate[1];
    
    //Checks to see if the corresponding coordinate has anything other than a wave (meaning symbols relating to a shot/hit/sunk ship)
    //If there is something other than a wave, then the coordinate has been guessed before
    if((strcmp(&playerGuesses->mapArray[y][x], "X") == 0) || (strcmp(&playerGuesses->mapArray[y][x], "O") == 0)){
        return true;
    }
    else {
        return false;
    }
}

//Method that checks to see if the coordinate missed a ship. If it misses a ship, it returns true. Otherwise, false.
bool missedShipHitCheck(string position, map* oppositePlayerShips) {
    /* CHANGELOG
     Changed before the meeting of 4-12-17
     Properly checked whether or not a ship was hit without needing to go into double for-loops
     */
    int coordinate[2];
    char column=0;
    char row=0;
    
    if (position.length() < 2) {
        column = position.at(0);
        row = position.at(1);
        return true;
    }
    
    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;
    
    int y = coordinate[0];
    int x = coordinate[1];
    
    //Checks if the corresponding coordinate is a wave, if so, then the hit missed
    if((strcmp(&oppositePlayerShips->mapArray[y][x], "~") == 0)) {
        return true;
    }
    else {
        //Need to figure out a way to implement the ship-shot method here (if it is the best way to go about this)
        return false;
    }
}

//Method to get player name from console
void Player::getName() {
    
    cout << "Enter your name: " << endl;
    cin >> name;
}


/*******************/
/**   AI CLASS   **/
/*******************/

//Allows AI to auto place ships
Ship* AI::createShip(int shipNumber, int length, map* map) {
    /* CHANGELOG
     *
     *
     */
    
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
    /* CHANGELOG
     *
     *
     */
    this->difficulty = difficulty;
}

//Method for the computer to 'take a turn' automatically
void AI::takeTurn(map enemyShipMap) {
    /* CHANGELOG
     *
     *
     */
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

//Allows the player to set a name for the AI
void AI::getName() {
    /* CHANGELOG
     *
     *
     */
    name = "Jonathan Liu";
}


/*******************/
/**   MAP CLASS  **/
/*******************/

// Constructor for map object
map::map() {
    /* CHANGELOG
     *
     *
     */
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mapArray[i][j] = '~';       // Default map element value is ~
        }
    }
}

// Checks if coordinate was already guessed
bool map::guessCheck(int coordinate[]) {
    /* CHANGELOG
     *
     *
     */
    if(mapArray[coordinate[0]][coordinate[1]] == 'X' || mapArray[coordinate[0]][coordinate[1]] == 'O') {    // Only other values for guess map
        return true;
    }else {
        return false;
    }
}

// Checks if ship was hit
bool map::hitCheck(map *guessMap, int coordinate[2]) {
    /* CHANGELOG
     *
     *
     */
    
    
    if(mapArray[coordinate[0]][coordinate[1]] == '~'){
        guessMap->mapArray[coordinate[0]][coordinate[1]] = 'O';     // Update guess map
        return true;
    }else {
        guessMap->mapArray[coordinate[0]][coordinate[1]] = 'X';     // Update guess map
        return false;
    }
}

// Print mapArray of map
void printMap(map player1ships, map player1guesses) {
    /* CHANGELOG
     *
     *
     */
    cout << "   ------P1 Ships-----  -----P1 Guess------" << endl;
    cout << "   A B C D E F G H I J  A B C D E F G H I J" << endl;
    
    char row_count = '0';
    for (int i = 0; i < player1guesses.size; i++) {
        cout << row_count << "  ";
        for (int j = 0; j < player1guesses.size; j++) {
            cout << player1ships.mapArray[i][j] << " " ;
        }
        cout << " ";
        for(int j=0; j< player1guesses.size; j++){
            cout << player1guesses.mapArray[i][j]<< " ";
        }
        cout << endl;
        row_count++;
    }
}

//
void placeShip(Ship *ship, map *shipMap, char counter) {
    /* CHANGELOG
     *
     *
     */
    
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


/*******************/
/**  SHIP CLASS  **/
/*******************/

//
Ship::Ship(int shipNumber, string position, int l, string orientation)
{
    /* CHANGELOG
     *
     *
     */
    
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
    //Searches through the all of the ship coordinates of the class
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

//int* generateGuess(string difficulty, char** guessMap) {

//}



