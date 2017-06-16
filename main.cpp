/************************* Snake - A Video Game. Built with C++ *************************/
/*************************         By Brandon Ikeda             *************************/



/*************************   Start   *************************/

#include <iostream>
using namespace std;

/************************* Variables *************************/

bool gameOver; // Trigger
const int width = 20; // Map Dimensions
const int height = 20; // Map Dimensions
int x, y; // Head Position
int fruitX, fruitY; // Fruit Position
int score; // Score
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN}; // Direction of Snake
eDirecton dir; // Direction of the Snake

// Basic functions
void Setup(){
    gameOver = false; // Trigger
    dir = STOP; // Still
    x = width / 2; // Start centered
    y = height / 2; // Start centered
    fruitX = rand() % width; // Random fruit location
    fruitY = rand() % height; // Random fruit location
    score = 0; // Score initalized at 0
}

void Draw(){
    system("clear"); // Clear map
    
    // Print walls
    for (int i = 0; i < width; i++) 
        cout << "#";
    cout << endl;
    
    for (int i = 0; i < height; i++){
        
        for (int j = 0; j < width; j++){
            
           if (j == 0)
               cout << "#";
            else
                cout << "#";
                
            if (j == width-1)
                cout << "#";
           
        }
    } 
    
    for (int i = 0; i < width; i++) 
        cout << "#";
    cout << endl;
    
}

void Input(){
    
}

void Logic(){
    
}

/*************************   Main   *************************/
int main(){
    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        //Sleep(10);
    }
    return 0;
}