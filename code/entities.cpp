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
    health = 3;
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

int Entity::CheckInMap(Map& map) {
  if(map.world[x][y-1] == 'W'){
    return 1;
  }
  else if(map.world[x][y+1] == 'W'){
    return 2;
  }
  else if(map.world[x-1][y] == 'W'){
    return 3;
  }
  else if(map.world[x+1][y] == 'W'){
    return 4;
  }
  else {
    return 0;
  }
}

int Werewolf::CheckInMap(Map& map) {
  if(map.world[this->get_x()][this->get_y()-1] == 'V'){
    return 1;
  }
  else if(map.world[this->get_x()][get_y()+1] == 'V'){
    return 2;
  }
  else if(map.world[this->get_x()-1][get_y()] == 'V'){
    return 3;
  }
  else if(map.world[this->get_x()+1][get_y()] == 'V'){
    return 4;
  }
  else {
    return 0;
  }
}

char Avatar::AvatarMove(Map& map) {
  char input;
  
  cout << "enter direction: ";

  cin >> input;

  if(input == 'w'){
    this->UpdatePosition(map,0);
    return 't';
  }
  else if(input == 's') {
    this->UpdatePosition(map,1);
    return 't';
  }
  else if(input == 'a') {
    this->UpdatePosition(map,2);
    return 't';
  }
  else if(input == 'd') {
    this->UpdatePosition(map,3);
    return 't';
  }
  else if(input == 'p') {
    return 'f';
  }
  else if(input == 'q') {
    return 'q';
  }
  else {
    cout << "wrong input,use w a s d\n"<< endl;
    return AvatarMove(map);
  }
}

void Game::GameGenerator(Map& map) {
  int size;
  
  map.MapGenerator(map);

  size = (map.world.size()*map.world.size()) / 15;

  cout << "Size is: " << size << endl;

  this->vamps.resize(size);
  this->weres.resize(size);

  this->av.SpawnInMap(map);

  for(int i=0; i < this->vamps.size(); i++) {
    this->vamps[i].SpawnInMap(map);

    this->weres[i].SpawnInMap(map);
  }
  time = false;

  for(int i=0; i < this->vamps.size(); i++) {
    this->vamps[i].InitializeAbilities();

    this->weres[i].InitializeAbilities();
  }
}

void Game::GameUpdater(Map& map) {
  char pause;
  char junk;

  this->counter++;
  if(counter == 5) {
    if(this->time == false){
      this->time = true;
      this->counter = 0;
    }
    else {
      this->time = false;
      this->counter = 0;
    }
  }
  
  if(this->time == false){
    cout << "------------------Day------------------" << endl;
  }
  else {
    cout << "------------------Night------------------" << endl;
  }
  map.MapPrinter(map);
  pause = av.AvatarMove(map);

  if(pause == 'f') {
    cout << "------------------Paused the game------------------" << endl;
    cout << "Vampires left: " << this->vamps.size() << endl;
    cout << "Werewolves left: " << this->weres.size() << endl;
    cout << "Press anything to continue" << endl;
    cin >> junk;

    return;
  }
  if(pause == 'q') {
    runner = false;
    cout << "------------------Quiting the game------------------" << endl;
    return;
  }
   
  for(int i=0; i < this->vamps.size(); i++) {
    int flag;
    flag = this->vamps[i].CheckInMap(map);
    if(flag == 1) {
      this->GameKiller(map,this->vamps[i].get_x(),this->vamps[i].get_y()-1);
    }
    else if(flag == 2) {
      this->GameKiller(map,this->vamps[i].get_x(),this->vamps[i].get_y()+1);
    }
    else if(flag == 3) {
      this->GameKiller(map,this->vamps[i].get_x()-1,this->vamps[i].get_y());
    }
    else if(flag == 4) {
      this->GameKiller(map,this->vamps[i].get_x()+1,this->vamps[i].get_y());
    }
    else {
      continue;
    }

  }

  for(int i=0; i < this->weres.size(); i++) {
    int flag;
    flag = this->weres[i].CheckInMap(map);
    if(flag == 1) {
      this->GameKiller(map,this->weres[i].get_x(),this->weres[i].get_y()-1);
    }
    else if(flag == 2) {
      this->GameKiller(map,this->weres[i].get_x(),this->weres[i].get_y()+1);
    }
    else if(flag == 3) {
      this->GameKiller(map,this->weres[i].get_x()-1,this->weres[i].get_y());
    }
    else if(flag == 4) {
      this->GameKiller(map,this->weres[i].get_x()+1,this->weres[i].get_y());
    }
    else {
      continue;
    }

  }

  for(int i=0; i < this->vamps.size(); i++) {
    cout << "Vampire's " << i << " health is :" << this->vamps[i].get_health() << endl;
  }

  for(int i=0; i < this->weres.size(); i++) {
    cout << "Werewolf's " << i << " health is :" << this->weres[i].get_health() << endl;
  }

  for(int i=0; i < this->vamps.size(); i++) {
    this->vamps[i].UpdatePosition(map,rand()%4);
  }

  for(int i=0; i < this->weres.size(); i++) {
    this->weres[i].UpdatePosition(map,rand()%4);
  }

  this->GameEnder(map);

}

void Game::GameKiller(Map& map, int a, int b) {
  for(int i=0; i<vamps.size(); i++){
    if(this->vamps[i].get_x() == a && this->vamps[i].get_y() == b){
      
      this->vamps[i].get_attacked(1);
      cout << "Vampire Damaged " << endl;
      
      if(this->vamps[i].get_health() <= 0) {
        map.world[a][b] = TERRAIN_SYMBOL;
        this->vamps.erase(this->vamps.begin()+i);
      }
    }
  }

  for(int i=0; i < this->weres.size(); i++) {
    if(this->weres[i].get_x() == a){
      if(this->weres[i].get_y() == b) {
        
        this->weres[i].get_attacked(1);
        cout << "Werewolf Damaged " << endl;

        if(this->weres[i].get_health() <= 0) {
          map.world[a][b] = TERRAIN_SYMBOL;
          this->weres.erase(this->weres.begin()+i);
        }
      }
    }
  }
}

void Game::GameEnder(Map& map) {
  if(this->weres.size() == 0) {
    runner = false;
    cout << "---------------VAMPIRES WON-------------" << endl;
  }
  else if(this->vamps.size() == 0) {
    runner = false;
    cout << "---------------WEREWOLVES WON-------------" << endl;
  } 
}