#include <iostream>
#include <utility>
using namespace std;


class Problem {
    public:
        Problem();
        Problem(int puzzle [3][3], int zeroX, int zeroY, int r, int c); //Change puzzle row and column values accordingly
        int array [3][3]; //Public vairable that stores the current array for the specific problem 
        void printArray() const;
        bool moveUp(); //Moves 0 tile up
        bool moveDown(); // Moves 0 tile down
        bool moveLeft(); //Moves 0 tile left
        bool moveRight(); //Moves 0 tile right
        void setHeuristic(int hVal);
        int getHeurisitc() const;
        bool isGoal();
        int getCost() const;
        int numMisplacedTiles();
        //Overloading Operators for priority queue cause it can't make comparisons with other variables of type Problem
        bool operator<(const Problem& copy) const;
        // Helper function to get Goal coordinates
        pair<int, int> goalCoordinates(int puzzleNum);
        double computeEuclideanHeuristic();
    private:
        int zeroTileX; //x coordinate of the 0 tile
        int zeroTileY; //y coordinate of the 0 tile
        int rows;
        int columns;
        int cost;
        int heuristic;
        int inital[3][3];
        int goal [3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}
        };
};