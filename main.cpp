#include <iostream>
#include <sstream>
#include <time.h> 
#include"survival.h"
using namespace std;

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

