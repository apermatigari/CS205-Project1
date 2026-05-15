#include "problem.h"
#include <iostream>
#include <cmath>
#include <utility>
using namespace std;

Problem::Problem() {
    //Change the number of rows and columsn needed to account for puzzle size
    rows = 3;
    columns = 3;
    cost = 0;
    heuristic = 0;
}

Problem::Problem(int puzzle [3][3], int zeroX, int zeroY, int r, int c) {
    //In C++ we can't assign arrays specifically to each other and must do each element one by one
    for(int i = 0; i < 3; ++i) { //Copy over contents to our own array in problem class and copy to inital
        for(int j = 0; j < 3; ++j) {
           array[i][j] = puzzle[i][j];
           inital[i][j] = puzzle[i][j];
        }
    }
    zeroTileX = zeroX;
    zeroTileY = zeroY;
    rows = r;
    columns = c;
    cost = 0;
    heuristic = 0;
}

bool Problem::moveUp() {
    //First it can't move up if its at the top
    if(zeroTileY  == 0) {
        //Cannot move up 
        return false;
    }

    //get num that is above zero tile to swap it
    int replacedValue = array[zeroTileY - 1][zeroTileX];

    //Replace above tile with zero
    array[zeroTileY - 1][zeroTileX] = 0;

    //Replace original zero tile location with replacedValue
    array[zeroTileY][zeroTileX] = replacedValue;

    //Set zeroTile locations
    zeroTileY = zeroTileY - 1; //Move Y up
    zeroTileX = zeroTileX; //But x is kept same

    ++cost;
    return true;
}

bool Problem::moveDown() {
    //First it can't move down if its at the bottom
    if(zeroTileY  == rows - 1) {
        //Cannot move up 
        return false;
    }

    //get num that is below zero tile to swap it
    int replacedValue = array[zeroTileY + 1][zeroTileX];

    //Replace below tile with zero
    array[zeroTileY + 1][zeroTileX] = 0;

    //Replace original zero tile location with replacedValue
    array[zeroTileY][zeroTileX] = replacedValue;

    //Set zeroTile locations
    zeroTileY = zeroTileY + 1; //Move Y down
    zeroTileX = zeroTileX; //But x is kept same

    ++cost;
    return true;
}

bool Problem::moveLeft() {
     //First it can't move left if its at the 0 index for x
    if(zeroTileX  == 0) {
        //Cannot move left
        return false;
    }

    //get num that is left of zero tile to swap it
    int replacedValue = array[zeroTileY][zeroTileX - 1];

    //Replace left tile with zero
    array[zeroTileY][zeroTileX - 1] = 0;

    //Replace original zero tile location with replacedValue
    array[zeroTileY][zeroTileX] = replacedValue;

    //Set zeroTile locations
    zeroTileY = zeroTileY; //Y stays same
    zeroTileX = zeroTileX - 1; // shift x by 1 to left

    ++cost;
    return true;
}

bool Problem::moveRight() {
     //First it can't move right if its at the 2 index for x
    if(zeroTileX  == columns -1) {
        //Cannot move left
        return false;
    }

    //get num that is right of zero tile to swap it
    int replacedValue = array[zeroTileY][zeroTileX + 1];

    //Replace right tile with zero
    array[zeroTileY][zeroTileX + 1] = 0;

    //Replace original zero tile location with replacedValue
    array[zeroTileY][zeroTileX] = replacedValue;

    //Set zeroTile locations
    zeroTileY = zeroTileY; //Y stays same
    zeroTileX = zeroTileX + 1; // shift x by 1 to right

    ++cost;
    return true;
}

int Problem::getCost() const {
    return cost;
}

bool Problem::isGoal(){
    for(int row = 0; row < rows; ++row) {
        for(int col = 0; col < columns; ++ col) {
            if(goal[row][col] != array[row][col]) {
                return false;
            }
        }
    }
    return true;
}

void Problem::printArray() const {
    for(int r = 0; r < 3; ++r) {
        for(int c = 0; c < 3; ++c) {
            cout << array[r][c] << " ";
        }
        cout << endl;
    }
}

int Problem::numMisplacedTiles() {
    int misplaced = 0;
    for(int r = 0; r < 3; ++r) {
        for(int c = 0; c < 3; ++c) {
            if(array[r][c] != goal[r][c]) {
                ++misplaced;
            }
        }
    }
    return misplaced;
}

void Problem::setHeuristic(int hVal) {
    heuristic = hVal;
}

int Problem::getHeurisitc() const {
    return heuristic;
}

//Overloading Operators for priority Queue
bool Problem::operator< (const Problem& copy) const {
    //Overload this comparison operator to make it so it takes the smallest of the two
    return (heuristic+ cost) > (copy.heuristic + copy.cost);
}

// helper function for euclidean algorithm to find the coordinates for a specific num tile
pair<int, int> Problem::goalCoordinates(int puzzleNum) {
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 3; column++) {
            if(goal[row][column] == puzzleNum) { // returns the goal coordinate for the number provided
                return {row, column};
            }
        }
    }
    return {-1, -1};   // return if number is not part of the 8-puzzle (not 0-8), 0 will be excluded for
                        // Euclidean calculation in the actual function
}

//uses Euclidean algorithm for finding heuristic.
double Problem::computeEuclideanHeuristic() {
    // the function must be double since we are dealing with sqrt and there will be decimals
    double totalHueristic = 0.0;

    for (int currentRow = 0; currentRow < 3; currentRow++) {
        for (int currentColumn = 0; currentColumn < 3; currentColumn++) {
            // save the numbers from the array in an int in order to use the helper later
            int puzzleNum = array[currentRow][currentColumn];
            if (puzzleNum != 0) { // exclude the 0 tile
            // user helper function to get the goal coordinates for the number in the puzzle
                pair<int, int> correctAllocation = goalCoordinates(puzzleNum);
                // .first gets the x value, .second gets the y 
                int goalRow = correctAllocation.first;
                int goalColumn = correctAllocation.second;

                // Euclidean distance formula 
               totalHueristic += sqrt(pow(goalRow - currentRow, 2) + pow(goalColumn - currentColumn, 2));
            }
        }
    }
    return totalHueristic;
}