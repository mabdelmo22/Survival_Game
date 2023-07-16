#include <iostream>
#include <sstream>
#include <time.h> 
#include "survival.h"
using namespace std; 


    Player::Player(){
               this -> health = max_health; 
        this -> hunger = max_hunger;
        this -> thirst = max_thirst;
        this -> lives = max_lives;
        this -> x = start_point;
        this -> y = start_point; 
    }
    int getScore() {
        return score;
    }
    int getHunger() {
        return this -> hunger;
    }
    int getHealth() {
        return this -> health;
    }
    int getLives() {
        return this -> lives;
    }
    int getThirst() {
        return this -> thirst;
    }
    void setHunger(int hunger) {
        this -> hunger = hunger;
    }
    void setHealth(int health) {
        this -> health = health;
    }
    void setScore(int score) {
        this -> score = score;
    }
    void setThirst(int thirst) {
        this -> thirst = thirst;
    }
    void setLives(int lives) {
        this -> lives = lives;
    }
    bool isAlive() { // check if the lives are 0 if so then the player died (return false and get out of the while loop - look at line 437)
        if (lives > 0) {
            return true;
        } else {
            return false;
        }
    }
    void setXposition(int x) { 
        this -> x = x;
    }
    void setYposition(int y) {
        this -> y = y;
    }
    int getXposition() {
        return x;
        
    }
    int getYposition() {
        return y;
    }
    void affectHealth(int health) { // a function that affects the health of the player based on the land
        this -> health += health;
        if (this->health>max_health){
            this->health = max_health;
        }
    }
    void affectThirst(int thirst) { // a function that affects the thirst of the player based on the land
        this -> thirst += thirst;
        if (this->thirst>max_thirst){
            this->thirst=max_thirst; 
        }
    }
    void affectLives(int lives) { // a function that affects the lives of the player based on the land
        this -> lives += lives;
        if (this->lives>max_lives){
            this->lives = max_lives;
        }
    }
    void affectHunger(int hunger) { // a function that affects the hunger of the player based on the land
        this -> hunger += hunger;
        if (this->hunger>max_hunger){
            this->hunger=max_hunger; 
        }
    }
    string getStats() const{ // a function to return the stats of the player
    stringstream ss;
        ss  << "Your health is:" << this->health << "\n"
            << "your hunger is:" << this->hunger << "\n" 
            << "Your thirst is:" << this->thirst << "\n"
            << "Your lives are:" <<this->lives<<"\n"
            <<"Your score is: "<<this->score<<"\n";
            return ss.str();
    }
    void takeTurn(){ // this function is used to decrement the thirst and the hunger each time the player makes a movement
        this->hunger--; 
        this->thirst--;
        ++this->score; 
        if (this->hunger<=0|| this->thirst<=0){ // if thirst and hunger < or = zero then decrease health and maximize them back
        this->health--; 
        this-> hunger = max_hunger; 
        this->thirst = max_thirst; 
        if (this->health<=0){ // if health, hunger, and thirst are less than or equal zero then decrease lives and maximize them back
            this->health = max_health; 
            this-> hunger = max_hunger; 
            this->thirst = max_thirst; 
            this->lives--; 
        }
        }
        
    }
    private: 
    int score;
    int health;
    int thirst;
    int lives;
    int hunger;
    int x, y;
};
class Land { // the land class is the base class for all the lands and it is an abstract so you can't initialize objects for it. 
    public:
    virtual string getDescription() = 0; 
    virtual string visit(Player & player) = 0;
    void endGame(Player & player) { /* a function that's not virtual that can give the player access to end the game, 
     we are using pass by reference so that the object that's passed as a parameter gets modified as the player object gets modified */ 
        char choice; // a character that is used to take input to decide if the user wants to end the game or no
        int loop_count = 0;
        cout << "Would you like to end the game(y/n)" << endl;
        while (loop_count == 0) { 
            cin >> choice;
            
            if (choice == 'y' || choice == 'Y') {
                cout << "Closing the game..." << endl;
                cout << "Your score is: " << player.getScore()<<endl;
                exit(0);
            } else if (choice == 'n' || choice == 'N') {
                cout << "Contiuing the game" << endl;
                ++loop_count;

            } else {
                cout << "Your response is wrong, please reinput" << endl;
            }
        }

    }



};
class Forest: public Land { // a class that's inherited from land and it is a different kind of land (in this game there are 7 different kinds of lands)
    public: 
    


