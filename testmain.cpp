#include <iostream>
#include "Pathfinder.h"

using namespace std;

int main(){
    Pathfinder p;
    bool t = p.importMaze("Mazes/Invalid1.txt");
    if(t){
        cout << "It worked!" << endl;
    } else{
        cout << "Invalid1 false" << endl;
    }
    cout << p.toString() << endl;

    bool s = p.importMaze("Mazes/Solvable1.txt");
    if(s){
        cout << "It worked!" << endl;
    } else{
        cout << "Invalid1 false" << endl;
    }
    cout << p.toString() << endl;
    bool test = p.importMaze("Mazes/Invalid2.txt");
    if(test){
        cout << "It worked!" << endl;
    } else{
        cout << "Invalid1 false" << endl;
    }
    cout << p.toString() << endl;
    

    //p.importMaze("Unsolvable1.txt");
    //p.importMaze("Invalid4.txt");
    return 0;
}