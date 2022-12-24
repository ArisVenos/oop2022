#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <vector>
#include "entities.h"

using namespace std;

bool runner = true;

int main(){
  srand(time(0));

  Map map;    //Δημιουργια object map
  Game game;  //Δημιουργια object game
  
  //Καλουμε την GameGenerator ωστε να αρχικοποιηθει ο χαρτης με ολες τις οντοτητες που περιεχει μεσα
  game.GameGenerator(map);
  
  //Καλειται η GameUpdater εως ωτου να τερματισει το παιχνιδι δηλαδη runner = false
  while(runner) {
    game.GameUpdater(map);
  }

  return 0;
  
}