    string getDescription() { // describe this land (If you notice here we are using polymorphism as we used this function from the base class) you will see it in every land
        return ("A forest (There is a possibilty that there is an animal)");

    }
    string visit(Player & p) { /* This function is the function that has the actual game and effects of being in the forest on the player (its also polymorphic) 
     You will see it in all the lands
     
        */
        int random =(rand() % 3); // determines the type of animal in the forest (if 3 then no animals)
        stringstream ssss; 
        if (random == 0) {
            ssss<<"There is a lion in this forest\n"
            <<"Your lives were decremented by 1\n";
            p.affectLives(-1); // reduce lives by 1
            return ssss.str(); 
            ssss.clear();
        } else if (random == 1) {
            ssss<<"There is a tiger in this forest\n"
            <<"Your health was decremented by 2\n";
            p.affectHealth(-2); // reduce health by 2
            return ssss.str(); 
            ssss.clear(); 
        } else if (random == 2) {
            ssss<<"There is a crocodile in this forest\n"
            <<"Your health was decremented by 1\n";
            p.affectHealth(-1); // reduce health by 1
            return ssss.str(); 
            ssss.clear();                 
        } else {
            return ("This forest is safe there is no animals in this forest\n");
            // if the number is not one of the previous then there is no animal
        }
    }



};
class Lake: public Land {
    public: string getDescription() {
        return ("A lake and it will restore your thirst when you drink from its water" );
    }
    string visit(Player & p) {
        p.setThirst(max_thirst); // if he is in the lake, then maximize his thirst 
        return ("Your thirst was restored to maximum");
    }
};
class Hospital: public Land {
    public: string getDescription() {
        return ("A hospital and it will restore your health when you take the medicine");
    }
    string visit(Player & p) {
        p.setHealth(max_health); // maximize the health
        return ("Your health was maximized"); 
    }

};
class IcedLand: public Land {
    public: string getDescription() {
        return ("An Iced land and it will decrease your health by 1");
    }
    string visit(Player & p) {
        p.affectHealth(-1); // decrement health by 1
        return ("Your health was decremented by 1"); 
    }

};
class HauntedHouse: public Land {
    public: int randomH; // this random variable controls what is going to be your challenge in the haunted house
    stringstream sss; 
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

