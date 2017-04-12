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

#ifndef map_h
#define map_h

#include "battleship.h"
using namespace std;

int main() {
    map player1ships;
    map player2ships;
    map player1guesses;
    map player2guesses;

    Player player1;
    Player player2;

    bool endGame = false;

    while(!endGame) {
        int playerOption = printMenu();

        switch(playerOption) {
            case 1:
                start1pGame();
                break;
            case 2:
                start2pGame();
                break;
            case 3:
                showCredits();
                break;
            case 4:
                endGame = true;
                break;
        }
    }
    cout << "Thanks for playing Warboats!" << endl;
    cout << "Press enter to exit." << endl;
    exit(9);
/*
    Ship ship1(1, "D5", 5, "right");
    placeShip(&ship1, &player1ships, '1');
    printMap(&player1ships, &player1guesses);
 */
    return 0;
}

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

bool validateInput(int input) {
    if (input >= 1 && input <= 4) {
        return true;
    }
    else {
        return false;
    }
}

void start1pGame() {
    Player* p1 = new Player();
    p1->getName();
    AI* p2 = new AI();
    p2->getName();
}

void start2pGame() {
    Player* p1 = new Player();
    p1->getName();
    Player* p2 = new Player();
    p2->getName();
}

void showCredits() {
    cout << "Evan Waxman" << endl;
    cout << "Andrew Ortega" << endl;
    cout << "Marcus Mills" << endl;
    cout << "Adam Hochberger" << endl;
    cout << "Victor Fan" << endl;
    cout << "Andrew Showen" << endl;
    cout << "Snoop Dogg" << endl;
}
  ////////////////////
 /// PLAYER CLASS ///
////////////////////

