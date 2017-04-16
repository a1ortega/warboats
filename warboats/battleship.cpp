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
 LATEST CHANGES:
 -Evan Waxman - changed the AI::TakeTurn and startGameAI methods
 */


#include "battleship.h"

using namespace std;

/*** MAIN ***/
int main() {
    bool quit = false;
    char playerOption;
    
    //While you don't want to quit the game, the main loop repeats
    while(!quit) {
        //Get the playerOption from the print menu function
        playerOption = printMenu();
        string difficulty = "";
        switch(playerOption) {
                //Single Player game against AI
            case '1':{
                //Creates a new AI object as p2
                AI* p2 = new AI();
                //Queries the user for difficulty setting of the AI and sets it
                cout << "Enter a difficulty for the computer player ('easy', 'medium', or 'hard'):" << endl;
                cin >> difficulty;
                cout << endl;
                //Input validation
                while (difficultyChecker(difficulty)) {
                    if (difficultyChecker(difficulty)) {
                        cout << "Incorrect input for difficulty. Please try again." << endl;
                        cout << "Enter a difficulty for the computer player ('easy', 'medium', or 'hard'):" << endl;
                        cin >> difficulty;
                        cout << endl;
                    }
                }
                //Sets the difficulty for the AI and calls the function to start a game with an AI
                p2->setDifficulty(difficulty);
                startGameAI(p2);
            }
                break;
            case '2':{
                //Creates a regular player object as p2
                Player *p2 = new Player();
                startGame(p2);
            }
                break;
            case '3':{
                //Shows the credits screen
                showCredits();
            }
                break;
            case '4':{
                //Breaks out of the loop
                quit = true;
                break;
            }
        }
    }
    cout << "Thanks for playing Warboats!" << endl;
    exit(9);
    
    return 0;
}

