#include <iostream>
#include "Pathfinder.h"

using namespace std;

int main(){
    Pathfinder p;
    p.createRandomMaze();
    string mze = p.toString();
    cout << mze << endl;
    return 0;
}