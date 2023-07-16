#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;
    const int MAX_HEALTH = 3;
    const int MAX_HUNGER = 5;
    const int MAX_THIRST = 3;
class Player {
    public:
    Player(int x, int y){
        health = MAX_HEALTH;
        hunger = MAX_HUNGER;
        thirst = MAX_THIRST;
        
        this->x = x;
        this->y = y;
        this->score = 0;
    }
    
    int getScore() const {
        return score;
    }
    
    void takeDamage(int val){
        this->health -= val;
        if(this->health < 0) this->health = 0;
    }
    
    void takeTurn(){
        this->thirst--;
        this->hunger--;
        
        if(this->thirst <= 0){
            this->health--;
            this->thirst = 0;
        }
        
        if(this->hunger <= 0){
            this->health--;
            this->hunger = 0;
        }
        
        this->score++;
    }
    
    string getStats() const {
        stringstream ss;
        ss  << "============\n"
            << "Health: " << this->health << "\n" 
            << "Hunger: " << this->hunger << "\n" 
            << "Thirst: " << this->thirst << "\n"
            << "============\n";
        return ss.str();
        ss.clear();
    }
    
    bool isAlive() const {
        return this->health > 0;
    }
    
    void increaseThrist(int val){
        //this->thirst = this->thirst + val;
        if(this->thirst > MAX_THIRST) this->thirst = MAX_THIRST;
    }
    
    void increaseHunger(int val){
        this->hunger += val;
        if(this->hunger > MAX_HUNGER) this->hunger = MAX_HUNGER;
    }
    
    int x, y;
    int health, hunger, thirst, score;

};

class Land {
    public:
    virtual string getDescription() = 0;
    virtual string visit(Player& player) = 0;
};

// TODO: Define at least 3 more types of derivded land types
// TODO: Add some unique effect to each new type

class Forest : public Land {
    public:
    string getDescription(){
        return "a densely wooded forest.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 74){
            player.takeDamage(1);
            return "You are attacked by a bear while foraging for berries.";
        } else {
            player.increaseHunger(1);
            return "You forage for berries in the woods and eat a few.";
        }
    }
};

class Lake : public Land {
    public:
    string getDescription(){
        return "a clear sparkling lake.";
    }
    
