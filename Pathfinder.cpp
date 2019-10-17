#include "Pathfinder.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;


/*
WARNING: It is expressly forbidden to modify any part of this document, including its name
*/

Pathfinder::Pathfinder() {
    has_maze = false;
    srand(time(NULL));
}
Pathfinder::~Pathfinder() {}

//Part 1-----------------------------------------------------------------------------------
/*
* toString
*
* Returns a string representation of the current maze. Returns a maze of all 1s if no maze
* has yet been generated or imported.
*
* A valid string representation of a maze consists only of 125 1s and 0s (each separated
* by spaces) arranged in five 5x5 grids (each separated by newlines) with no trailing newline. A valid maze must
* also have 1s in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).
*
* Cell (0, 0, 0) is represented by the first number in the string representation of the
* maze. Increasing in x means moving toward the east, meaning cell (1, 0, 0) is the second
* number. Increasing in y means moving toward the south, meaning cell (0, 1, 0) is the
* sixth number. Increasing in z means moving downward to a new grid, meaning cell
* (0, 0, 1) is the twenty-sixth cell in the maze. Cell (4, 4, 4) is represented by the last number.
*
* Returns:		string
*				A single string representing the current maze
*/
string Pathfinder::toString() const {
    stringstream write_to_maze_str;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                if(has_maze)
                    write_to_maze_str << current_maze[i][j][k];
                else
                    write_to_maze_str << 1;
                if(k != 4)
                    write_to_maze_str << " ";
            }
            if((i != 4) || (j != 4)){
                write_to_maze_str << endl;
            }
        }
        write_to_maze_str << endl;
        
    }
    return write_to_maze_str.str();
}

/*
* createRandomMaze
*
* Generates a random maze and stores it as the current maze.
*
* The generated maze must contain a roughly equal number of 1s and 0s and must have a 1
* in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).  The generated maze may be
* solvable or unsolvable, and this method should be able to produce both kinds of mazes.
*/
void Pathfinder::createRandomMaze(){
    
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                current_maze[i][j][k] = rand() % 2;
            }
        }
    }
    current_maze[0][0][0] = 1;
    current_maze[4][4][4] = 1;
    has_maze = true;
}
//-----------------------------------------------------------------------------------------

//Part 2-----------------------------------------------------------------------------------
/*
* importMaze
*
* Reads in a maze from a file with the given file name and stores it as the current maze.
* Does nothing if the file does not exist or if the file's data does not represent a valid
* maze.
*
* The file's contents must be of the format described above to be considered valid.
*
* Parameter:	file_name
*				The name of the file containing a maze
* Returns:		bool
*				True if the maze is imported correctly; false otherwise
*/
bool Pathfinder::importMaze(string file_name){
    
    ifstream maze_file(file_name);
    int zeros_and_ones_count = 0;
    int temp_maze[5][5][5];
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                if(!maze_file.eof()){
                    zeros_and_ones_count += 1;
                }
                //int current_location;
                maze_file >> temp_maze[i][j][k];
                //cout << "cm[" << i << "][" << j << "][" << k << "] = " << current_maze[i][j][k] << endl;
                if((temp_maze[i][j][k] != 0) && (temp_maze[i][j][k] != 1)){
                    maze_file.close();
                    return false;
                } else if((i == 0) && (j == 0) && (k == 0) && (temp_maze[i][j][k] != 1)){ // checks if first spot is valid
                    maze_file.close();
                    return false;
                } else if((i == 4) && (j == 4) && (k == 4) && (temp_maze[i][j][k] != 1)){ // checks if last spot is valid
                    maze_file.close();
                    return false;
                } 
            }
        }
    }
    if(maze_file.eof() == false){
        return false;
    }
    cout << zeros_and_ones_count << endl;
    cout << temp_maze[0][0][0] << endl << temp_maze[4][4][4] << endl;
    if((temp_maze[0][0][0] == 1) && (temp_maze[4][4][4] == 1) && (zeros_and_ones_count == 125)){
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                for(int k = 0; k < 5; k++){
                    current_maze[i][j][k] = temp_maze[i][j][k];
                }
            }
        }
        cout << "made it to where has maze is true" << endl;
        has_maze = true;
        maze_file.close();
        return true;
    }
}
//-----------------------------------------------------------------------------------------

//Part 3-----------------------------------------------------------------------------------
/*
* solveMaze
*
* Attempts to solve the current maze and returns a solution if one is found.
*
* A solution to a maze is a list of coordinates for the path from the entrance to the exit
* (or an empty vector if no solution is found). This list cannot contain duplicates, and
* any two consecutive coordinates in the list can only differ by 1 for only one
* coordinate. The entrance cell (0, 0, 0) and the exit cell (4, 4, 4) should be included
* in the solution. Each string in the solution vector must be of the format "(x, y, z)",
* where x, y, and z are the integer coordinates of a cell.
*
* Understand that most mazes will contain multiple solutions
*
* Returns:		vector<string>
*				A solution to the current maze, or an empty vector if none exists
*/
vector<string> Pathfinder::solveMaze(){
    findPath(0, 0, 0);
    return p;
}

bool Pathfinder::findPath(int x, int y, int z){
    stringstream ss;
    ss << "(" << x << ", " << y << ", " << z << ")";
    p.push_back(ss.str());
    if((x < 0) || (x > 4) || (y < 0) || (y > 4) || (z < 0) || (z > 4)){ // out of bounds
        p.pop_back();
        return false;
    }
    if(current_maze[x][y][z] == 0){ // hit a wall
        p.pop_back();
        return false;
    }
    if(current_maze[x][y][z] == 2){ // been here before
        p.pop_back();
        return false;
    }
    if((x == 4) && (y == 4) && (z == 4)){
        return true;
    }
    
    current_maze[x][y][z] = 2; // mark we've been here
    
    bool down = findPath(x, y, z + 1);
    bool east = findPath(x + 1, y, z);
    bool south = findPath(x, y + 1, z);
    bool west = findPath(x - 1, y, z);
    bool up = findPath(x, y, z - 1);
    bool north = findPath(x, y - 1, z);
    
    if(down || east || south || west || up || north){
        return true; // there's a way out
    }else {
        p.pop_back();
        return false;
    }
}
//-----------------------------------------------------------------------------------------
