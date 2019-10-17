#include <iostream>
#include "Pathfinder.h"

using namespace std;

int main(){
    Pathfinder p;
    p.importMaze("Mazes/Solvable2.txt");
    cout << p.toString() << endl;
    vector<string> sol = p.solveMaze();
    for(vector<string>::iterator it = sol.begin(); it != sol.end(); ++it){
        cout << *it << endl;
    }
    
    return 0;
}