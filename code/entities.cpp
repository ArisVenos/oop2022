#include <cstdlib>
#include <iostream>
#include <vector>
#include "entities.h"

// Ορίζουμε τα σύμβολα που χρησιμοποιούνται για την αναπαράσταση διαφορετικών στοιχείων στον κόσμο
const char TERRAIN_SYMBOL = ' ';
const char WATER_SYMBOL = 'L';
const char TREE_SYMBOL = 'T';
const char EDGE_SYMBOL = '=';
const char MAGIC_POTION_SYMBOL = 'M';

// Ορίζουμε την πιθανότητα να εμφανιστεί κάθε στοιχείο στον κόσμο
const float TERRAIN_PROBABILITY = 0.9;
const float WATER_PROBABILITY = 0.05;
const float TREE_PROBABILITY = 0.05;
using namespace std;

const int HEALTH = 6; //Health που ξεκινανε τα enities

//Αρχικοποιουμε τις ικανοτητες του Werewolf και Vampire
void Entity::InitializeAbilities(){
    healing = rand() % 3;
    attack =  rand() % 3 + 1;
    defence = rand() % 2 + 1;
    health = HEALTH;
}

//Καλει μια αλλη συναρτηση η οποια δημιουργει τον χαρτη
void Map::MapGenerator(Map& map){
    GenerateMap(map);
}

//Καλει μια αλλη συναρτηση η οποια τυπωνει τον χαρτη
void Map::MapPrinter(Map& map){
   PrintMap(map);
}

void Map::GenerateMap(Map& map){
  unsigned short int X, Y;
  cout <<  "Enter dimensions:" <<endl;
  cin >> X >> Y;    //Οι διαστασεις του χαρτη
  
  map.world.resize(X);  // Resize to vector ώστε να έχει τον επιθυμητό αριθμό στηλών

  //Bρόχος ο οποιος σε κάθε γραμμή του vector το τροποποιει ώστε να έχει τον επιθυμητό αριθμό στηλών
  for (int i = 0; i < X; i++)
  {
    map.world[i].resize(Y);
  }

  //Αρχικοποιηση του χαρτη με εδαφος, νερο, δεντρα αναλογα με τις πιθανοτητες που εχουμε ορισει
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

  //Η πρωτη και τελευταια γραμμη και η πρωτη και τελευταια στηλη αρχικοποιειται με το edge_symbol
  //Τα όρια του χαρτη η αλλιως "τειχος"
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

  bool potplace = true;
  

  while(potplace) { //While μεχρι να βρει εδαφος να βαλει το potion
    int randx = rand() % (X - 1);
    int randy = rand() % (Y - 1);
    if(map.world[randx][randy] == TERRAIN_SYMBOL) {
      map.world[randx][randy] = MAGIC_POTION_SYMBOL;
      potplace = false;
    }
  }

}

//Συναρτηση η οποια τυπωνει τον χαρτη η αλλιως καθε "κουτακι του χαρτη" και τι περιεχει
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