/*******************/
/**  FUNCTIONS  **/
/*******************/
//Method that returns true if a coordinate is no longer valid, but false if the coordinate is a valid option
bool coordinateCheck(string position) {
    //Creates a 1D array of two coordinate values
    int coordinate[2];
    char column, row;
    
    //If the user enters a coordinate value with 1 or less characters, it returns true
    if (position.length() < 2) {
        return true;
    }
    //Assigns column and row to what they enter
    column = position.at(0);
    row = position.at(1);
    
    //Converts from ASCII to int coordinates
    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;
    
    //Checks to make sure the coordinates are within the specified range
    if (isalpha(column) != 0) {
        if ((coordinate[0] > 9 || coordinate[0] < 0) || (coordinate[1] > 9 || coordinate[1] < 0)){
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return true;
    }
}

//Function that checks to make sure the ships don't overlap
bool intersectionCheck(string position, string orientation, int length, map *map) {
    //Initializes the variables and assigns them to the characters in the string passed into the funciton
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
    
    //Checks to see if the area is clear to the left/right/up/down of the coordinate they enter
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

//Checks to see if the ship will overlap the end of the board
bool boundaryCheck(string position, string orientation, int length) {
    //Initializes variables to the position parameter
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
    
    //Checks to make sure the ship won't be out of bounds on the left/right/up/downi
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

//Checks to make sure they enter a valid difficulty
bool difficultyChecker(string difficulty) {
    if (!(difficulty == "easy" || difficulty == "medium" || difficulty == "hard")) {
        return true;
    }
    return false;
}

//Prints out the guess and ship maps for the player object that is passed into it
void printMap(Player p1) {
    //Displays the name, as well as a key to make the coordinates easier to understand
    cout << p1.name << endl;
    cout << "   -------Ships-------  -------Guess-------" << endl;
    cout << "   A B C D E F G H I J  A B C D E F G H I J" << endl;
    
    char row_count = '0';
    //Prints the character value at each tile on the grid
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

//Sets the characters representing the ship on the map to * to represent that every tile of the ship has been shot and it is fully sunk
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

//Sets the tiles the ship takes up after its initial position and orientation has been set
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

//Prints the main menu screen and returns the mode the user selects
char printMenu() {
    
    char playerOption;
    cout << "==========================================" << endl;
    cout << "========== Welcome to Warboats! ==========" << endl;
    cout << "==========================================\n" << endl;
    cout << "1. Single Player Game" << endl;
    cout << "2. Multi Player Game" << endl;
    cout << "3. Credits" << endl;
    cout << "4. Exit\n" << endl;
    cout << "Enter the number that corresponds to the game mode: " << endl;
    cin >> playerOption;
    cout << endl;
    //Checks that the user inputs a valid option
    bool isValid = validateInput(playerOption);
    while(!isValid) {
        cout << "Incorrect game mode input. Please try again. " << endl;
        cout << "Enter the number that corresponds to the game mode: " << endl;
        cin >> playerOption;
        cout << endl;
        isValid = validateInput(playerOption);
    }
    return playerOption;
}

//Helper function for checking valid input in the main menu screen
bool validateInput(char input) {
    if (input >= '1' && input <= '4') {
        return true;
    }
    else {
        return false;
    }
}

//Main game function loop for a two player game
void startGame(Player* p2) {
    
    //Creates a human player 1 object
    Player* p1 = new Player();
    p1->getName();
    p2->getName();
    cout << endl;
    
    //Variables for tracking the state of the game
    int p1turnsElapsed = 1;
    int p2turnsElapsed = 1;
    bool gameOver = false;
    bool turn = false;
    
    //Variables for checking valid input
    char selection;
    bool validSelection = true;
    
    //Queries player 1 for how they want to set up their ships
    cout << "1. Manual setup" << endl;
    cout << "2. Auto setup" << endl;
    cout << p1->name << ", how do you want to set your ships?" << endl;
    cin >> selection;
    cout << endl;
    //Makes sure the user is entering a valid input at all times
    while(validSelection) {
        switch (selection) {
                //Player 1 places their ships on the map manually
            case '1':
                printMap(*p1);
                cout << endl << "Player 1 Enter Ships: " << endl;
                p1->initializeShips();
                clearScreen();
                validSelection = false;
                break;
                //Player 1 has their ships placed automatically
            case '2':
                p1->autoInitializeShips();
                validSelection = false;
                break;
                //Player 1 entered an invalid option, queries them to select again
            default:
                cout << "Invalid selection, try again." << endl << endl;
                cout << p1->name << " how do you want to set your ships?" << endl;
                cout << "1. Manual setup" << endl;
                cout << "2. Auto setup" << endl;
                cin >> selection;
                cout << endl;
                break;
        }
    }
    //Queries player 2 for how they want to enter their ships
    validSelection = true;
    cout << "1. Manual setup" << endl;
    cout << "2. Auto setup" << endl;
    cout << endl;
    cout << p2->name << ", how do you want to set your ships?" << endl;
    cin >> selection;
    cout << endl;
    while(validSelection) {
        switch (selection) {
                //Player 2 places their ships manually
            case '1':
                printMap(*p2);
                cout << endl << "Player 2 Enter Ships: " << endl;
                p2->initializeShips();
                clearScreen();
                validSelection = false;
                break;
                //Player 2 has their ships placed automatically
            case '2':
                p2->autoInitializeShips();
                validSelection = false;
                break;
                //Players 2 entered an invalid option, queries them to select again
            default:
                cout << "Invalid selection, try again." << endl << endl;
                cout << p2->name << " how do you want to set your ships?" << endl;
                cout << "1. Manual setup" << endl;
                cout << "2. Auto setup" << endl;
                cin >> selection;
                cout << endl;
                break;
        }
    }
    
    //Main Game loop after both players ships have been placed
    cout << endl << endl << "BATTLE TO THE DEATH GO!" << endl;
    //While the game has not ended
    while(!gameOver){
        if(turn == false){  //p1 turn
            cout << "\nTurn " << p1turnsElapsed << ": " << p1->name << " make your move." << endl;
            //Prints the turn menu, asking whether the player wants to display the map, take their turn, or concede the game
            switch (showSubMenu()) {
                    //Prints the players map
                case 1:
                    printMap(*p1);
                    break;
                    //Lets the player gues
                case 2:
                    if(!p1->takeTurn(p2)) {
                        gameOver = endGame(p1, p2turnsElapsed);
                    }
                    turn = true;
                    p1turnsElapsed++;
                    break;
                    //Concedes the game
                case 3:
                    cout << "Thanks for playing Warboats!" << endl;
                    gameOver = endGame(p2, p2turnsElapsed);
                    exit(9);
                    break;
                    //Queries the user for valid input
                default:
                    cout << "Invalid selection, try again." << endl;
                    break;
            }
        }
        else{               //AIturn
            cout << "\nTurn " << p2turnsElapsed << ": " << p2->name << " make your move." << endl;
            switch (showSubMenu()) {
                case 1:
                    printMap(*p2);
                    break;
                case 2:
                    if(!p2->takeTurn(p1)) {
                        gameOver = endGame(p2, p1turnsElapsed);
                    }
                    turn = false;
                    p2turnsElapsed++;
                    break;
                case 3:
                    cout << "Thanks for playing Warboats!" << endl;
                    gameOver = endGame(p1, p1turnsElapsed);
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
    //cout << string(100, '\n');
}

void startGameAI(AI* p2) {
    
    Player* p1 = new Player();
    p1->getName();
    p2->getName();
    
    int turnsElapsed = 1;
    bool gameOver = false;
    bool turn = false;
    
    char selection;
    bool validSelection = true;
    cout << "1. Manual setup" << endl;
    cout << "2. Auto setup" << endl;
    cout << endl;
    cout << p1->name << ", how do you want to set your ships?" << endl;
    cin >> selection;
    cout << endl;
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
                cout << endl;
                break;
        }
    }
    
    p2->initializeAIShips();
    
    cout << endl << endl << "BATTLE TO THE DEATH GO!" << endl;
    while(!gameOver){
        if(turn == false){  //p1 turn
            cout << "\nTurn " << turnsElapsed << ": " << p1->name << " make your move." << endl;
            switch (showSubMenu()) {
                case 1:
                    printMap(*p1);
                    break;
                case 2:
                    if(!p1->takeTurn(p2)) {
                        gameOver = endGame(p1, turnsElapsed);
                    }
                    turn = true;
                    turnsElapsed++;
                    break;
                case 3:
                    cout << "Thanks for playing Warboats!" << endl;
                    gameOver = endGame(p2, turnsElapsed);
                    exit(9);
                    break;
                default:
                    cout << "Invalid selection, try again." << endl;
                    break;
            }
        }else {
            
            if (!p2->takeTurn(p1)) {
                gameOver = endGame(p2, turnsElapsed);
            }
            turn = false;
        }
    }
    
} //end of 1P game

bool endGame(Player* winner, int turnsElapsed) {
    cout << winner->name << " won in " << turnsElapsed << " turn(s)!" << endl;
    cout << "Returning to main menu..." << endl;
    return true;
}


/*******************/
/** PLAYER CLASS **/
/*******************/

//
void Player::createShip(int shipNumber, int length, map* map) { //Allows user to input ship and checks input
    /* CHANGELOG
     Added in the initial check for whether or not the position is of the right length. (This relenvace of this mainly being
     because a position with length 1 will crash the program out of terminal) After this, it goes through ahd verifies other stipulations
     of the coordinateCheck method. If it does fail, it outputs what the problem was to the user and continues to take input
     */
    
    cout << "What position do you want to put your " << length <<" length ship at? (enter a capital letter and a digit ex: D7): "<< endl;
    string position;
    cin >> position;
    cout << endl;
    
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
        cout << endl;
    }
    
    cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
    string orientation;
    cin >> orientation;
    cout << endl;
    
    while(orientation != "right" && orientation != "left" && orientation != "up" && orientation != "down") {
        cout << "Incorrect Orientation Input" << endl;
        
        cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
        cin >> orientation;
        cout << endl;
    }
    
    while(intersectionCheck(position, orientation, length, map) || boundaryCheck(position, orientation, length)){
        if (boundaryCheck(position, orientation, length)) {
            cout << "Incorrect Placement (outside of map boundary)" << endl;
        }else if (intersectionCheck(position, orientation, length, map)) {
            cout << "Incorrect Placement (intersection with ship)" << endl;
        }
        cout << "What position do you want to put your " << length <<" length ship at? (enter a capital letter and a digit ex: 'D7'): "<< endl;
        cin >> position;
        cout << endl;
        
        while(position.length() > 2 || position.length() < 2) {
            cout << "Incorrect Coordinate Input (coordinate too long)" << endl;
            
            cout << "What position do you want to put your " << length <<" length ship at? (Enter a capital letter and a digit ex: 'D7'): "<< endl;
            cin >> position;
            cout << endl;
        }
        
        //Coordinate check
        
        cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
        cin >> orientation;
        cout << endl;
        
        while(orientation != "right" && orientation != "left" && orientation != "up" && orientation != "down") {
            cout << "Incorrect Orientation Input" << endl;
            
            cout << "What orientation do you want to put your ship at? (up, down, left, right)" << endl;
            cin >> orientation;
            cout << endl;
        }
        
    }
    
    ship[shipNumber-1] = new Ship(shipNumber, position, length, orientation);
    placeShip(ship[shipNumber-1], map, shipNumber);
    
}

//Method that allows the player to have ships auto-created for them if they do not want to manually place them
void Player::autoCreateShip(int shipNumber, int length, map* map) {
    
    //Initialization of x, y, and orientation variables for the starting point of the ships
    srand((unsigned)time(0));
    int randX = rand() % 9 +1;
    int randY = rand() % 9 +1;
    int randPos = rand() % 3 +1;
    
    //DEBUG
    //cout << "pos: " << randX << randY << "dir: " << randPos << endl;
    
    /*Initializes the orientation and coordinate variables to default values
     
     */
    string orientation = "up";
    string cord = "";
    
    //Uses a switch statement to designate the orientation of the ship through the previously obtained random position variable
    switch (randPos) {
        case 0:
            //The orientation of the ship is designated as up
            orientation = "up";
            break;
        case 1:
            //The orientation of the ship is designated as down
            orientation = "down";
            break;
        case 2:
            //The orientation of the ship is designated as left
            orientation = "left";
            break;
        case 3:
            //The orientation of the ship is designated as right
            orientation = "right";
            break;
        default:
            break;
    }
    
    //Uses a switch statement to designate the x coordinate of the ship through the previously obtained random position variable
    switch (randX) {
        case 0:
            //The x-coordinate of the ship is an 'A'
            cord = "A";
            break;
        case 1:
            //The x-coordinate of the ship is an 'B'
            cord = "B";
            break;
        case 2:
            //The x-coordinate of the ship is an 'C'
            cord = "C";
            break;
        case 3:
            //The x-coordinate of the ship is an 'D'
            cord = "D";
            break;
        case 4:
            //The x-coordinate of the ship is an 'E'
            cord = "E";
            break;
        case 5:
            //The x-coordinate of the ship is an 'F'
            cord = "F";
            break;
        case 6:
            //The x-coordinate of the ship is an 'G'
            cord = "G";
            break;
        case 7:
            //The x-coordinate of the ship is an 'H'
            cord = "H";
            break;
        case 8:
            //The x-coordinate of the ship is an 'I'
            cord = "I";
            break;
        case 9:
            //The x-coordinate of the ship is an 'J'
            cord = "J";
            break;
        default:
            break;
    }
    
    
    //Concatenates the previous x-coordinate with the y-coordinate that was randomly generated into a coordinate for the ship to start
    cord += to_string(randY);
    
    //DEBUG
    //cout << "cord: " << cord << "orientation: " << orientation;
    
    //Loop that checks to make sure that the generated coordinate will not intersect with a currently placed ship
    //If a coordinate or orientation does fail, another is generated through the same process as before
    while(intersectionCheck(cord, orientation, length, map) || boundaryCheck(cord, orientation, length)){
        int randX = rand() % 9 +1;
        int randY = rand() % 9 +1;
        int randPos = rand() % 3 +1;
        
        //Uses a switch statement to designate the orientation of the ship through the previously obtained random position variable
        switch (randPos) {
            case 0:
                //The orientation of the ship is designated as up
                orientation = "up";
                break;
            case 1:
                //The orientation of the ship is designated as down
                orientation = "down";
                break;
            case 2:
                //The orientation of the ship is designated as left
                orientation = "left";
                break;
            case 3:
                //The orientation of the ship is designated as right
                orientation = "right";
                break;
            default:
                break;
        }
        
        //Uses a switch statement to designate the x coordinate of the ship through the previously obtained random position variable
        switch (randX) {
            case 0:
                //The x-coordinate of the ship is an 'A'
                cord = "A";
                break;
            case 1:
                //The x-coordinate of the ship is an 'B'
                cord = "B";
                break;
            case 2:
                //The x-coordinate of the ship is an 'C'
                cord = "C";
                break;
            case 3:
                //The x-coordinate of the ship is an 'D'
                cord = "D";
                break;
            case 4:
                //The x-coordinate of the ship is an 'E'
                cord = "E";
                break;
            case 5:
                //The x-coordinate of the ship is an 'F'
                cord = "F";
                break;
            case 6:
                //The x-coordinate of the ship is an 'G'
                cord = "G";
                break;
            case 7:
                //The x-coordinate of the ship is an 'H'
                cord = "H";
                break;
            case 8:
                //The x-coordinate of the ship is an 'I'
                cord = "I";
                break;
            case 9:
                //The x-coordinate of the ship is an 'J'
                cord = "J";
                break;
            default:
                break;
        }
        //Concatenates the previous x-coordinate with the y-coordinate that was randomly generated into a coordinate for the ship to start
        cord += to_string(randY);
    }
    
    //After a valid point and orientation is successfully generated, a ship of a corresponding number is created.
    ship[shipNumber-1] = new Ship(shipNumber, cord, length, orientation);
    
    //After the ship is created, it is then placed on the map.
    placeShip(ship[shipNumber-1], map, shipNumber);
    
}

//Allows each player to individually place their ships
void Player::initializeShips() {
    
    //Array containing the various ship sizes for the createShip's reference
    int sizeArray[5] = {2, 3, 3, 4, 5};
    
    //For loop that goes through and creates 5 ships of corresponding sizes
    for(int i = 1; i < 6; i++) {
        
        //For loop that goes through and creates 5 ships of corresponding sizes
        createShip(i, sizeArray[i-1], &shipMap);
        
        //Outputs a map for the player after each ship is created based on their new ship map
        printMap(*this);
    }
}

//Allows the player to randomly create ships and then automatically place them
void Player::autoInitializeShips() {
    
    //Array containing the various ship sizes for the createShip's reference
    int sizeArray[5] = {2, 3, 3, 4, 5};
    
    //For loop that goes through and creates 5 ships of corresponding sizes
    for(int i = 1; i < 6; i++) {
        //For loop that goes through and creates 5 ships of corresponding sizes
        autoCreateShip(i, sizeArray[i-1], &shipMap);
        
        //DEBUG
        //printMap(*this);
    }
}

/*Method that allows a player to take their turn (guessing and checking if the coordinate was valid/hit a ship) and returns if the
 turn was successful (meaning the game is not over)
 */
bool Player::takeTurn(Player* otherPlayer) {
    
    //Initialization of coordinate array, column and row characters, hit number, and the position of the coordinate
    int coordinate[2];
    char column, row;
    int hit;
    string position;
    
    //Output statement that prompts the user to enter a coordinate and then take in their input
    cout << "Enter a coordinate to guess (ex: 'D7'):" << endl;
    cin >> position;
    cout << endl;
    
    /*While loop that checks the length of the inputted position before changing the column and row variables to the
     first and second positions respectively. This is done to prevent the row variable from accessing a null part of the string
     and crasing the terminal client/compiler
     */
    while (position.size() < 2) {
        
        /*If the current position is too short, it prompts the user to enter a new one.
         If it still to short, it continues the while loop.
         */
        if (position.length() < 2) {
            
            cout << "Coordinate too short. Enter a coordinate to guess (ex: 'D7'):" << endl;
            cin >> position;
            cout << endl;
            continue;
        }
        
        //Once the size of the position string is at least 2, it leaves this while loop and goes through the method
    }
    
    //The column and row variables are set to the first and second parts of the position string, respectively (to be broken down later)
    column = position.at(0);
    row = position.at(1);
    
    /* While loop that verifies that the length of the position string is 2, the coordinate being guessed is a valid coordinate
     (meaning from A-J, and 0-9), and that it has not been guessed previously by the same player. Within the while loop,
     if the player's inputted position fails to meet any given criteria, it is put through a series of if statements that seek
     to remedy the problem's individually
     */
    while (position.length() != 2 || coordinateCheck(position) == true || this->guessCheck(position) == true) {
        
        //Secondary check for if the position length is going be less than 2 and with a reprompt for the user
        if (position.length() < 2) {
            cout << "Coordinate too short. Enter a coordinate to guess (ex: 'D7'):" << endl;
            cin >> position;
            cout << endl;
            continue;
        }
        
        //Checks to see if the length of the string is greater than 2 (meaning that it is not a valid coordinate)
        else if (position.length() > 2) {
            cout << "Coordinate too long. Enter a coordinate to guess (ex: 'D7'):" << endl;
            cin >> position;
            cout << endl;
        }
        
        /*Checks to see if the coordinate is valid, if coordinateCheck(position) == true (meaning there is an error), the user is prompted to
         enter a coordinate that is in the range
         */
        else if (coordinateCheck(position) == true) {
            cout << "Coordinate not in range." << endl;
            
            cout << "Enter a coordinate to guess (ex: 'D7'):" << endl;
            cin >> position;
            cout << endl;
            
            column = position.at(0);
            row = position.at(1);
        }
        
        //Checks to see if the coordinate has been guessed before, if guessCheck(position) == true (meaning there is an error), the user
        //is prompted to enter a coordinate that is original
        else if (this->guessCheck(position) == true) {
            cout << "This coordinate has already been checked." << endl;
            cout << "Enter a coordinate to guess (ex: 'D7'):" << endl;
            
            cin >> position;
            cout << endl;
        }
        
        else {
            break;
        }
        
    }
    
    //Sets the column and row variables to the newly-defined valid coordinates
    column = position.at(0);
    row = position.at(1);
    
    //Sets the positions of the coordinate based upon the column and row conversions to numbers through their ASCII value
    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;
    
    //Checks the hit's type through the hitCheck method
    hit = otherPlayer->hitCheck(this, coordinate);
    
    //If hit == 0, it is a miss and then that is read out to the user
    if (hit == 0) {
        clearScreen();
        cout << "You missed :'(" << endl;
        cout << endl;
        cout << endl;
        
    }
    
    //If hit == 1, it is a hit and then that is read out to the user
    else if (hit == 1) {
        clearScreen();
        cout << "You got a hit!" << endl;
        cout << endl;
        cout << endl;
        
    }
    
    //If hit == 2, it is a hit that sunk the battleship and then that is read out to the user
    else if (hit == 2) {
        clearScreen();
        cout << "YOU SUNK A BATTLESHIP!!" << endl;
        cout << endl;
        cout << endl;
        
    }
    
    //If hit == 3, it is a hit that sunk the last battleship and then the user is told that they won. Also returns false showing there are
    //no more turns possible
    else if (hit == 3) {
        clearScreen();
        cout << "YOU WIN!!!" << endl;
        return false;
    }
    
    //Returns true because no one won because of this turn, meaning that the game is still going
    return true;
}


//Method to get player name from console
void Player::getName() {
    cout << "Enter your name: " << endl;
    string placeholder;
    cin >> name;
    cout << endl;
    getline(cin, placeholder);
    name = name + placeholder;
}

//Checks if coordinate was already guessed, returns true if it was, false otherwise
bool Player::guessCheck(string position) {
    
    //Initializes the column and row variables to be the first two parts of the position string that was inputted
    int column = position.at(0);
    int row = position.at(1);
    
    
    //Sets the coordinate to be equal to the parts of the position converted through their ASCII values
    int coordinate[2];
    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;
    
    //Checks if the guessMap has a coordinate on its mapArray that has the 'X', 'O', or '*' characters meaning it has been guessed before
    if (guessMap.mapArray[coordinate[0]][coordinate[1]] == 'X' || guessMap.mapArray[coordinate[0]][coordinate[1]] == 'O' || guessMap.mapArray[coordinate[0]][coordinate[1]] == '*') {
        return true;
    }
    else {
        
        //Returns false if there was no error with the inputted coordinate
        return false;
    }
}

//Checks if ship was hit
int Player::hitCheck(Player* otherPlayer, int coordinate[2]) {
    
    //Initializes a character to be the corresponding number to the ship at the desired coordinate
    char shot = shipMap.mapArray[coordinate[0]][coordinate[1]];
    
    //Bool variable to check whether or not the player has ships sunk
    bool hasShips = false;
    
    //Checks if the shot character "hit" a ship, by comparing its value to those of each possible ship
    if (shot == '1' || shot == '2' || shot == '3' || shot == '4' || shot == '5') {
        
        //Sets the corresponding values for your shipMap and the other person's guessMap to an 'X' because a ship was hit
        otherPlayer->guessMap.mapArray[coordinate[0]][coordinate[1]] = 'X';
        shipMap.mapArray[coordinate[0]][coordinate[1]] = 'X';
        
        //For loop that checks if the ships in your map have been sunk, if any are still alive, then it returns true
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
        
        //If there are ships, it sinks the corresponding ship (based on number) once they have all turned to
        if (hasShips) {
            int intShot = (int) shot - 49;
            sinkShip(ship[intShot], &shipMap);
            sinkShip(ship[intShot], &otherPlayer->guessMap);
            return 2; //sunk ship
        }
        else {
            return 3; //no more ships (game over)
        }
        
    }
    else {
        
        //Missed hit
        otherPlayer->guessMap.mapArray[coordinate[0]][coordinate[1]] = 'O';
        shipMap.mapArray[coordinate[0]][coordinate[1]] = 'O';
        return 0;
    }
}

/*******************/
/**   AI CLASS   **/
/*******************/

//Initializes ships for the AI through a for loop
void AI::initializeAIShips() {
    
    //Array containing the lengths of each ship
    int sizeArray[5] = { 2, 3, 3, 4, 5 };
    
    //Loop that goes through and creates each ship through the parameters of shipNumber, length, and map
    for (int i = 1; i < 6; i++) {
        createShip(i, sizeArray[i - 1], &shipMap);
    }
}

//Allows AI to auto place ships
void AI::createShip(int shipNumber, int length, map* map) {
    
    //Initializes the x, y, and position variables to random values
    int randX = rand() % 10;
    int randY = rand() % 10;
    int randPos = rand() % 4;
    
    
    //DEBUG
    //cout << "pos: " << randX << randY << "dir: " << randPos << endl;
    
    //Initializes the orientation and cord variables
    string orientation = "up";
    string cord = "";
    
    //Uses a switch statement to designate the orientation of the ship through the previously obtained random position variable
    switch (randPos) {
        case 0:
            //The orientation of the ship is designated as up
            orientation = "up";
            break;
        case 1:
            //The orientation of the ship is designated as down
            orientation = "down";
            break;
        case 2:
            //The orientation of the ship is designated as left
            orientation = "left";
            break;
        case 3:
            //The orientation of the ship is designated as right
            orientation = "right";
            break;
        default:
            break;
    }
    
    //Uses a switch statement to designate the x coordinate of the ship through the previously obtained random position variable
    switch (randX) {
        case 0:
            //The x-coordinate of the ship is an 'A'
            cord = "A";
            break;
        case 1:
            //The x-coordinate of the ship is an 'B'
            cord = "B";
            break;
        case 2:
            //The x-coordinate of the ship is an 'C'
            cord = "C";
            break;
        case 3:
            //The x-coordinate of the ship is an 'D'
            cord = "D";
            break;
        case 4:
            //The x-coordinate of the ship is an 'E'
            cord = "E";
            break;
        case 5:
            //The x-coordinate of the ship is an 'F'
            cord = "F";
            break;
        case 6:
            //The x-coordinate of the ship is an 'G'
            cord = "G";
            break;
        case 7:
            //The x-coordinate of the ship is an 'H'
            cord = "H";
            break;
        case 8:
            //The x-coordinate of the ship is an 'I'
            cord = "I";
            break;
        case 9:
            //The x-coordinate of the ship is an 'J'
            cord = "J";
            break;
        default:
            break;
    }
    
    //Concat
    
    cord += to_string(randY);
    
    //DEBUG
    //cout << "cord: " << cord << "orientation: " << orientation;
    
    //Loop that checks to make sure that the generated coordinate will not intersect with a currently placed ship
    //If a coordinate or orientation does fail, another is generated through the same process as before
    while (intersectionCheck(cord, orientation, length, map) || boundaryCheck(cord, orientation, length)) {
        int randX = rand() % 10;
        int randY = rand() % 10;
        int randPos = rand() % 4;
        
        //Uses a switch statement to designate the orientation of the ship through the previously obtained random position variable
        switch (randPos) {
            case 0:
                //The orientation of the ship is designated as up
                orientation = "up";
                break;
            case 1:
                //The orientation of the ship is designated as down
                orientation = "down";
                break;
            case 2:
                //The orientation of the ship is designated as left
                orientation = "left";
                break;
            case 3:
                //The orientation of the ship is designated as right
                orientation = "right";
                break;
            default:
                break;
        }
        
        //Uses a switch statement to designate the x coordinate of the ship through the previously obtained random position variable
        switch (randX) {
            case 0:
                //The x-coordinate of the ship is an 'A'
                cord = "A";
                break;
            case 1:
                //The x-coordinate of the ship is an 'B'
                cord = "B";
                break;
            case 2:
                //The x-coordinate of the ship is an 'C'
                cord = "C";
                break;
            case 3:
                //The x-coordinate of the ship is an 'D'
                cord = "D";
                break;
            case 4:
                //The x-coordinate of the ship is an 'E'
                cord = "E";
                break;
            case 5:
                //The x-coordinate of the ship is an 'F'
                cord = "F";
                break;
            case 6:
                //The x-coordinate of the ship is an 'G'
                cord = "G";
                break;
            case 7:
                //The x-coordinate of the ship is an 'H'
                cord = "H";
                break;
            case 8:
                //The x-coordinate of the ship is an 'I'
                cord = "I";
                break;
            case 9:
                //The x-coordinate of the ship is an 'J'
                cord = "J";
                break;
            default:
                break;
        }
        cord += to_string(randY);
    }
    //After a valid point and orientation is successfully generated, a ship of a corresponding number is created.
    ship[shipNumber - 1] = new Ship(shipNumber, cord, length, orientation);
    
    //After the ship is created, it is then placed on the map.
    placeShip(ship[shipNumber - 1], map, shipNumber);
}

//Allows player to choose AI difficulty
void AI::setDifficulty(string difficulty) {
    this->difficulty = difficulty;
}

//Method for the computer to 'take a turn' automatically
bool AI::takeTurn(Player* p2) {
    int hit;
    cout << "Computer's turn" << endl;
    //printMap(*this);
    int guess[2];
    int coordinateX;
    int coordinateY;
    if (this->difficulty.compare("easy") == 0) {
        coordinateX = rand() % 10;
        coordinateY = rand() % 10;
        while (guessMap.mapArray[coordinateX][coordinateY] != '~') {
            
            coordinateX = rand() % 10;
            coordinateY = rand() % 10;
            //cout << coordinateX << endl;
            //cout << coordinateY << endl;
            
        }
        
        guess[0] = coordinateX;
        guess[1] = coordinateY;
        
    }
    if (this->difficulty.compare("medium") == 0) {
        int potentialList[70][2] = {};
        int c = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (guessMap.mapArray[i][j] == 'X') {
                    if (j < 9 && guessMap.mapArray[i][j + 1] == '~') {
                        potentialList[c][0] = i;
                        potentialList[c][1] = j + 1;
                        c++;
                    }
                    if (j > 0 && guessMap.mapArray[i][j - 1] == '~') {
                        potentialList[c][0] = i;
                        potentialList[c][1] = j - 1;
                        c++;
                    }
                    if (i < 9 && guessMap.mapArray[i + 1][j] == '~') {
                        potentialList[c][0] = i + 1;
                        potentialList[c][1] = j;
                        c++;
                    }
                    if (i > 0 && guessMap.mapArray[i - 1][j] == '~') {
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
            int counter = 0;
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
    if (this->difficulty.compare("hard") == 0) {
        int potentialList[70][2] = {};
        int hiPotentialList[70][2] = {};
        potentialList[0][0] = 420;
        hiPotentialList[0][0] = 420;
        int c = 0;
        int d = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j <10; j++) {
                if (guessMap.mapArray[i][j] == 'X') {
                    if (j < 9 && guessMap.mapArray[i][j + 1] == '~') {
                        potentialList[c][0] = i;
                        potentialList[c][1] = j + 1;
                        c++;
                    }
                    if (j > 0 && guessMap.mapArray[i][j - 1] == '~') {
                        potentialList[c][0] = i;
                        potentialList[c][1] = j - 1;
                        c++;
                    }
                    if (i < 9 && guessMap.mapArray[i + 1][j] == '~') {
                        potentialList[c][0] = i + 1;
                        potentialList[c][1] = j;
                        c++;
                    }
                    if (i > 0 && guessMap.mapArray[i - 1][j] == '~') {
                        potentialList[c][0] = i - 1;
                        potentialList[c][1] = j;
                        c++;
                    }
                    
                    
                    if (j > 0 && j < 9 && guessMap.mapArray[i][j + 1] == 'X' && guessMap.mapArray[i][j - 1] == '~') {
                        hiPotentialList[d][0] = i;
                        hiPotentialList[d][1] = j - 1;
                        d++;
                    }
                    if (j > 0 && j < 9 && guessMap.mapArray[i][j - 1] == 'X' && guessMap.mapArray[i][j + 1] == '~') {
                        hiPotentialList[d][0] = i;
                        hiPotentialList[d][1] = j + 1;
                        d++;
                    }
                    if (i > 0 && i < 9 && guessMap.mapArray[i + 1][j] == 'X' && guessMap.mapArray[i - 1][j] == '~') {
                        hiPotentialList[d][0] = i - 1;
                        hiPotentialList[d][1] = j;
                        d++;
                    }
                    if (i > 0 && i < 9 && guessMap.mapArray[i - 1][j] == 'X' && guessMap.mapArray[i + 1][j] == '~') {
                        hiPotentialList[d][0] = i + 1;
                        hiPotentialList[d][1] = j;
                        d++;
                    }
                }
            }
        }
        if (potentialList[0][0] == 420) {
            coordinateX = rand() % 10;
            coordinateY = rand() % 10;
            while (guessMap.mapArray[coordinateX][coordinateY] != '~' || (coordinateX + coordinateY) % 2 != 0) {
                coordinateX = rand() % 10;
                coordinateY = rand() % 10;
            }
            guess[0] = coordinateX;
            guess[1] = coordinateY;
        }
        else if (hiPotentialList[0][0] != 420) {
            guess[0] = hiPotentialList[0][0];
            guess[1] = hiPotentialList[0][1];
        }
        
        else {
            int counter = 0;
            for (int k = 0; k <= 69; k++) {
                if (potentialList[k][0] != 0) {
                    counter++;
                }
            }
            int q = rand() % counter;
            guess[0] = potentialList[q][0];
            guess[1] = potentialList[q][1];
        }
    }
    //cout << guess[0] << endl;
    //cout << guess[1] << endl;
    
    hit = p2->hitCheck(this, guess);
    
    if (hit == 0) {
        cout << "They missed!" << endl;
    }
    else if (hit == 1) {
        cout << "They got a hit!" << endl;
    }
    else if (hit == 2) {
        cout << "THEY SUNK YOUR BATTLESHIP!!" << endl;
    }
    else if (hit == 3) {
        cout << "YOU LOST!!!" << endl;
        return false;
    }
    return true;
}


//Accesses a random name from a file called "names.txt"
void AI::getName() {
    srand(time(0));
    string str;
    vector<string> names;
    ifstream file("names.txt");
    int randNum = rand() % (int)278;
    
    if (file.is_open()) {
        while(getline(file, str)) {
            names.push_back(str);
        }
        file.close();
        name = names.at(randNum);
    }
    else {
        name = "Computer";
    }
}

/*******************/
/**   MAP CLASS  **/
/*******************/

// Constructor for map object
map::map() {
    
    //Goes through and fills the 2D array of map with '~' to model waves
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mapArray[i][j] = '~';
        }
    }
}


/*******************/
/**  SHIP CLASS  **/
/*******************/

//Constructor for the ship object
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
            //Sets the chunk array to the correct positions
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
            //Sets the chunk array to the correct positions
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
            //Sets the chunk array to the correct positions
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
            //Sets the chunk array to the correct positions
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