Ship* Player::createShip(int shipNumber, int length, map* map) {
    cout << "What position do you want to put your " << length <<" length ship at? (enter a capital letter and a digit ex: D7): "<< endl;
    string position;
    cin >> position;

    while(position.length() > 2 || position.length() < 2) {
        cout << "Incorrect Coordinate Input" << endl;

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
        cout << "Incorrect Placement" << endl;

        cout << "What position do you want to put your " << length <<" length ship at? (Enter a capital letter and a digit ex: 'D7'): "<< endl;
        cin >> position;

        while(position.length() > 2 || position.length() < 2) {
            cout << "Incorrect Coordinate Input" << endl;

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
void Player::initializeShips(map* playerShips, map* playerGuesses) {
    int sizeArray[5] = {2, 3, 3, 4, 5};
    for(int i = 1; i < 6; i++) {
        createShip(i, sizeArray[i-1], playerShips);
        printMap(playerShips, playerGuesses);
    }
}
/*
void Player::placeShips(Player player, map playerShipMap) {
    for(int i=1; i<6; i++) {
        player1.createShip(i, sizeArray[i-1], &player1ships);
        printMap(&player1ships, &player1guesses);
    }

    for(int i=1; i<6; i++) {
        player2.createShip(i, sizeArray[i-1], &player2ships);
        printMap(&player2ships, &player2guesses);
    }
} */
void Player::takeTurn(map playerGuessMap, map playerShipMap, map enemyShipMap){

    printMap(&playerGuessMap, &playerShipMap);
    cout << "Enter a coordinate to guess (ex: 'D7'): ";

    string position;
    cin >> position;

    int coordinate[2];
    char column, row;

    column = position.at(0);
    row = position.at(1);

    while(position.length() > 2 || position.length() < 2) {
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

bool boundaryCheck(string position, string orientation, int length) {
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


    if(orientation == "left")
    {
        if ((coordinate[1] - length) < 0)
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
        if ((coordinate[1] + length) > 10)
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
        if ((coordinate[0] - length) < 0)
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
        if ((coordinate[0] + length) > 10)
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

bool intersectionCheck(string position, string orientation, int length, map *map) {
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

    for(int i=0; i<length; i++) {
        if(map->mapArray[coordinate[0]][coordinate[1]] != '~') {
            return true;
        }
        coordinate[1]++;
    }
    return false;
}

//Edit: the next three methods have not been tested with compilation, I edited it from github. Fixing any errors should be painless
//Method that returns true if a coordinate is no longer valid, but false if the coordinate is a valid option
bool coordinateCheck(string position) {
    int coordinate[2];
    char column, row;

    column = position.at(0);
    row = position.at(1);

    //Sets the positions of the coordinate
    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;

    if ((coordinate[0] > 9 || coordinate[0] < 0) || (coordinate[1] > 9 || coordinate[1] < 0)) {
            return true;
    }
    else {
        return false;
    }
}

//Method that checks whether or not the guess is on the map. If the guess is already on the map, it returns true
bool guessMapCheck(string position, map* playerGuesses) {
    int coordinate[2];
    char column, row;

    column = position.at(0);
    row = position.at(1);

    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;

    int y = coordinate[0];
    int x = coordinate[1];
 
    //Checks to see if the corresponding coordinate has anything other than a wave (meaning symbols relating to a shot/hit/sunk ship)
    //If there is something other than a wave, then the coordinate has been guessed before
    if(strcmp(&playerGuesses->mapArray[y][x], "~") != 0) {
        return true;
    }
    else {
        return false;
    }
}


//Method that checks to see if the coordinate missed a ship. If it collides with a ship, it returns false. Otherwise it misses and
//returns true
bool missedShipHitCheck(string position, map* oppositePlayerShips) {
    int coordinate[2];
    char column, row;

    column = position.at(0);
    row = position.at(1);

    coordinate[1] = toupper(column) - 0x41;
    coordinate[0] = row - 0x30;

    int y = coordinate[0];
    int x = coordinate[1];
 
    //Checks if the corresponding coordinate is a wave, if so, then the hit missed
    if(strcmp(&oppositePlayerShips->mapArray[y][x], "~") == 0) {
        return true;
    }
    else {
    //Need to figure out a way to implement the ship-shot method here (if it is the best way to go about this)
        return false;
    }
 }


int Player::getGuessX() {
    cout << "Enter your guess for the x coordinate: " << endl;
    int x;
    cin >> x;

    return x;
}

int Player::getGuessY() {

    cout << "Enter your guess for the y coordinate: " << endl;
    int y;
    cin >> y;

    return y;
}

void Player::getName() {

    cout << "Enter your name: " << endl;
    cin >> name;
}

  ////////////////////
 ///   AI CLASS  z ///
////////////////////

Ship* AI::createShip(int shipNumber, int length, map* map) {

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

void AI::getName() {
    name = "Jonathan Liu";
}

  ////////////////////
 ///   MAP CLASS  ///
////////////////////

// Constructor for map object
map::map() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mapArray[i][j] = '~';       // Default map element value is ~
        }
    }
}

// Checks if coordinate was already guessed
bool map::guessCheck(int coordinate[]) {
    if(mapArray[coordinate[0]][coordinate[1]] == 'X' || mapArray[coordinate[0]][coordinate[1]] == 'O') {    // Only other values for guess map
        return true;
    }else {
        return false;
    }
}

// Checks if ship was hit
bool map::hitCheck(map *guessMap, int coordinate[2]) {
    if(mapArray[coordinate[0]][coordinate[1]] == '~'){
        guessMap->mapArray[coordinate[0]][coordinate[1]] = 'O';     // Update guess map
        return true;
    }else {
        guessMap->mapArray[coordinate[0]][coordinate[1]] = 'X';     // Update guess map
        return false;
    }
}

// Print mapArray of map
void printMap(map *player1ships, map *player1guesses) {
    cout << "   ------P1 Ships-----  -----P1 Guess------" << endl;
    cout << "   A B C D E F G H I J  A B C D E F G H I J" << endl;

    char row_count = '0';
    for (int i = 0; i < player1guesses->size; i++) {
        cout << row_count << "  ";
        for (int j = 0; j < player1guesses->size; j++) {
            cout << player1ships->mapArray[i][j] << " " ;
        }
        cout << " ";
        for(int j=0; j< player1guesses->size; j++){
            cout << player1guesses->mapArray[i][j]<< " ";
        }
        cout << endl;
        row_count++;
    }
}

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

  ////////////////////
 ///  SHIP CLASS  ///
////////////////////

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

#endif


/*
int mediumGuess(char board[], char ships){

    int remainingShips[28];
      int numHitMiss =0;
    for(int i = 0; i!=100; i++){
            if(board[i]=='$'||board[i]=='X'){
                numHitMiss++;
            }
    }
        int numRem=0;
    for(int i = 0; i!=100; i++){
        if(board[i]=='+'){
            remainingShips[numRem] =i;
            numRem++;
        }
    }

     int rando=  rand()%30;
     //   std::cout<<rand<<std::endl;
        // probability of hit
        // roll dice
    if(rando<numHitMiss-numRem/4){
        rando = rand()%numRem;
        return remainingShips[rando];
    }
}





int[] generateguess(str difficulty, string[][]guessMap) {
	if (difficulty == Easy) {
		int coordinateX = rand() % 10;
		int coordinateY = rand() % 10;
		int guess[2];
			while (guessMap[coordinateX][coordinateY]!=~) {
				int coordinateX = rand() % 10;
				int coordinateY = rand() % 10;
			}
			int guess[0] = coordinateX;
			int guess[1] = coordinateY;


	}
	if (difficulty == Medium) {
		int guess[2];
		int[][] potentialList = new int [15][2];
		int c = 0;
		for (int i = 0; i < guessMap.size; i++) {
			for (int j = 0; j < guessMap[i].size; j++) {
				if (guessMap[i][j] = "*") {
					if (guessMap[i][j + 1] == "~") {
						potentialList[c][0] = i;
						potentialList[c][1] = j + 1;
						c++;
					}
					if (guessMap[i][j -1] == "~") {
						potentialList[c][0] = i;
						potentialList[c][1] = j -1;
						c++;
					}
					if (guessMap[i+1][j] == "~") {
						potentialList[c][0] = i+1;
						potentialList[c][1] = j ;
						c++;
					}
					if (guessMap[i-1][j] == "~") {
						potentialList[c][0] = i-1;
						potentialList[c][1] = j ;
						c++;
					}

				}
			}
		}


		if (potentialList[0][0]==NULL){
		int coordinateX = rand() % 10;
		int coordinateY = rand() % 10;
		while (guessMap[coordinateX][coordinateY] != "~") {
			int coordinateX = rand() % 10;
			int coordinateY = rand() % 10;
		}
		int guess[0] = coordinateX;
		int guess[1] = coordinateY;

	}
		else {
			int counter;
			for (int k = 0; k <= 14; k++) {
				if (potentialList[k][0]!=NULL) {
					counter++;
				}
			}
			int q = rand() % counter;
			guess[0] = potentialList[q][0];
			guess[1] = potentialList[q][1];
		}


	}
	if (difficulty == Hard) {
		int guess[2];
		int[][] potentialList = new int[15][2];
		int [][] hiPotentialList = new int[15][2];
		int c = 0;
		int d=0;
		for (int i = 0; i < guessMap.size; i++) {
			for (int j = 0; j < guessMap[i].size; j++) {
				if (guessMap[i][j] = "*") {
					if (guessMap[i][j + 1] == "~") {
						potentialList[c][0] = i;
						potentialList[c][1] = j + 1;
						c++;
					}
					if (guessMap[i][j - 1] == "~") {
						potentialList[c][0] = i;
						potentialList[c][1] = j - 1;
						c++;
					}
					if (guessMap[i + 1][j] == "~") {
						potentialList[c][0] = i + 1;
						potentialList[c][1] = j;
						c++;
					}
					if (guessMap[i - 1][j] == "~") {
						potentialList[c][0] = i - 1;
						potentialList[c][1] = j;
						c++;
					}


					if (guessMap[i][j + 1] == "*") {
						hiPotentialList[c][0] = i;
						hiPotentialList[c][1] = j-1;
						d++;
					}
					if (guessMap[i][j-1] == "*") {
						hiPotentialList[c][0] = i;
						hiPotentialList[c][1] = j + 1;
						d++;
					}
					if (guessMap[i+1][j] == "*") {
						hiPotentialList[c][0] = i-1;
						hiPotentialList[c][1] = j;
						d++;
					}
					if (guessMap[i-1][j] == "*") {
						hiPotentialList[c][0] = i+1;
						hiPotentialList[c][1] = j;
						d++;
					}

				}
			}
		}
		if (potentialList[0][0] == NULL && hiPotentialList[0][0]==NULL) {
			int coordinateX = rand() % 10;
			int coordinateY = rand() % 10;
			while (guessMap[coordinateX][coordinateY] != "~"&& coordinateX + coordinateY % 2 != 0) {
				int coordinateX = rand() % 10;
				int coordinateY = rand() % 10;
			}
			int guess[0] = coordinateX;
			int guess[1] = coordinateY;

		}
		else if(hiPotentialList[0][0]!=NULL){
		    guess[0]=hiPotentialList[0][0];
		    guess[1]=hiPotentialList[0][1];
		}

		else  {
			int counter;
			for (int k = 0; k <= 14; k++) {
				if (potentialList[k][0] != NULL) {
					counter++;
				}
			}
			int q = rand() % counter;
			guess[0] = potentialList[q][0];
			guess[1] = potentialList[q][1];


		}
	}
*/
