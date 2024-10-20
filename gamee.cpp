#include <iostream>
#include <cstdlib> // I have used this for rand() and srand() builtin functions
#include <ctime>   // I have used this for time() and clock() builtin functions
#include <stack>   //I have used thus for storing move , coins and keys history
#include <thread> // I have used this library for sleep
using namespace std;
class Node {
public:
    bool isStar; 
    bool isBomb; 
    bool isCoin; 
    bool isPlayer; 
    bool isKey; 
    bool isDoor; 
    Node* up;
    Node* down;
    Node* left;
    Node* right;

    Node() {
        isStar = false;
        isBomb = false;
        isCoin = false;
        isPlayer = false;
        isKey = false;
        isDoor = false;
        up = nullptr;
        down = nullptr;
        left = nullptr;
        right = nullptr;
    }
};
void createGrid(Node** grid, int gridSize) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = Node();
            grid[i][j].isStar = true;
        }
    }
  for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (i > 0) grid[i][j].up = &grid[i - 1][j];
            if (i < gridSize - 1) grid[i][j].down = &grid[i + 1][j]; 
            if (j > 0) grid[i][j].left = &grid[i][j - 1]; 
            if (j < gridSize - 1) grid[i][j].right = &grid[i][j + 1]; 
        }
    }
}

void placeBombs(Node** grid, int gridSize, int maxBombs) {
    srand(static_cast<unsigned>(time(0))); 

    int bombsPlaced = 0;

    while (bombsPlaced < maxBombs) {
        int randomRow = rand() % gridSize;
        int randomCol = rand() % gridSize;

  
        if (grid[randomRow][randomCol].isStar) {
            grid[randomRow][randomCol].isBomb = true; 
            grid[randomRow][randomCol].isStar = false; 
            bombsPlaced++;
        }
    }
}

void placeCoins(Node** grid, int gridSize, int maxCoins) {
    srand(static_cast<unsigned>(time(0))); 
    int coinsPlaced = 0;
    while (coinsPlaced < maxCoins) {
        int randomRow = rand() % gridSize;
        int randomCol = rand() % gridSize;
        if (grid[randomRow][randomCol].isStar) {
            grid[randomRow][randomCol].isCoin = true; 
            grid[randomRow][randomCol].isStar = false; 
            coinsPlaced++;
        }
    }
}



int calculateTotalMoves(Node** grid, int gridSize, int playerRow, int playerCol) {
    int keyRow, keyCol, doorRow, doorCol;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j].isKey) {
                keyRow = i;
                keyCol = j;
            }
            if (grid[i][j].isDoor) {
                doorRow = i;
                doorCol = j;
            }
        }
    }
    int distanceToKey = abs(playerRow - keyRow) + abs(playerCol - keyCol);
    int distanceToDoor = abs(keyRow - doorRow) + abs(keyCol - doorCol);
    int totalMoves = distanceToKey + distanceToDoor;

    return totalMoves;
}

void manageCoins(Node** grid, int gridSize, int maxCoins) {
    while (true) {
       std::this_thread::sleep_for(std::chrono::seconds(10)); 
       // Clear existing coins and instead replace them wit stars
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (grid[i][j].isCoin) {
                    grid[i][j].isCoin = false; 
                    grid[i][j].isStar = true; 
                }
            }
        }

        placeCoins(grid, gridSize, maxCoins);  // reposioned coins //new coins
    } 
}

void placePlayers(Node** grid, int gridSize, int &playerRow, int &playerCol) {
    srand(static_cast<unsigned>(time(0))); 
    int playersPlaced = 0;
    
    while (playersPlaced < 1) {  //only a single player
        int randomRow = rand() % gridSize;
        int randomCol = rand() % gridSize;

        // Place a player if it is a star
        if (grid[randomRow][randomCol].isStar) {
            grid[randomRow][randomCol].isPlayer = true;
            grid[randomRow][randomCol].isStar = false; 
            playerRow = randomRow; 
            playerCol = randomCol; 
            playersPlaced++;
        }
    }
}
void placeKeys(Node** grid, int gridSize, int maxKeys) {
    srand(static_cast<unsigned>(time(0))); 
    int keysPlaced = 0;
    while (keysPlaced < maxKeys) {
        int randomRow = rand() % gridSize;
        int randomCol = rand() % gridSize;
        if (grid[randomRow][randomCol].isStar) {
            grid[randomRow][randomCol].isKey = true; // Place a key
     //         grid[randomRow][randomCol].isStar = false; // Remove this line for hiding
           
            // Keep star as that keys are invisible
            keysPlaced++;
        }
    }
}
void placeDoors(Node** grid, int gridSize, int maxDoors) {
    srand(static_cast<unsigned>(time(0))); 
    int doorsPlaced = 0;
    
    while (doorsPlaced < maxDoors) {
        int randomRow = rand() % gridSize;
        int randomCol = rand() % gridSize;
        if (grid[randomRow][randomCol].isStar) {
            grid[randomRow][randomCol].isDoor = true; // Place a door
      //       grid[randomRow][randomCol].isStar = false; // Remove star //remove this line  to hide door and also remove isdoor of grid
        
            doorsPlaced++;
        }
    }
}

