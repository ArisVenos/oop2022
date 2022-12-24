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
const char MAGIC_POTION_SYMBOL = 'M';

// Define the probability of each element appearing in the world
const float TERRAIN_PROBABILITY = 0.9;
const float WATER_PROBABILITY = 0.05;
const float TREE_PROBABILITY = 0.05;
using namespace std;

const int HEALTH = 6;

void Entity::InitializeAbilities(){
    healing = rand() % 3;
    attack =  rand() % 3 + 1;
    defence = rand() % 2 + 1;
    health = HEALTH;
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
  cout <<  "Enter dimensions:" <<endl;
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
  else if(pos == 4){
    if(map.world[x-1][y-1] == TERRAIN_SYMBOL){
      map.world[x-1][y-1] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->x = this->x - 1;
      this->y = this->y - 1;
    }
  }
  else if(pos == 5){
    if(map.world[x+1][y+1] == TERRAIN_SYMBOL){
      map.world[x+1][y+1] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->x = this->x + 1;
      this->y = this->y + 1;
    }
  }
  else if(pos == 6){
    if(map.world[x+1][y-1] == TERRAIN_SYMBOL){
      map.world[x+1][y-1] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->x = this->x + 1;
      this->y = this->y - 1;
    }
  }
  else if(pos == 7){
    if(map.world[x-1][y+1] == TERRAIN_SYMBOL){
      map.world[x-1][y+1] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->x = this->x - 1;
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

int Entity::CheckInMapAly(Map& map) {
  if(map.world[x][y-1] == 'V'){
    return 1;
  }
  else if(map.world[x][y+1] == 'V'){
    return 2;
  }
  else if(map.world[x-1][y] == 'V'){
    return 3;
  }
  else if(map.world[x+1][y] == 'V'){
    return 4;
  }
  else {
    return 0;
  }
}

int Werewolf::CheckInMapAly(Map& map) {
  if(map.world[this->get_x()][this->get_y()-1] == 'W'){
    return 1;
  }
  else if(map.world[this->get_x()][get_y()+1] == 'W'){
    return 2;
  }
  else if(map.world[this->get_x()-1][get_y()] == 'W'){
    return 3;
  }
  else if(map.world[this->get_x()+1][get_y()] == 'W'){
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
  else if(input == 'h') {
    return 'h';
  }
  else {
    cout << "wrong input,use w a s d p q h\n"<< endl;
    return AvatarMove(map);
  }
}

void Avatar::TeamSelector() {
  char a;
  cout << "Please select team : w for werewolves or v for vampires " << endl;
  cin >> a;
  if(a == 'w') {
    cout << "You chose werewolves" << endl;
    this->team = a;
    return;
  }
  else if(a == 'v') {
    cout << "You chose vampires" << endl;
    this->team = a;
    return;
  }
  else {
    cout << "Wrong selection, please type w or v" << endl;
    this->TeamSelector();
    return;
  }

}

void Game::GameGenerator(Map& map) {
  int size;
  
  map.MapGenerator(map);

  size = (map.world.size()*map.world.size()) / 15;

  cout << "Teams size: " << size << endl;

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

  this->av.TeamSelector();
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


  //DAY EPOULONEI VAMPIRES - NIGHT EPOULONEI WEREWOLFS
  //entometaxu ta vampires to vradu xupnane alla o diogenhs den exei vampire diaries XD
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
    cout << "Potions left: " << this->av.get_healing() << endl;
    cout << "Press anything to continue" << endl;
    counter--;
    cin >> junk;

    return;
  }
  if(pause == 'q') {
    runner = false;
    cout << "------------------Quiting the game------------------" << endl;
    return;
  }
  if(pause == 'h') {
    if(this->time == true) {
      if(av.get_healing() > 0) {
        if(av.team == 'w') {
          for(int i=0; i < this->weres.size(); i++) {
            this->weres[i].get_healed();
          }
          av.ReduceHealing();
        }
        else {
          for(int i=0; i < this->vamps.size(); i++) {
            this->vamps[i].get_healed();
          }
          av.ReduceHealing();
        }
      }
      else {
        cout << "You have no potions" << endl;
        counter--;
        return;
      }
    }
    else {
      cout << "Its day time, you cant heal" << endl;
      counter--;
      return;
    }
  }
   
  for(int i=0; i < this->vamps.size(); i++) {
    int flag;
    flag = this->vamps[i].CheckInMap(map);
    if(flag == 1) {
      this->GameKiller(map,this->vamps[i].get_x(),this->vamps[i].get_y()-1, this->vamps[i].get_attack());
    }
    else if(flag == 2) {
      this->GameKiller(map,this->vamps[i].get_x(),this->vamps[i].get_y()+1, this->vamps[i].get_attack());
    }
    else if(flag == 3) {
      this->GameKiller(map,this->vamps[i].get_x()-1,this->vamps[i].get_y(), this->vamps[i].get_attack());
    }
    else if(flag == 4) {
      this->GameKiller(map,this->vamps[i].get_x()+1,this->vamps[i].get_y(), this->vamps[i].get_attack());
    }
    else {
      continue;
    }
  }

  //Edo healaroun ta weres
  for(int i=0; i < this->weres.size(); i++) {
    int flag;
    flag = this->weres[i].CheckInMapAly(map);
    if(this->weres[i].get_healing() > 0){
      if(flag == 1) {
        if(this->GameHealer(map,this->weres[i].get_x(),this->weres[i].get_y()-1) == 1){
          this->weres[i].ReduceHealing();
        }
      }
      else if(flag == 2) {
        if(this->GameHealer(map,this->weres[i].get_x(),this->weres[i].get_y()+1) == 1){
          this->weres[i].ReduceHealing();
        }
      }
      else if(flag == 3) {
        if(this->GameHealer(map,this->weres[i].get_x()-1,this->weres[i].get_y()) == 1){
          this->weres[i].ReduceHealing();
        }
      }
      else if(flag == 4) {
       if(this->GameHealer(map,this->weres[i].get_x()+1,this->weres[i].get_y()) == 1){
          this->weres[i].ReduceHealing();
        }
      }
      else {
        continue;
      }
    }
  }

  for(int i=0; i < this->weres.size(); i++) {
    int flag;
    flag = this->weres[i].CheckInMap(map);
    if(flag == 1) {
      this->GameKiller(map,this->weres[i].get_x(),this->weres[i].get_y()-1, this->weres[i].get_attack());
    }
    else if(flag == 2) {
      this->GameKiller(map,this->weres[i].get_x(),this->weres[i].get_y()+1, this->weres[i].get_attack());
    }
    else if(flag == 3) {
      this->GameKiller(map,this->weres[i].get_x()-1,this->weres[i].get_y(), this->weres[i].get_attack());
    }
    else if(flag == 4) {
      this->GameKiller(map,this->weres[i].get_x()+1,this->weres[i].get_y(), this->weres[i].get_attack());
    }
    else {
      continue;
    }
  }

  for(int i=0; i < this->vamps.size(); i++) {
    int flag;
    flag = this->vamps[i].CheckInMapAly(map);
    if(this->vamps[i].get_healing() > 0){
      if(flag == 1) {
        if(this->GameHealer(map,this->vamps[i].get_x(),this->vamps[i].get_y()-1) == 1){
          this->vamps[i].ReduceHealing();
        }
      }
      else if(flag == 2) {
        if(this->GameHealer(map,this->vamps[i].get_x(),this->vamps[i].get_y()+1) == 1){
          this->vamps[i].ReduceHealing();
        }
      }
      else if(flag == 3) {
        if(this->GameHealer(map,this->vamps[i].get_x()-1,this->vamps[i].get_y()) == 1){
          this->vamps[i].ReduceHealing();
        }
      }
      else if(flag == 4) {
       if(this->GameHealer(map,this->vamps[i].get_x()+1,this->vamps[i].get_y()) == 1){
          this->vamps[i].ReduceHealing();
        }
      }
      else {
        continue;
      }
    }
  }


  for(int i=0; i < this->vamps.size(); i++) {
    cout << "Vampire " << i << " health is :" << this->vamps[i].get_health() << endl;
  }

  for(int i=0; i < this->weres.size(); i++) {
    cout << "Werewolf " << i << " health is :" << this->weres[i].get_health() << endl;
  }

  for(int i=0; i < this->vamps.size(); i++) {
    this->vamps[i].UpdatePosition(map,rand()%8);
  }

  for(int i=0; i < this->weres.size(); i++) {
    this->weres[i].UpdatePosition(map,rand()%4);
  }

  this->GameEnder(map);

}

void Game::GameKiller(Map& map, int a, int b, int c) {
  for(int i=0; i<vamps.size(); i++){
    if(this->vamps[i].get_x() == a && this->vamps[i].get_y() == b){
      if(this->vamps[i].get_attack() <= c){
        this->vamps[i].get_attacked(c, this->vamps[i].get_defence());
        cout << "Vampire "<< i << " got damaged" << endl;
      }
      if(this->vamps[i].get_health() <= 0 || this->vamps[i].get_health() > 50) {
        map.world[a][b] = TERRAIN_SYMBOL;
        this->vamps.erase(this->vamps.begin()+i);
      }
    }
  }

  for(int i=0; i < this->weres.size(); i++) {
    if(this->weres[i].get_x() == a && this->weres[i].get_y() == b){
      if(this->weres[i].get_attack() <= c){
        this->weres[i].get_attacked(c, this->weres[i].get_defence());
        cout << "Werewolf "<< i << " got damaged" << endl;
      }
      if(this->weres[i].get_health() <= 0 || this->weres[i].get_health() > 50) {
        map.world[a][b] = TERRAIN_SYMBOL;
        this->weres.erase(this->weres.begin()+i);
      }
    }  
  }
}

int Game::GameHealer(Map& map, int a, int b) {
  for(int i=0; i < vamps.size(); i++){
    if(this->vamps[i].get_x() == a && this->vamps[i].get_y() == b){
      if(this->vamps[i].get_health() < HEALTH){
        if(rand() % 2 == 0){
          this->vamps[i].get_healed();
          cout << "Vampire "<< i << " got healed " << endl;
          return 1;
        }
      }
      return 0;
    }
  }

   for(int i=0; i < weres.size(); i++){
    if(this->weres[i].get_x() == a && this->weres[i].get_y() == b){
      if(this->weres[i].get_health() < HEALTH){
        if(rand() % 2 == 0){
          this->weres[i].get_healed();
          cout << "Werewolf " << i << " got healed " << endl;
          return 1;
        }
      }
      return 0;
    }
  }
  return 0;
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