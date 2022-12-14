#include <cstdlib>
#include <iostream>
#include <vector>
#include "entities.h"

//vector<vector<char>> world(10, vector<char>(10));
// Define the symbols used to represent different elements in the world
const char TERRAIN_SYMBOL = ' ';
const char WATER_SYMBOL = 'W';
const char TREE_SYMBOL = 'X';
const char EDGE_SYMBOL = '=';

// Define the probability of each element appearing in the world
const float TERRAIN_PROBABILITY = 0.8;
const float WATER_PROBABILITY = 0.1;
const float TREE_PROBABILITY = 0.1;

using namespace std;


void Entity::InitializeAbilities(){
    
    health = rand() % 3;
    attack = rand() % 3 + 1;
    defence = rand() % 2 + 1;
}

void Entity::UpdatePosition(int dx, int dy) {
    x += dx;
    y += dy;
}

/*Map::Map(){
  unsigned short int X, Y;
  vector<vector<char>> world(X, vector<char>(Y));


}*/
//unsigned short int X, Y;/vector<vector<char>> world(int X, vector<char>(Y));
void Map::MapGenerator(Map& map){
    GenerateMap(map);
}

void Map::MapPrinter(Map& map){
   PrintMap(map);
}

void Map::GenerateMap(Map& map){
  unsigned short int X, Y;
  cout <<  "Enter dimensions" <<endl;
  cin >> X >> Y;
  // Resize the vector to have the desired number of rows
  map.world.resize(X);

  // Loop through each row of the vector and resize it to have the desired number of columns
  for (int i = 0; i < X; i++)
  {
    map.world[i].resize(Y);
  }
    // Create a two-dimensional vector to represent the world
  //vector<vector<char>> map.wor (X, vector<char>(Y));
  //int world[X][Y];
    // Initialize the world with terrain, water, and trees according to their probabilities
  for (int i = 0; i < X; i++)
  {
    for (int j = 0; j < Y; j++)
    {
      float z = (float) rand() / RAND_MAX;

      if (z <= TERRAIN_PROBABILITY)
      {
        map.world[i][j] = TERRAIN_SYMBOL;
      }
      else if (z <= WATER_PROBABILITY + TERRAIN_PROBABILITY)
      {
        map.world[i][j] = WATER_SYMBOL;
      }
      else
      {
       map.world[i][j] = TREE_SYMBOL;
      }
    }
  }

  for(int i = 0; i < X; i++) {
    map.world[i][0] = EDGE_SYMBOL;
  }
  for(int i = 0; i < X; i++) {
    map.world[i][X-1] = EDGE_SYMBOL;
  }
  for(int i = 0; i < X; i++) {
    map.world[0][i] = EDGE_SYMBOL;
  }
  for(int i = 0; i < X; i++) {
    map.world[Y-1][i] = EDGE_SYMBOL;
  }
}

void Map::PrintMap(Map& map) const{
  for (int i = 0; i < map.world.size(); i++)
  {
    for (int j = 0; j < map.world[i].size(); j++)
    {
      cout << map.world[i][j] << " ";
    }
    cout << endl;
  }

}

void Entity::SpawnInPosition(Map& map) {
  bool flag = true;

  while(flag) {
    x = rand() % map.world.size();
    y = rand() % map.world[0].size();

    if(map.world[x][y] == TERRAIN_SYMBOL) {
      map.world[x][y] = get_symbol();
      flag = false;
    }
  }
}

void Entity::SpawnInMap(Map& map) {
  SpawnInPosition(map);
}