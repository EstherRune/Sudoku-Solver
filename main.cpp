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

//user enters puzzle into the array
void enter_puzzle(){

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


//called to manage solving of puzzle
int solve_puzzle(){

  return 0;
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
  cout << "Hello! Welcome to Sudoke Solver!\n";
  init_puzzle();
  //enter_puzzle();
  print_puzzle();
  int error = solve_puzzle();

  return 0;
}