    string visit(Player& player){
        player.increaseThrist(2);
        return "You visit the lake and drink its clean water";
    }
};
class Hospital: public Land {
    public: string getDescription() {
        return (" A hospital and it will restore your health when you take the medicine");
    }
    string visit(Player & p) {
        p.health = MAX_HEALTH; // maximize the health
        return ("Your health is maximized\n"); 
    }

};
class IcedLand: public Land {
    public: string getDescription() {
        return (" An Iced land and it will decrease your health by 1");
    }
    string visit(Player & p) {
        p.health = p.health-1; // decrement health by 1
        return "You cold";
    }

};
class Farm : public Land{
    public: string getDescription(){
        return (" A farm and it will increase your hunger by 1"); 
        
    }
    string visit(Player&p){
        p.hunger +=1; 
        return (" Your hunger was increased by 1");
    }
};
class Camp: public Land{
    public: string getDescription(){
        return (" A camp and it will increase your health and hunger by 1"); 
    }
    string visit(Player &p ){
        p.hunger+=1; 
        p.thirst+=1; 
        return (" Your hunger and thirst were increased by 1"); 
    }
};
class BasketBallField: public Land{
    public: string getDescription(){
        return (" A basket ball field which will decrease your thirst by 2"); 
    }
    string visit(Player&p){
        p.thirst-=2; 
    }
};
class HauntedHouse: public Land {
    public: 
    stringstream sss;
    int randomH;
    string getDescription() {
         randomH = (rand() % 100); // this random variable controls what is going to be your challenge in the haunted house

        if (randomH < 25) { // if the random variable is less than 25 then the player will have a math problem

             sss<<" You see a haunted house and in order to survive through here you need to solve the following Maths problem\n";
            if (randomH < 13) { // 1st question
                sss<< " 10 + 20 * 30 +50/70";
            } else { //2nd question 
                sss<< "(10^2)*(10^3)-10";
            }
        } else if (randomH < 50) {// if the random variable is less than 50 and higher than 25 then the player will have a riddle 
                sss<<" You see a haunted house and in order to survive through here you need to solve the following riddle (ALL CAPS)\n";
            if (randomH < 38) { // 1st question
                 sss<<" What can run but  can't walk?";
            } else { //2nd question
                sss<<" What starts with T, filled with T, ends with T?";
            }

        } else if (randomH < 75) {// if the random variable is less than 75 and higher than 50 then the player will have a historical question 
            sss<<"You see a haunted house and in order to survive through here you need to answer the following history questions\n";
            if (randomH < 63) { // 1st question
               sss<<" Who built the pyramids?\n 1- Ancient Egyptians \n 2- Ancient Romans\n 3- Ottomans \n 4- Mongolos";
            } else { //2nd question
                sss<<" What was the name of the Egyptian president in 1973?\n 1- Anwar Elsadat\n 2- Gamal Abdelnaser\n 3- Hosny Mubarak\n 4-Mohamed Nageeb";
            }
        } else { // if the random variable is less than 100 and higher than 75 then the player will have a historical question 
            sss<<"You see a haunted house and in order to survive through here you need to answer the following questions (numbers or ALL CAPS)\n";
            if (randomH < 88) { // 1st question 
                sss<<" How many states in the United States?";

            } else { //2nd question
                sss<<"How many continents are in the world?";
            }
        }
        return sss.str();
        sss.clear(); // clear the buffer each time it returns 
    }
    string visit(Player & p) {
        double input = 0; //takes the input for the mathematical questions
        if (randomH < 25) {
            int count1 = 0;
            while (count1 < 1) {
                cin >> input;
                if (randomH < 13) {
                    if (input == 610 || input == 611) { // this is the right answer for the first challenge 
                        return ("That's correct, Great job\n");
                        ++count1;
                    } else {
                        return ("That's incorrect\n your health was decreases by 1");
                        p.health = p.health-1; //decrement health by 1 if he answeres incorrectly
                    }
                } else {
                    if (input == 0) { // this is the right answer for the first challenge 
                        return ("that's correct\n Great job\n");
                        ++count1;
                    } else {
                        return ("That's incorrect\n your health was decreases by 1");
                        p.health = p.health-1;
                    }
                }
            }
        } else if (randomH < 50) { 
            string input;
            int count1 = 0;
            while (count1 < 1) {
                cin >> input;
                if (randomH < 38) {
                    if (input == "RIVER" || input == "THE RIVER") { // This is the right answer
                        return ("that's correct\n Great job\n");
                        ++count1; // let him out 
                    } else { // if he answered incorrectly 
                        return ("That's incorrect\n your health was decreases by 1");
                        p.health = p.health-1;// decrement health by 1 
                    }
                } else {
                    if (input == "TEAPOT" || input == "THE TEAPOT") { 
                        return ("that's correct\n Great job\n");
                        ++count1;
                    } else {
                        return ("That's incorrect\n your health was decreases by 1");
                        p.health = p.health-1;
                    }
                }
            }
        } else if (randomH < 75) {
            int input = 0;
            int count1 = 0;
            while (count1 < 1) {
                cin >> input;
                if (randomH < 63) {
                    if (input == 1) {
                        return ("that's correct\n Great job\n");
                        ++count1; 
                    } else {
                        return ("That's incorrect\n your health was decreases by 1");
                        p.health = p.health-1;
                    }
                }
                if (input == 1) {

                    return ("that's correct\n Great job\n");
                    ++count1;
                } else {
                    return ("That's incorrect\n your health was decreases by 1");
                   p.health = p.health-1;
                }
            }
        } else {
            string input;
            int count1 = 0;
            while (count1 < 1) {
                cin >> input;

                if (randomH < 88) {
                    if (input == "50" || input == "FIFTY") {

                        return ("that's correct\n Great job\n");
                        ++count1;
                    } else {
                        return ("That's incorrect\n your health was decreases by 1");
                        p.health = p.health-1;
                    }
                } else {
                    if (input == "7" || input == "SEVEN") {
                        return ("that's correct\n Great job\n");
                        ++count1;
                    } else {
                        return ("That's incorrect\n your health was decreases by 1");
                        p.health = p.health-1;
                    }
                }
            }
        }

    }

};
class LivesShop: public Land {
    public: string getDescription() {
        return (" A lives shop and it will increase your health by 1");
    }
    string visit(Player & p) {
        p.health = MAX_HEALTH; // increase lives from the lives shop 
        return ("Your health is maximized\n"); 
    }

};
class GroceryStore: public Land { 

