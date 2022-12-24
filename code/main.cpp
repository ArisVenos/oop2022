#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <vector>
#include "entities.h"

using namespace std;

bool runner = true;

int main(){
  srand(time(0));

  Map map;
  Game game;
  
  game.GameGenerator(map);
  
  while(runner) {
    game.GameUpdater(map);
  }

  return 0;
  
}
