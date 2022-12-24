using namespace std;

extern bool runner;

//Κλαση Map
class Map{
    private:
        void GenerateMap(Map& map);    //Συνάρτηση η οποία αρχικοποιεί τον χαρτη
        void PrintMap(Map& map) const; //Συνάρτηση η οποία εκτυπώνει τον χαρτη
    public:
        vector<vector<char>> world;     //Two dimension vector για τον χαρτη
        void MapGenerator(Map& map);
        void MapPrinter(Map& map);
};

class Entity{
    private:
        unsigned short int healing = 1; //Γιατρικό
        unsigned short int health;      //Υγεία
        unsigned short int attack;      //Επίθεση
        unsigned short int defence;     //Άμυνα
        unsigned short int x;           //Συντεταγμενες x,y
        unsigned short int y;
        void SpawnInPosition(Map& map); //Συναρτηση η οποια σε καθε σημειο (x,y) του χαρτη βαζει ενα αντικειμενο
        char SYMBOL;    //Σύμβολο καθε οντοτητας
    public:
        Entity() {};
        ~Entity() {};
        unsigned short int get_health() const { return health; };   //Επιστρεφει την τιμη της υγειας
        unsigned short int get_attack() const { return attack; };   //Επιστρεφει την τιμη της επιθεσης
        unsigned short int get_defence() const { return defence;};  //Επιστρεφει την τιμη της αμυνας
        unsigned short int get_healing() const { return healing;};  //Επιστρεφει την τιμη του γιατρικου
        unsigned short int get_x() const { return x;};              //Επιστρεφει την τιμη της συντεταγμενης x
        unsigned short int get_y() const { return y;};              //Επιστρεφει την τιμη της συντεταγμενης y
        void get_attacked(int dmg, int def) { if(dmg <= def) {return;} health = health + (def - dmg);};     //Οταν μια οντοτητα κανει επιθεση σε μια αλλη, μειωνεται η υγεια της
        void get_healed() { health = health + 1;};      //Αυξανεται η υγειας μιας οντοτητας οταν καποιος της δινει γιατρικο
        void symbol_set(char s) {SYMBOL = s;};
        char get_symbol() const { return SYMBOL;};      //Επιστρεφει ενα συμβολο
        void InitializeAbilities();                     //Συνάρτηση η οποία αρχικοποιει την υγεια, γιατρικο, επιθεση, αμυνα του Werewolf και Vampire
        void UpdatePosition(Map& map,int pos);          //Συναρτηση η οποια κανει update τις συντεταγμενες καθε οντοητας σε καθε κινηση τους
        void SpawnInMap(Map& map);
        void ReduceHealing(){ healing--;};        //Συναρτηση η οποια μειώνει το γιατρικο
        void IncreaseHealth(){ health++;}         //Συναρτηση η οποια αυξανει την υγεια
        virtual int CheckInMap(Map& map);
        virtual int CheckInMapAly(Map& map);
};


// Κλαση Werewolf
class Werewolf:public Entity{
    private:
        char S = 'W';           //το συμβολο του werewolf στο χαρτη
    public:
        Werewolf() {symbol_set(S);};                //Βαζουμε σαν συμβολο του werewolf το χαρακτηρα 'W'
        ~Werewolf() {cout <<"Werewolf killed"<<endl;};
        int CheckInMap(Map& map);
        int CheckInMapAly(Map& map);

};

//Κλαση Vampire
class Vampire:public Entity{
    private:
        char S = 'V';               //το συμβολο του vampire στο χαρτη
    public:
        Vampire() {symbol_set(S);};             //Βαζουμε σαν συμβολο του vampire το χαρακτηρα 'V'
        ~Vampire() {cout <<"Vampire killed"<<endl;};
};

//Κλαση Avatar
class Avatar:public Entity{
    private:
        char S = 'A';               //το συμβολο του Avatar στο χαρτη
    public:
        Avatar() {symbol_set(S);};          //Βαζουμε σαν συμβολο του Avatar το χαρακτηρα 'A'
        ~Avatar(){cout << "Destroyed Avatar"<<endl;};
        char AvatarMove(Map& map);          //Συναρτηση με την οποια κινειται ο Avatar
        void TeamSelector();                //Συναρτηση με την οποια επιλεγει ομαδα ο Avatar
        char team;  
};

// Κλαση Game
class Game {
    private:
        vector<Vampire> vamps;  //Vector για τη δημιουργια των vamps
        vector<Werewolf> weres; //Vector για τη δημιουργια των werewolfs
        Avatar av;              //Δημιουργα object Avatar
        int counter = 0;
        bool time;
    public:
        void GameKiller(Map& map, int a, int b, int c); //Συναρτηση η οποια καθε οντοτητα επιτιθεται σε αντιπαλη οπως θα δουμε στην υλοποιηση της στο .cpp
        int GameHealer(Map& map, int a, int b);         //Συναρτηση η οποια καθε οντοτητα δινει γιατρικο σε καποο συμμαχο της οπως θα δουμε στην υλοποιηση της στο .cpp
        void GameGenerator(Map& map);
        void GameUpdater(Map& map);
        void GameEnder(Map& map);                   //Συναρτηση για να τερματιζει το παιχνιδι
};