                cin >> input;
                if (randomH < 13) {
                    if (input == 610 || input == 611) { // this is the right answer for the first challenge 
                        return ("That's correct\n Great job\n");
                        
                    } else {
                        p.affectHealth(-1); //decrement health by 1 if he answeres incorrectly
                        return ("That's incorrect\n your health was decreases by 1");
                        
                    }
                } else {
                    if (input == 0) { // this is the right answer for the first challenge 
                        return ("that's correct\n Great job\n");
                    } else {
                        p.affectHealth(-1);
                        return ("That's incorrect\n your health was decreases by 1");
                       
                    }
                }
            
        } else if (randomH < 50) { 
            string input;
                cin >> input;
                if (randomH < 38) {
                    if (input == "RIVER" || input == "THE RIVER") { // This is the right answer
                        return ("that's correct\n Great job\n");
                    } else { // if he answered incorrectly
                    p.affectHealth(-1); // decrement health by 1 
                        return ("That's incorrect\n your health was decreases by 1");
                        
                    }
                } else {
                    if (input == "TEAPOT" || input == "THE TEAPOT") { 
                        return ("that's correct\n Great job\n");
                    } else {
                        p.affectHealth(-1);
                        return ("That's incorrect\n your health was decreases by 1");
                        
                    }
                }
            
        } else if (randomH < 75) {
            int input = 0;
                cin >> input;
                if (randomH < 63) {
                    if (input == 1) {
                        return ("that's correct\n Great job\n");
                    } else {
                        p.affectHealth(-1);
                        return ("That's incorrect\n your health was decreases by 1");
                        
                    }
                }
                if (input == 1) {

                    return ("that's correct\n Great job\n");
                } else {
                    p.affectHealth(-1);
                    return ("That's incorrect\n your health was decreases by 1");
                    
                }
            
        } else {
            string input;
                cin >> input;

                if (randomH < 88) {
                    if (input == "50" || input == "FIFTY") {

                        return ("that's correct\n Great job\n");
                    } else {
                        p.affectHealth(-1);
                        return ("That's incorrect\n your health was decreases by 1");
                        
                    }
                } else {
                    if (input == "7" || input == "SEVEN") {
                        return ("that's correct\n Great job\n");
                    } else {
                        p.affectHealth(-1);
                        return ("That's incorrect\n your health was decreases by 1");
                        
                    }
                }
            
        }

    }

};
class LivesShop: public Land {
    public: string getDescription() {
        return ("A lives shop and it will increase your health by 1");
    }
    string visit(Player & p) {
        p.affectLives(1); // increase lives from the lives shop 
        return ("Your lives were increased by 1");
    }

};
class GroceryStore: public Land { 

    public: string getDescription() {
        return ("A grocery store and it will restore your hunger to the max");
    }
    string visit(Player & p) {
        p.setHunger(max_hunger); // maximize hunger from the grocery store
        return ("Your hunger was set to the max");
    }
};
class StartPoint: public Land {
    public: string getDescription() {
        return ("your starting point");
    }
    string visit(Player & p) {
        return ("Back to the begining");
    }


};


char lands[7] = {'F','L','H','I','h','l', 'G'};
/*  F stands for forest, L stands for lake, H stands for hospital, I stands for 
 * Iced land,
h stands for haunted house, l stands fo lives shop, G stands for grocery store

 */
