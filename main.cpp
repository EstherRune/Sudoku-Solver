/*
Sudoku Solver by Erik Lundquist
05 November 2015
*/

#include <iostream>
#include <math.h>
using namespace std;

int Puzzle[9][9][10];

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




//called to manage solving of puzzle
bool solve_puzzle(){

  return true;
}

//checks a single position on the board for collisions and falsifies impossible answers
void single_pos_check(int x, int y){

}

//checks a single position to see if there is only one number it can be
void only_ans_check(int x, int y){

}

//check a single position to see if it is the only place a number can go in its squar/horizontal/vertical
void only_pos_check(int x, int y){

}

//does a single position check for the whole board
void whole_puzzle_check(){

}

//checks every position to see if there is only one possible number it can be
void only_ans_sweep(){

}

//checks every position to see if it is the only place a number in a sqaure/horizontal/vertical can go
void only_pos_sweep(){

}

main (){
  bool run = true;
  while(run){
    cout << "Hello! Welcome to Sudoke Solver!" << endl;
    init_puzzle();
    enter_puzzle();
    print_puzzle();
    cout << "Solving!" << endl;
    bool solved = solve_puzzle();
    if(solved){
      print_puzzle();
      cout << endl << "You're puzzle has been solved!" << endl;
      cout << "Would you like to solve another puzzle? (y/n): ";
      char ans;
      cin >> ans;
      if(ans != 'y') run = false;
    }
  }
  return 0;
}
