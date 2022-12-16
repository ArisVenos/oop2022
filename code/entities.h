using namespace std;


class Map{
    private:
        void GenerateMap(Map& map);
        void PrintMap(Map& map) const;
    public:
        //Map();
        //~Map();
        vector<vector<char>> world;
        void MapGenerator(Map& map);
        void MapPrinter(Map& map);
};

class Entity{
    private:
        unsigned short int health;
        unsigned short int attack;
        unsigned short int defence;
        unsigned short int x;
        unsigned short int y;
        void SpawnInPosition(Map& map);
        char SYMBOL;
    public:
        Entity() {};
        unsigned short int get_health() const { return health; }
        unsigned short int get_attack() const { return attack; }
        unsigned short int get_defence() const { return defence;}
        unsigned short int get_x() const { return x;}
        unsigned short int get_y() const { return y;};
        void symbol_set(char s) {SYMBOL = s;};
        char get_symbol() const { return SYMBOL;};
        void InitializeAbilities();
        void UpdatePosition(Map& map,int pos);
        void SpawnInMap(Map& map);

};



class Werewolf:public Entity{
    private:
        char S = 'R';
    public:
        Werewolf() {symbol_set(S);};


};

class Vampire:public Entity{
    private:
        char S = 'V';
    public:
        Vampire() {symbol_set(S);};
};

class Avatar:public Entity{
    private:
        char S = 'A';
    public:
        Avatar() {symbol_set(S);};
        void AvatarMove(Map& map);


        
};

class Game {
    private:
        vector<Vampire> vamps;
        vector<Werewolf> weres;
        Avatar av;
    public:
        void GameGenerator(Map& map,int size);
        void GameUpdater(Map& map);
};