char map_char[10][10]; // a charachter array that have the symbols for different lands 
Land * map[10][10]; // The actual array that has the lands 
void MakeMap(Player & p) {
    
    for (int i = 0; i < 10; ++i) { // randomly assign the characters 
        for (int j = 0; j < 10; ++j) {
            int randMap = (rand() % 6); // the random number that is used to populate the map 
            map_char[i][j] = lands[randMap];

        }
    }
    start_point = (rand() % 9); // randomly make the starting point between 0 and 9
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == start_point && j == start_point) {
                map[i][j] = new StartPoint;
                p.setXposition(i); // set the x starting point 
                p.setYposition(i); // set the y starting point 
            } else {
                switch (map_char[i][j]) {// populate the array 
                    case 'F':
                        map[i][j] = new Forest;
                        break;
                    case 'L':
                        map[i][j] = new Lake;
                        break;
                    case 'H':
                        map[i][j] = new Hospital;
                        break;
                    case 'I':
                        map[i][j] = new IcedLand;
                        break;
                    case 'h':
                        map[i][j] = new HauntedHouse;
                        break; 
                    case 'l':
                        map[i][j] = new LivesShop;
                        break; 
                    case 'G':
                        map[i][j] = new GroceryStore;
                        break; 

                }
            }


        }
    }
}
int main() {
    srand(time(0));
    Player Mohamed;
    MakeMap(Mohamed);
    char moveChoice;
    
    while (Mohamed.isAlive()) {
        if (Mohamed.getYposition() ==9){
            cout << "You have to the North " << map[Mohamed.getXposition()][0] -> getDescription() << endl;
        }
        else {
            cout << "You have to the North " << map[Mohamed.getXposition()][Mohamed.getYposition() +1] -> getDescription() << endl;
        }
        if (Mohamed.getYposition()==0){
            cout << "You have to the South " << map[Mohamed.getXposition()][9] -> getDescription() << endl;
        }
        else{
            cout << "You have to the South " << map[Mohamed.getXposition()][Mohamed.getYposition() - 1] -> getDescription() << endl;
        }
        
        if (Mohamed.getXposition()==9){
            cout << "You have to the East " << map[0][Mohamed.getYposition() ] -> getDescription() << endl;
        }
        else{
            cout << "You have to the East " << map[Mohamed.getXposition() +1][Mohamed.getYposition() ] -> getDescription() << endl;
        }
        
        if (Mohamed.getXposition()==0){
            cout << "You have to the West " << map[9][Mohamed.getYposition() ] -> getDescription() << endl;
        }
        else{
            cout << "You have to the West " << map[Mohamed.getXposition() -1][Mohamed.getYposition() ] -> getDescription() << endl;
        }
        
        
        cout << "Choose where to go (N-S-E-W)" << endl;       
        int counter = 0;
        while (counter == 0) {
            cin >> moveChoice;
            switch (moveChoice){ // moves the player based on the choice of him. 
            case  'N': 
                if (Mohamed.getYposition()==9){
                    Mohamed.setYposition(0);
                    ++counter;
                }
                else{
                    Mohamed.setYposition(Mohamed.getYposition() + 1);
                    ++counter;                    
                }
                break;

            case  'n' :
                if (Mohamed.getYposition()==9){
                    Mohamed.setYposition(0);
                    ++counter;
                }
                else{
                    Mohamed.setYposition(Mohamed.getYposition() + 1);
                    ++counter;                    
                }
                break;

            case  'S':
                if (Mohamed.getYposition()==0){
                    Mohamed.setYposition(9);
                    ++counter;
                }
                else{
                    Mohamed.setYposition(Mohamed.getYposition() - 1);
                    ++counter;                    
                }
                break;

            case  's':
                if (Mohamed.getYposition()==0){
                    Mohamed.setYposition(9);
                    ++counter;
                }
                else{
                    Mohamed.setYposition(Mohamed.getYposition() - 1);
                    ++counter;                    
                }
                break;

            case  'W':
                if (Mohamed.getXposition()==0){
                    Mohamed.setXposition(9);
                    ++counter;
                }
                else{
                    Mohamed.setXposition(Mohamed.getXposition() - 1);
                    ++counter;                    
                }
                break;

            case  'w':
                if (Mohamed.getXposition()==0){
                    Mohamed.setXposition(9);
                    ++counter;
                }
                else{
                    Mohamed.setXposition(Mohamed.getXposition() - 1);
                    ++counter;                    
                }
                break;

            case  'E':
                if (Mohamed.getXposition()==9){
                    Mohamed.setXposition(0);
                    ++counter;
                }
                else{
                    Mohamed.setXposition(Mohamed.getXposition() + 1);
                    ++counter;                    
                }
                break;

            case  'e':
                if (Mohamed.getXposition()==9){
                    Mohamed.setXposition(0);
                    ++counter;
                }
                else{
                    Mohamed.setXposition(Mohamed.getXposition() + 1);
                    ++counter;                    
                }
                break;

            default : 
                counter = 0;
                break;

        }


    }
        
        
        cout<<map[Mohamed.getXposition()][Mohamed.getYposition()] -> visit(Mohamed)<<endl; // Call the methods in the lands based on the position
        Mohamed.takeTurn();  // call the take turn method to affect his stats
        
        
        cout << Mohamed.getStats() << endl;
        map[Mohamed.getXposition()][Mohamed.getYposition()] -> endGame(Mohamed);// ask him if he wants to end the game or no 
         

}
        cout<<"You died, Loser HAHAHAHAHA" <<endl;  


}