void InitialStateplaceKeys(Node** grid, int gridSize,int maxKeys) {
    srand(static_cast<unsigned>(time(0))); 
    int keysPlaced = 0;
 while (keysPlaced < maxKeys) {
        int randomRow = rand() % gridSize;  
        int randomCol = rand() % gridSize;  
        if (grid[randomRow][randomCol].isStar) {
            grid[randomRow][randomCol].isKey = true; 
             grid[randomRow][randomCol].isStar = false; 
            keysPlaced++;
        }
    }
}


void InitialStateplaceDoors(Node** grid, int gridSize , int maxDoors) {
    srand(static_cast<unsigned>(time(0))); 
    int doorsPlaced = 0;
 while (doorsPlaced < maxDoors) {
        int randomRow = rand() % gridSize;  
        int randomCol = rand() % gridSize;  
        if (grid[randomRow][randomCol].isStar) {
            grid[randomRow][randomCol].isDoor = true; 
           grid[randomRow][randomCol].isStar = false; //remove this line  to hide door and also remove isdoor of grid
            doorsPlaced++;
        }
    }
}

void printGrid(Node** grid, int gridSize) {

    cout << "||";
    for (int j = 0; j < gridSize; j++) {
        cout << "||" ;
    }
    cout << "||" << endl;
    for (int i = 0; i < gridSize; i++) {
        cout << "||"; 
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j].isBomb) {
                cout << " B"; // Display bomb as 'B'
            } else if (grid[i][j].isCoin) {
                cout << " C"; // Display coin as 'C'
            } else if (grid[i][j].isPlayer) {
                cout << " P"; // Display player as 'P'    
            } else if (grid[i][j].isStar) {
                cout << " *"; // Display star 
            }
         //   else if (grid[i][j].isKey) {
           //     cout << " K"; invisible keys 
         //   }
        //    else if (grid[i][j].isDoor) {
          //      cout << " D"; // invisible  doors
            //}
            else {
                cout << "  "; 
            }
        }
        cout << "||" << endl; 
    }
    cout << "||";
    for (int j = 0; j < gridSize; j++) {
       cout << "||" ;
    }
   cout << "||" << endl;
}
void displaykeyCoordinates(stack<pair<int, int>> coinHistory);
void displayCoinCoordinates(stack<pair<int, int>> coinHistory);
void InitialState(Node** grid, int gridSize , int maxKeys , int maxDoors);
bool movePlayer(Node** grid, int gridSize, int &total_coins,int &score, int &playerRow,int &maxKeys,int & maxDoors, int &playerCol, const string &direction, stack<pair<int, int>> &moveHistory,int &undoCount, int maxUndos,bool &hasKey,stack<pair<int, int>> &coinHistory ,  stack<pair<int, int>> &keyHistory)  {
    moveHistory.push({playerRow, playerCol});
    Node* currentNode = &grid[playerRow][playerCol];
    //bool hasKey = false;
    const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;
const int NONE = 0;
int lastMoveDirection = NONE;
int currentMoveDirection = NONE;
    if (direction == "up" && currentNode->up) {
        playerRow--;
    } else if (direction == "down" && currentNode->down) {
        playerRow++;
    } else if (direction == "left" && currentNode->left) {
        playerCol--;
    } else if (direction == "right" && currentNode->right) {
        playerCol++;
    } else {
        cout << "Invalid!!!!" << endl;
        return false;
    }
    if ((currentMoveDirection == UP && lastMoveDirection == DOWN) ||
        (currentMoveDirection == DOWN && lastMoveDirection == UP) ||
        (currentMoveDirection == LEFT && lastMoveDirection == RIGHT) ||
        (currentMoveDirection == RIGHT && lastMoveDirection == LEFT)) {
        cout << "You cannot move back immediately!" << endl;
        playerRow = moveHistory.top().first; 
        playerCol = moveHistory.top().second;
        moveHistory.pop(); 
        return true;
    }
    lastMoveDirection = currentMoveDirection; 
    Node* newNode = &grid[playerRow][playerCol];
   if (newNode->isBomb) {
    cout << "Game Over!!!" << endl;
    cout<<"you have hit the bomb!!"<<endl;
    cout << "Items Collected :" << endl;
    displayCoinCoordinates(coinHistory);
    displaykeyCoordinates(keyHistory);
     InitialState(grid, gridSize, maxKeys, maxDoors);
   //   printGrid(grid,gridSize);
    return false;
     //   cout<<"Items collected :";
      //  if(newNode->isCoin){
            // cout << "(" << playerRow << "," << playerCol << ", c)" << endl;
    //    }
    } else if (newNode->isCoin) {
        cout << "Congratulations you have collected coin!!!" << endl;
        total_coins++;
        score=score+2;
         coinHistory.push({playerRow, playerCol}); // coordinates for coin
        cout<<endl;
        cout<<"total coins collected :"<<total_coins;
        cout<<endl;
        newNode->isCoin = false; 
        if (undoCount < maxUndos) {
            undoCount--;
            cout << "You have an additional undo now !!!!" << endl;
        }
    }
     else if (newNode->isKey) {
        cout << "You collected a key!" << endl;
      //  bool keyStatus;
              hasKey = true; 
        
        newNode->isKey = false; 
    }
     else if (newNode->isDoor) {
        // Only allow if player has boh key and entered door
      if (hasKey) {  
            cout << "You found a door and entered! " << endl;
            cout << "Congratulations! You have won the game!" << endl; 
            return false; // End the game
        } else {
           // cout << "You found a door but need a key to enter!" << endl;
            //  playerRow = moveHistory.top().first; // Reset to last position
           // playerCol = moveHistory.top().second;
            return true; 
        }
    }


//updating positions of the players
    currentNode->isPlayer = false; 
    currentNode->isStar=true;   
    newNode->isPlayer = true; 

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j].isKey) { 
                int distance = abs(playerRow - i) + abs(playerCol - j); 
             
              cout<<"Hint :";

                if (distance < 7) {
                    cout << "Getting closer to key!" << endl;
                } else if (distance < 3) {
                    cout << "Almost reached key!" << endl;            
                } else if (distance == 0) {
                    cout << "Reached key!" << endl;
                } else if (distance > 3) {
                    cout << "Getting further from key!" << endl;
                }
            }
        }
    }
    

    

    return true;
}
bool undoMove(Node** grid, int gridSize, int &playerRow, int &playerCol, stack<pair<int, int>> &moveHistory, int &undoCount, int maxUndos) {
if (undoCount >= maxUndos || moveHistory.empty()) {
    cout << "No more moves left" << endl;
    return false;
}
    pair<int, int> lastMove = moveHistory.top();
    moveHistory.pop();
    grid[playerRow][playerCol].isPlayer = false;
    grid[playerRow][playerCol].isStar = true;
    playerRow = lastMove.first;
    playerCol = lastMove.second;
    grid[playerRow][playerCol].isPlayer = true;
    cout<<"Remaining Undos"<<endl;
    undoCount++;
    cout << "Remaining Undos: " << (maxUndos - undoCount) << endl;
    return true;
}
void displayCoinCoordinates(stack<pair<int, int>> coinHistory) {
    while (!coinHistory.empty()) {
        pair<int, int> coin = coinHistory.top();
        cout << "(" << coin.first << ", " << coin.second << " ,c"<<")" << endl;
        coinHistory.pop();
    }
}
void displaykeyCoordinates(stack<pair<int, int>> keyHistory) {
    while (!keyHistory.empty()) {
        pair<int, int> key = keyHistory.top();
        cout << "(" << key.first << ", " << key.second << " ,k"<<")" << endl;
        keyHistory.pop();
    }
}
void InitialStateplaceKeys(Node** grid, int gridSize, int maxKeys);
void InitialStateplaceDoors(Node** grid, int gridSize, int maxDoors);
void InitialState(Node** grid, int gridSize, int maxKeys, int maxDoors) {
    cout << "This was the original state of the game:" << endl;
    InitialStateplaceKeys(grid, gridSize, maxKeys);
    InitialStateplaceDoors(grid, gridSize, maxDoors);

    // Print top boundary
    cout << "||";
    for (int j = 0; j < gridSize; j++) {
        cout << "||"; 
    }
    cout << "||" << endl;

    for (int i = 0; i < gridSize; i++) {
        cout << "||"; 
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j].isBomb) {
                cout << " B"; // Display bomb as 'B'
            } else if (grid[i][j].isCoin) {
                cout << " C"; // Display coin as 'C'
            } else if (grid[i][j].isPlayer) {
                cout << " P"; // Display player as 'P'
            } else if (grid[i][j].isStar) {
                cout << " *"; // Display star
            } else if (grid[i][j].isKey) {
                cout << " K"; // Display key as 'K'
            } else if (grid[i][j].isDoor) {
                cout << " D"; // Display door as 'D'
            } else {
                cout << "  "; 
            }
        }
        cout << "||" << endl; 
    }
    cout << "||";
    for (int j = 0; j < gridSize; j++) {
        cout << "||"; 
    }
    cout << "||" << endl;
}

