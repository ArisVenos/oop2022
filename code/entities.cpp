#include <cstdlib>
#include <iostream>
#include <vector>
#include "entities.h"

//vector<vector<char>> world(10, vector<char>(10));
// Define the symbols used to represent different elements in the world
const char TERRAIN_SYMBOL = ' ';
const char WATER_SYMBOL = 'L';
const char TREE_SYMBOL = 'T';
const char EDGE_SYMBOL = '=';

// Define the probability of each element appearing in the world
const float TERRAIN_PROBABILITY = 0.9;
const float WATER_PROBABILITY = 0.05;
const float TREE_PROBABILITY = 0.05;

using namespace std;


void Entity::InitializeAbilities(){
    
    healing = rand() % 3;
    attack = rand() % 3 + 1;
    defence = rand() % 2 + 1;
    health = 5;
}

void Map::MapGenerator(Map& map){
    GenerateMap(map);
}

void Map::MapPrinter(Map& map){
   PrintMap(map);
}

void Map::GenerateMap(Map& map){
  unsigned short int X, Y;
  int size = 3;
  cout <<  "Enter dimensions" <<endl;
  cin >> X >> Y;
  // Resize the vector to have the desired number of rows
  map.world.resize(X);

  // Loop through each row of the vector and resize it to have the desired number of columns
  for (int i = 0; i < X; i++)
  {
    map.world[i].resize(Y);
  }
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
      cout << "[" << map.world[i][j] << "]";
    }
    cout << endl;
  }

}
void Entity::UpdatePosition(Map& map,int pos) {
  if(pos == 0) {
    if(map.world[x-1][y] == TERRAIN_SYMBOL){
      map.world[x-1][y] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->x = this->x - 1;
    }
  }
  else if(pos == 1) {
    if(map.world[x+1][y] == TERRAIN_SYMBOL){
      map.world[x+1][y] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->x = this->x + 1;
    }
  }
  else if(pos == 2) {
    if(map.world[x][y-1] == TERRAIN_SYMBOL){
      map.world[x][y-1] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->y = this->y - 1;
    }
  }
  else if(pos == 3){
    if(map.world[x][y+1] == TERRAIN_SYMBOL){
      map.world[x][y+1] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->y = this->y + 1;
    }
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

void Avatar::AvatarMove(Map& map) {
  char input;
  
  cout << "enter direction: ";

  cin >> input;

  if(input == 'w'){
    this->UpdatePosition(map,0);
  }
  else if(input == 's') {
    this->UpdatePosition(map,1);
  }
  else if(input == 'a') {
    this->UpdatePosition(map,2);
  }
  else if(input == 'd') {
    this->UpdatePosition(map,3);
  }
  else {
    cout << "wrong input,use w a s d\n"<< endl;
    this->UpdatePosition(map,rand()%4);
    AvatarMove(map);
  }
}

void Game::GameGenerator(Map& map, int size) {
  map.MapGenerator(map);

  this->vamps.resize(size);
  this->weres.resize(size);

  this->av = Avatar();

  for(int i; i < size; i++) {
    this->vamps[i] = Vampire();

    this->weres[i] = Werewolf();
  }

  this->av.SpawnInMap(map);

  for(int i=0; i < this->vamps.size(); i++) {
    this->vamps[i].SpawnInMap(map);

    this->weres[i].SpawnInMap(map);
  }
}

void Game::GameUpdater(Map& map) {
  map.MapPrinter(map);
  av.AvatarMove(map);

  for(int i=0; i < this->vamps.size(); i++) {
    this->vamps[i].UpdatePosition(map,rand()%4);

    this->weres[i].UpdatePosition(map,rand()%4);
  }
}