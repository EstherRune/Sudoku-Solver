/*
Sudoku Solver by Erik Lundquist
05 November 2015
*/

#include <iostream>

using namespace std;

int Puzzle[9][9][10];

//returns true if cell has a solution set
bool is_set(int x, int y){
  if(Puzzle[x]y[][0] != 0) return true;
  else return false;
}

//fills Puzzle with all true possible values and zeroes the actual values
void init_puzzle(){
  for(int y=0; y < 9; y++){
    for(int x=0; x < 9; x++){
      Puzzle[x][y][0] = 0; //0 = no answer yet
      for(int z=1; z < 10; z++){
        Puzzle[x][y][z] = 1; //1 = possible
      }
    }
  }
}

//prints ascii version of current puzzle
void print_puzzle(){
  cout << endl << "Current Puzzle:" << endl;
  for(int y=0; y < 9; y++){
    for(int x=0; x < 9; x++){
      cout << Puzzle[x][y][0] << " ";
      if(x==2 || x==5) cout << "| ";
      }
      cout << endl;
      if(y==2||y==5) cout << "- - - | - - - | - - - " << endl;
    }
}

//user enters puzzle into the array
void enter_puzzle(){
  bool entering = true;
  while(entering){
    int x;
    int y;
    int val;
    print_puzzle();
    cout << "Enter x coordinate (0-8): " << endl;
    cin >> x;
    cout << "Enter y coordinate (0-8): " << endl;
    cin >> y;
    cout << "Enter value for that position (0-9)" << endl << "Entering a 0 will erase that position" << endl;
    cin >> val;
    //input sanitization
    bool safe = true;
    if(val > 9 || val < 0){
      cout << "Illegal value entered, input not recorded" << endl;
      safe = false;
    }
    if(x < 0 || x > 8){
      cout << "X value out of bounds, input not recorded" << endl;
      safe = false;
    }
    if(y < 0 || y > 8){
      cout << "Y value out of bounds, input not recorded" << endl;
      safe = false;
    }
    if(safe) Puzzle[x][y][0] = val;

    print_puzzle();

    cout << endl << "Would you like to enter another value? (y/n): ";
    char ans;
    cin >> ans;
    if(ans != 'y') entering = false;
  }
}

//checks a single position to see if there is only one number it can be
int only_ans_check(int x, int y){
  int possibilities = 0;
  int solution;
  for(int z = 1; z < 10; z++){
    if(Puzzle[x][y][z] == 1){
      possibilities++;
      solution = z;
    }
  }
  if(possibilities == 0) return 0; //There should never be no possible answer for a cell
  else if(possibilities == 1){
    Puzzle[x][y][0] = solution; //If there is only one possibility, set the answer for the cell
    return 1
  }
  else return 1;
}

//checks every position to see if there is only one possible number it can be
int only_ans_sweep(){
  for(int y=0; y < 9; y++){
    for(int x=0; x < 9; x++){
      int check = only_ans_check(x,y);
      if(check == 0) return 0; //Pass that error up!
    }
  }
  return 1;
}

//check a single position to see if it is the only place a number can go in its squar/horizontal/vertical
int only_pos_check(int x, int y){


  return 1;
}

//checks every position to see if it is the only place a number in a sqaure/horizontal/vertical can go
int only_pos_sweep(){
  for(int y=0; y < 9; y++){
    for(int x=0; x < 9; x++){
      int check = only_pos_check(x,y);
      if(check == 0) return 0;
    }
  }
  return 1;
}

//checks a single position on the board for collisions and falsifies impossible answers
int single_cell_check(int x, int y){

  possibilities[10];
  for(int i = 0; i < 10; i++){
    possibilities[i] = 1; //we set a temp variable to have all possible, then we check everywhere and update
  }

  //horizontal check
  for(int i = 0; i < 9; i++){
    //only check if it isn't itself
    if(i != x) possibilities[ Puzzle[i][y][0] ] = 0;
  }

  //vertical check
  for(int i = 0; i < 9; i++){
    //only check if it isn't itself
    if(i != y) possibilities[ Puzzle[x][i][0] ] = 0;
  }

  //sqaure check
  //0-2, 3-5, 6-8 are the possible squares
  int x_square;
  int y_square;

  //determine what square we are in and set starting points for x and y
  if(x < 3) x_sqaure = 0;
  else if(x > 5) x_square = 6;
  else x_square = 3;
  if(y < 3) y_sqaure = 0;
  else if(y > 5) y_square = 6;
  else y_square = 3;

  //now go through sqaure for the check
  for(int i = x_square; i < (x_sqaure+3); i++){
    for(int j = y_square; j < (y_sqaure+3); j++){
      //we only check the x,y pairs that are in the square and not in a row/column because we already checked those
      if(i != x && j != y) possibilities[ Puzzle[i][j][0] ] = 0;
    }
  }

  //now we have an array with the possible things the cell can be in locations 1-9
  //let's set the Puzzle to reflect our findings
  for(int i = 1; i < 10; i++){
    Puzzle[x][y][i] = possibilities[i]; //put 0 or 1 in each corrisponding location
  }

  //we do an error check here too
  //if the cell is set and it can't be the number it currently is
  //we give up and show the puzzle as is
  if(is_set(x,y)){
    if( possibilities[ Puzzle[x][y][0] ] == 0) return 0;
  }

  return 1;
}

//does a single position check for the whole board
int whole_puzzle_check(){
  for(int y=0; y < 9; y++){
    for(int x=0; x < 9; x++){
      int check = single_cell_check(x,y);
      if(check == 0) return 0;
    }
  }
  return 1;
}

int complete(){
  int check = whole_puzzle_check();
  if(check == 0) return 0;

  for(int y=0; y < 9; y++){
    for(int x=0; x < 9; x++){
      if(!is_set(x,y)) return 1;
    }
  }

  return 2;
}

//called to manage solving of puzzle
int solve_puzzle(){
  bool working = true;
  int check;
  while(working){

      //check if the puzzle is full
      //this calls whole_puzzle check which updates possible answers for each cell while checking
      //2 if it is full and no error
      //1 if isnt full
      //0 if error is found
      int done = complete();
      if(done == 2) return 1; //full and no error? WE SOLVED IT!
      else if(done == 0) return 0; //shit...collision

      //go through whole puzzle and set cells that can only be one thing
      check = only_ans_sweep();
      if(check == 0) return 0;


  }

  return 1; //SOLVED!
}

main (){
  bool run = true;
  while(run){
    cout << "Hello! Welcome to Sudoke Solver!" << endl;
    init_puzzle();
    enter_puzzle();
    cout << "Solving!" << endl;
    int check = solve_puzzle();
    if(check == 1){
      cout << endl << "Your puzzle has been solved!" << endl;
    }
    else{
      cout << "We couldn't solve your puzzle." <<endl;
      cout << "This was the end result, but an error occurred along the way." << endl;
      cout
    }
    print_puzzle();
    cout << "Would you like to solve another puzzle? (y/n): ";
    char ans;
    cin >> ans;
    if(ans != 'y') run = false;
  }
  return 0;
}