    public: string getDescription() {
        return (" A grocery store and it will restore your hunger to the max");
    }
    string visit(Player & p) {
        p.hunger = MAX_HUNGER; // maximize hunger from the grocery store
        return ("Your hunger is stored to max\n"); 
    }
};
const int MAP_SIZE = 10;
Land* map[MAP_SIZE][MAP_SIZE];

void populateMap(){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            // TODO: Modify this code to add your new land types
            int randomNum = rand() % 9;
            switch(randomNum){
                case 0: // Forest
                    map[i][j] = new Forest;
                    break;
                case 1: // Lake
                    map[i][j] = new Lake;
                    break;
                case 2: // Lake
                    map[i][j] = new HauntedHouse;
                    break;
                case 3: // Lake
                    map[i][j] = new LivesShop;
                    break;
                case 4: // Lake
                    map[i][j] = new GroceryStore;
                    break;
                case 5: // Lake
                    map[i][j] = new IcedLand; 
                    break;
                case 6: // Lake
                    map[i][j] = new Hospital;
                case 7: 
                    map[i][j] = new Farm;
                    break; 
                case 8: 
                    map[i][j] = new Camp; 
                    break;
                default:
                    cout << "Invalid land type selected" << endl;
                    break;
            }
        }
    }
}

int main(){
    srand(time(0));
    
    populateMap();
    
    Player player(MAP_SIZE/2, MAP_SIZE/2);
    
    cout << "You wake up and find yourself lost in the middle of a strange wilderness." << endl;
    
    // TODO: Handle boundary conditions (e.g., if index out of bounds north, you index the south-most location)
    
    while(player.isAlive()){
                if (player.x > 9) {
            player.x=0;
        } else if (player.x < 0) {
            player.x = 9;
        }
        if (player.y > 9) {
            player.y=0;
        } else if (player.y) {
            player.y = 9;
        }
        cout << "To the north you see " << map[player.x][player.y - 1]->getDescription() << endl;
        cout << "To the east you see " << map[player.x + 1][player.y]->getDescription() << endl;
        cout << "To the south you see " << map[player.x][player.y + 1]->getDescription() << endl;
        cout << "To the west you see " << map[player.x - 1][player.y]->getDescription() << endl;
        
        cout << "Which way will you go? Enter N, E, S, or W:" << endl;
        char userInput;
        cin >> userInput;
        
        switch(userInput){
            case 'N':
                player.y = player.y - 1;
                break;
            case 'E':
                player.x = player.x + 1;
                break;
            case 'S':
                player.y = player.y + 1;
                break;
            case 'W':
                player.x = player.x - 1;
                break;
            default:
                break;
        }
        
        cout << map[player.x][player.y]->visit(player) << endl;
        
        cout << player.getStats() << endl;
        player.takeTurn();
    }
    
    cout << "You died." << endl;
    cout << player.getScore() << endl;
    
    return 0;
}