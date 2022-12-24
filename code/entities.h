using namespace std;

extern bool runner;

class Map{
    private:
        void GenerateMap(Map& map);
        void PrintMap(Map& map) const;
    public:
        vector<vector<char>> world;
        void MapGenerator(Map& map);
        void MapPrinter(Map& map);
};

class Entity{
    private:
        unsigned short int healing = 1;
        unsigned short int health;
        unsigned short int attack;
        unsigned short int defence;
        unsigned short int x;
        unsigned short int y;
        void SpawnInPosition(Map& map);
        char SYMBOL;
    public:
        Entity() {};
        ~Entity() {};
        unsigned short int get_health() const { return health; };
        unsigned short int get_attack() const { return attack; };
        unsigned short int get_defence() const { return defence;};
        unsigned short int get_healing() const { return healing;};
        unsigned short int get_x() const { return x;};
        unsigned short int get_y() const { return y;};
        void get_attacked(int dmg, int def) { if(dmg <= def) {return;} health = health + (def - dmg);};
        void get_healed() { health = health + 1;};
        void symbol_set(char s) {SYMBOL = s;};
        char get_symbol() const { return SYMBOL;};
        void InitializeAbilities();
        void UpdatePosition(Map& map,int pos);
        void SpawnInMap(Map& map);
        void ReduceHealing(){ healing--;};
        void IncreaseHealth(){ health++;}
        virtual int CheckInMap(Map& map);
        virtual int CheckInMapAly(Map& map);
};



class Werewolf:public Entity{
    private:
        char S = 'W';
    public:
        Werewolf() {symbol_set(S);};
        ~Werewolf() {cout <<"Werewolf killed"<<endl;};
        int CheckInMap(Map& map);
        int CheckInMapAly(Map& map);

};

class Vampire:public Entity{
    private:
        char S = 'V';
    public:
        Vampire() {symbol_set(S);};
        ~Vampire() {cout <<"Vampire killed"<<endl;};
};

class Avatar:public Entity{
    private:
        char S = 'A';
    public:
        Avatar() {symbol_set(S);};
        ~Avatar(){cout << "Destroyed Avatar"<<endl;};
        char AvatarMove(Map& map);
        void TeamSelector();
        char team;  
};

class Game {
    private:
        vector<Vampire> vamps;
        vector<Werewolf> weres;
        Avatar av;
        int counter = 0;
        bool time;
    public:
        void GameKiller(Map& map, int a, int b, int c);
        int GameHealer(Map& map, int a, int b);
        void GameGenerator(Map& map);
        void GameUpdater(Map& map);
        void GameEnder(Map& map);
};