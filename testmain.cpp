#include <iostream>
#include "Pathfinder.h"

using namespace std;

int main(){
    Pathfinder p;
    bool t = p.importMaze("Solvable1.txt");
    p.importMaze("Unsolvable1.txt");
    p.importMaze("Invalid4.txt");
    if(t){
        cout << "It worked!" << endl;
    } else{
        cout << "Let's give it one more try!" << endl;
    }
    return 0;
}