//Συναρτηση η οποια μετακινει το werewolf και vampire κατα μια θεση (εαν ειναι ελευθεση δλδ δεν υπαρχει καποιο εμποδιο παρα μονο το εδαφος)
void Entity::UpdatePosition(Map& map,int pos) {
  if(pos == 0) {
    if(map.world[x-1][y] == TERRAIN_SYMBOL){
      map.world[x-1][y] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->x = this->x - 1;
    }
    else if((map.world[x-1][y] == MAGIC_POTION_SYMBOL) && (get_symbol() == 'A')){  //Ξεχωριστη περιπτωση για Avatar και potion
      map.world[x-1][y] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->x = this->x - 1;
      this->healing++;
      cout << "You got a potion" << endl;
    }
  }
  else if(pos == 1) {
    if(map.world[x+1][y] == TERRAIN_SYMBOL){
      map.world[x+1][y] = get_symbol(); 
      map.world[x][y] = TERRAIN_SYMBOL;
      this->x = this->x + 1;
    }
    else if((map.world[x+1][y] == MAGIC_POTION_SYMBOL) && (get_symbol() == 'A')){
      map.world[x+1][y] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->x = this->x + 1;
      this->healing++;
      cout << "You got a potion" << endl;
    }
  }
  else if(pos == 2) {
    if(map.world[x][y-1] == TERRAIN_SYMBOL){
      map.world[x][y-1] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->y = this->y - 1;
    }
    else if((map.world[x][y-1] == MAGIC_POTION_SYMBOL) && (get_symbol() == 'A')){
      map.world[x][y-1] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->y = this->y - 1;
      this->healing++;
      cout << "You got a potion" << endl;
    }
  }
  else if(pos == 3){
    if(map.world[x][y+1] == TERRAIN_SYMBOL){
      map.world[x][y+1] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->y = this->y + 1;
    }
    else if((map.world[x][y+1] == MAGIC_POTION_SYMBOL) && (get_symbol() == 'A')){
      map.world[x][y+1] = get_symbol();
      map.world[x][y] = TERRAIN_SYMBOL;
      this->y = this->y + 1;
      this->healing++;
      cout << "You got a potion" << endl;
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

//Συναρτηση η οποια βαζει τυχαια στο χαρτη τις οντοτητες
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

//Καλει μια αλλη συναρτηση η οποια βαζει τυχαια στο χαρτη τις οντοτητες werewolfes και vampires
void Entity::SpawnInMap(Map& map) {
  SpawnInPosition(map);
}

//Ελεγχει εαν υπαρχει σε διπλανες θεσεις καποιο werewolf, η συναρτηση αυτη καλειται απο vampire ωστε να κανει attack καποιο werewolf οπως θα δουμε παρακατω
int Entity::CheckInMap(Map& map) {
  if(map.world[x][y-1] == 'W'){       //Ελεγχει την αριστερα θεση
    return 1;
  }
  else if(map.world[x][y+1] == 'W'){  //Ελεγχει την δεξια θεση
    return 2;
  }
  else if(map.world[x-1][y] == 'W'){  //Ελεγχει την πανω θεση
    return 3;
  }
  else if(map.world[x+1][y] == 'W'){  //Ελεγχει την κατω θεση
    return 4;
  }
  else {
    return 0;
  }
}

//Ελεγχει εαν υπαρχει σε διπλανες θεσεις καποιο vampire, η συναρτηση αυτη καλειται απο werewolf ωστε να κανει attack καποιο vampire οπως θα δουμε παρακατω
int Werewolf::CheckInMap(Map& map) {
  if(map.world[this->get_x()][this->get_y()-1] == 'V'){   //Ελεγχει την αριστερα θεση
    return 1;
  }
  else if(map.world[this->get_x()][get_y()+1] == 'V'){    //Ελεγχει την δεξια θεση
    return 2;
  }
  else if(map.world[this->get_x()-1][get_y()] == 'V'){    //Ελεγχει την πανω θεση
    return 3;
  }
  else if(map.world[this->get_x()+1][get_y()] == 'V'){    //Ελεγχει την κατω θεση
    return 4;
  }
  else {
    return 0;
  }
}

//Ελεγχει εαν υπαρχει σε διπλανες θεσεις καποιο vampire, η συναρτηση αυτη καλειται απο vampire ωστε να δωσει γιατρικο σε καποιο αλλο vampire οπως θα δουμε παρακατω
int Entity::CheckInMapAly(Map& map) {
  if(map.world[x][y-1] == 'V'){       //Ελεγχει την αριστερα θεση
    return 1;
  }
  else if(map.world[x][y+1] == 'V'){  //Ελεγχει την δεξια θεση
    return 2;
  }
  else if(map.world[x-1][y] == 'V'){   //Ελεγχει την πανω θεση
    return 3;
  }
  else if(map.world[x+1][y] == 'V'){  //Ελεγχει την κατω θεση
    return 4;
  }
  else {
    return 0;
  }
}

//Ελεγχει εαν υπαρχει σε διπλανες θεσεις καποιο werewolf, η συναρτηση αυτη καλειται απο werewolf ωστε να δωσει γιατρικο σε καποιο αλλο werewolf οπως θα δουμε παρακατω
int Werewolf::CheckInMapAly(Map& map) {
  if(map.world[this->get_x()][this->get_y()-1] == 'W'){   //Ελεγχει την αριστερα θεση
    return 1;
  }
  else if(map.world[this->get_x()][get_y()+1] == 'W'){    //Ελεγχει την δεξια θεση
    return 2;
  }
  else if(map.world[this->get_x()-1][get_y()] == 'W'){    //Ελεγχει την πανω θεση
    return 3;
  }
  else if(map.world[this->get_x()+1][get_y()] == 'W'){    //Ελεγχει την κατω θεση
    return 4;
  }
  else {
    return 0;
  }
}

//Συναρτηση η οποια μετακινει το Avatar αναλογα με τι χαρακτηρα του δινουμε στη γραμμη εντολων
//'w' για να παει μια θεση πανω, 's' για να παει μια θεση κατω, 'a' για να παει μια θεση αριστερα, 'd' για να παει μια θεση δεξια
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

//Συναρτηση με την οποια ο Avatar επιλεγει ποια ομαδα θα υποστηριξει
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

//Συναρτηση η οποια καλειται καθε φορα ωστε να τρεχει το παιχνιδι
void Game::GameGenerator(Map& map) {
  int size;
  
  map.MapGenerator(map);

  size = (map.world.size()*map.world.size()) / 15;

  cout << "Teams size: " << size << endl;

  //Δημιουργια vampires και werewolfs
  this->vamps.resize(size);
  this->weres.resize(size);

  //Τοποθετουμε τον avatar στο χαρτη
  this->av.SpawnInMap(map);

  //Τοποθετουμε τα vampires και werewolfs στο χαρτη
  for(int i=0; i < this->vamps.size(); i++) {
    this->vamps[i].SpawnInMap(map);

    this->weres[i].SpawnInMap(map);
  }
  time = false;

  //Αρχικοποιουμε τις ικανοτητες καθε vampire και werewolf
  for(int i=0; i < this->vamps.size(); i++) {
    this->vamps[i].InitializeAbilities();

    this->weres[i].InitializeAbilities();
  }

  this->av.TeamSelector();
}


void Game::GameUpdater(Map& map) {
  char pause;
  char junk;

  //Καθε φορα που αυξανεται το counter κατα 5 εναλλασσεται η μερα με τη νυχτα
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

  //Καθε φορα που αυξανεται κατα 5 το counter εναλλασσεται η μερα με την νυχτα και εκτυπωνεται το αντιστοιχο μηνυμα
  if(this->time == false){
    cout << "------------------Day------------------" << endl;
  }
  else {
      cout << "------------------Night------------------" << endl;
    }


  map.MapPrinter(map);
  pause = av.AvatarMove(map);

  //Εαν πατηθει το πληκτρο f στη γραμμη εντολων γινεται pause το game και
  //Εκτυπωνονται ο αριθμος werewolfs και vampires
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
  //Εαν πατηθει το πληκτρο q τελειωνει το παιχνιδι
  if(pause == 'q') {
    runner = false;
    cout << "------------------Quiting the game------------------" << endl;
    return;
  }

  //Επιλεγουμε εαν επουλωσουμε vampires η werewolfs πατωντας το πληκτρο h αναλογα με το εαν ειναι μερα η νυχτα
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
   
  //Συναρτηση οπου ελεγχει εαν καθε vampire εχει σε διπλανη του θεση καποιο werewolf με την CheckInMap
  //Εαν βρει καποιο werewolf σε διπλανη θεση καλειται η GameKiller ωστε να του κανει επιθεση
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


  //Συναρτηση οπου ελεγχει εαν καθε werewolf εχει σε διπλανη του θεση καποιο αλλο werewolf με την CheckInMapAly
  //Εαν βρει καποιο werewolf σε διπλανη θεση καλειται η GameHealer ωστε να του δωσει γιατρικο
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

  //Συναρτηση οπου ελεγχει εαν καθε werewolf εχει σε διπλανη του θεση καποιο vampire με την CheckInMap
  //Εαν βρει καποιο vampire σε διπλανη θεση καλειται η GameKiller ωστε να του κανει επιθεση
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

  //Συναρτηση οπου ελεγχει εαν καθε vampire εχει σε διπλανη του θεση καποιο αλλο wampire με την CheckInMapAly
  //Εαν βρει καποιο vampire σε διπλανη θεση καλειται η GameHealer ωστε να του δωσει γιατρικο
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

  //Γινεται update της θεσης καθε vampire
  for(int i=0; i < this->vamps.size(); i++) {
    this->vamps[i].UpdatePosition(map,rand()%8);
  }

  //Γινεται update της θεσης καθε werewolf
  for(int i=0; i < this->weres.size(); i++) {
    this->weres[i].UpdatePosition(map,rand()%4);
  }

  this->GameEnder(map);

}

//Εδω καθε οντοτητα κανει επιθεση σε μια αντιπαλη οντοτητα
void Game::GameKiller(Map& map, int a, int b, int c) {
  //Εδω τα werewolfs κανουν επιθεση στα vampires
  for(int i=0; i<vamps.size(); i++){
    if(this->vamps[i].get_x() == a && this->vamps[i].get_y() == b){
      if(this->vamps[i].get_attack() <= c){
        this->vamps[i].get_attacked(c, this->vamps[i].get_defence());
        cout << "Vampire "<< i << " got attacked" << endl;
      }
      //Εαν μηδενιστει η υγεια καποιου vampire τοτε διαγραφεται απο το χαρτη και συνεπως απο το vector
      if(this->vamps[i].get_health() <= 0 || this->vamps[i].get_health() > 50) {
        map.world[a][b] = TERRAIN_SYMBOL;
        this->vamps.erase(this->vamps.begin()+i);
      }
    }
  }

  //Εδω τα vampires κανουν επιθεση στα werewolfs
  for(int i=0; i < this->weres.size(); i++) {
    if(this->weres[i].get_x() == a && this->weres[i].get_y() == b){
      if(this->weres[i].get_attack() <= c){
        this->weres[i].get_attacked(c, this->weres[i].get_defence());
        cout << "Werewolf "<< i << " got attacked" << endl;
      }
      //Εαν μηδενιστει η υγεια καποιου werewolf τοτε διαγραφεται απο το χαρτη και συνεπως απο το vector
      if(this->weres[i].get_health() <= 0 || this->weres[i].get_health() > 50) {
        map.world[a][b] = TERRAIN_SYMBOL;
        this->weres.erase(this->weres.begin()+i);
      }
    }  
  }
}

//Εδω καθε οντοτητα δινει γιατρικο σε εναν συμμαχο της
int Game::GameHealer(Map& map, int a, int b) {
  for(int i=0; i < vamps.size(); i++){
    if(this->vamps[i].get_x() == a && this->vamps[i].get_y() == b){
      //Εαν καποιο vampire δεν εχει πληρη υγεια τοτε θα λαβει "βοηθεια" δηλαδη γιατρικο απο ενα αλλο
      if(this->vamps[i].get_health() < HEALTH){
        //Θα επιλεξει τυχαια αν του δωσει γιατρικο
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
      //Εαν καποιο werewolf δεν εχει πληρη υγεια τοτε θα λαβει "βοηθεια" δηλαδη γιατρικο απο ενα αλλο
      if(this->weres[i].get_health() < HEALTH){
        //Θα επιλεξει τυχαια αν του δωσει γιατρικο
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

//Συναρτηση η οποια τερματιζει το παιχνιδι οταν πεθανουν ολα τα werewolfs ή ολα ta vampires 
//και τυπωνει το αντιστοιχο μηνυμα αναλογα με το ποιος νικησε
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