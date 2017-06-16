/************************* Snake - A Video Game. Built with C++ *************************/
/*************************         By Brandon Ikeda             *************************/



/*************************   Start   *************************/

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
 
int _kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

char _getch(){
    #include <unistd.h>   //_getch*/
    #include <termios.h>  //_getch*/
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
 }
using namespace std;

/************************* Variables *************************/

bool gameOver; // Trigger
const int width = 50; // Map Dimensions
const int height = 20; // Map Dimensions
int x, y; // Head Position
int fruitX, fruitY; // Fruit Position
int tailX[100], tailY[100]; // Tail max
int nTail; // Tail current
int score; // Score
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN}; // Direction of Snake
eDirecton dir; // Direction of the Snake

/************************* Functions *************************/
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
    // Intro Display
    cout << "     Snake - A C++ Video Game By Brandon Ikeda"<< endl;
    cout << "Eat all the fruit, but don't hit the wall or yourself!" <<  endl;
    for (int i = 0; i < width + 2; i++)
        cout << "#"; // Top wall
    cout << endl;
    
    for (int i = 0; i < height; i++){
        
        for (int j = 0; j < width; j++){
            
           if (j == 0)
               cout << "#"; // Left wall
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else{
                bool print = false;
                for (int k = 0; k < nTail; k++){
                    if (tailX[k] == j && tailY[k] == i){
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                        cout << " ";
            }
            if (j == width - 1)
               cout << "#"; // Right wall
           
        }
        cout << endl;
    } 
    
    for (int i = 0; i < width + 2; i++) 
        cout << "#"; // Bottom wall
    cout << endl;
    // Intro Display
    cout << "       YOUR SCORE:" << score << "        HIGHSCORE:" << 100000 <<  endl;
    cout << "   Controls: W = UP, A = LEFT, D = RIGHT, S = DOWN" <<  endl;
    cout << "   Press any direction to play or press X to quit" << endl;
    
}

void Input(){
    // Get user input
    if (_kbhit()){
        switch (_getch()){
            case 'w':
                dir = UP;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        
        }
    }
}

void Logic(){
    
    // Tail
    int prevX = tailX[0]; //Rememeber previous X co-ordinate
    int prevY = tailY[0]; //Rememeber previous Y co-ordinate
    int prev2X;
    int prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    // Move Snake
    switch(dir){
        case UP:
            y--;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (x > width || x < 0 || y > height || y < 0){
        cout << "####################################################" << endl;
        cout << "   GAME OVER - YOU HIT THE WALL. FINAL SCORE:" << score << endl;
        cout << "####################################################" << endl;
        gameOver = true; // Gameover if user exits map
    }
    for (int i = 0; i < nTail; i++){
        if(tailX[i] == x && tailY[i] == y){
            cout << "####################################################" << endl;
            cout << "   GAME OVER - YOU HIT YOURSELF. FINAL SCORE:" << score << endl;
            cout << "####################################################" << endl;
            gameOver = true;
        }
    }
    if (x == fruitX && y == fruitY){
        nTail++; // Grow from eating the fruit
        score += 10; // Increment score
        fruitX = rand() % width; // Spawn new random fruit location
        fruitY = rand() % height; // Spawn new random fruit location
    }
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