int main() {
     int maxBombs = 6; 
     int maxCoins = 18; 
     int maxKeys = 1; 
     int maxDoors = 1; 
  bool hasKey = false; 
    int total_coins = 0;
    int score=0;
        // Stack 
    stack<pair<int, int>> moveHistory;
    stack<pair<int, int>> coinHistory;
     stack<pair<int, int>> keyHistory;
    int maxUndos;
    int undoCount = 0;
    int gridSize;
    srand(static_cast<unsigned>(time(0)));
    char difficulty;
    cout << "Select difficulty level:"<<endl;
    cout<<"Enter 'e' for Easy"<<endl;
    cout<<"Enter 'm' for Medium"<<endl;
    cout<<"Enter 'h' for Hard "<<endl;
    cin >> difficulty;
      cout<<endl;
    switch (difficulty) {
        case 'e':
        cout<<"MODE  :"<<"Easy";
        cout<<endl;
            gridSize = 10;
            maxBombs = 6;
            maxCoins = 18;
            maxUndos=6;
            break;
        case 'm': 
                cout<<"MODE  :"<<"Medium";
            gridSize = 15;
            maxBombs = 10;
            maxCoins = 22;
            maxUndos=4;
            break;
        case 'h': 
                cout<<"MODE  :"<<"Hard";
            gridSize = 20;
            maxBombs = 15;
            maxCoins = 30;
            maxUndos=1;
            break;
     
    }
    Node** grid = new Node*[gridSize];
    for (int i = 0; i < gridSize; ++i) {
        grid[i] = new Node[gridSize];
    }
  // InitialState(grid, gridSize, maxKeys, maxDoors); 
    createGrid(grid, gridSize);
    placeBombs(grid,gridSize, maxBombs);
    placeCoins(grid,gridSize, maxCoins);
    int playerRow, playerCol; 
    placePlayers(grid,gridSize, playerRow, playerCol);
    placeKeys(grid,gridSize, maxKeys);
    placeDoors(grid,gridSize, maxDoors);
    printGrid(grid,gridSize);
   std::thread coinThread(manageCoins, grid, gridSize, 6); 
    coinThread.detach(); 
    string command;
    while (true) {
        cout<<endl;
        cout << "Enter commands up, down, left, right, undo or quit: "<<endl;
        cin >> command;
        if (command == "quit") {
            break;
        } else if (command == "undo") {
           undoMove(grid, gridSize, playerRow, playerCol, moveHistory, undoCount, maxUndos);
        }
        else {
            if (!movePlayer(grid, gridSize, total_coins,score, playerRow,maxKeys,maxDoors, playerCol, command, moveHistory ,undoCount, maxUndos,hasKey ,coinHistory,keyHistory)) {
                
                break;  //end when hit the bomb
            }
        }
        printGrid(grid,gridSize);
              cout<<" MODE  :"<<difficulty<<endl;
        cout << "Total coins: " << total_coins << endl;
            
            cout<<"score  :"<<score;
            //  displayCoinCoordinates(coinHistory);
            cout<<"         ";
             cout <<"            Key Status:" << (hasKey ? "True" : "false") << endl;
             
             int totalMovesAllowed = calculateTotalMoves(grid, gridSize, playerRow, playerCol);
             cout << "Remaining Undos: " << (maxUndos - undoCount) ;
               cout<<"           ";
             
cout << "Total moves allowed: " << totalMovesAllowed ;
    }
    }

