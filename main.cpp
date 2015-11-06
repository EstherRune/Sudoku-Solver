/*
Sudoku Solver by Erik Lundquist
05 November 2015
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <cstring>
#include <cstdlib>

using namespace std;

int Puzzle[9][9][10];

//returns true if cell has a solution set
bool is_set(int x, int y){
  if(Puzzle[x][y][0] != 0) return true;
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
    cout << endl;
}

//user enters puzzle into the array
void enter_puzzle(){
    ifstream file;
    file.open("puzzle.txt");
    string line;
    int i = 0;
    int j = 0;
    int num;
    while( getline(file,line) ){
      num = atoi(line.c_str());
      Puzzle[i][j][0] = num;
      i++;
      if(i > 8){
        i = 0;
        j++;
      }
      if(j > 8) break;
    }
    file.close();
    print_puzzle();
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
  else if(possibilities == 1 && Puzzle[x][y][0] != solution){
    Puzzle[x][y][0] = solution; //If there is only one possibility, set the answer for the cell
    cout << "Found an answer: " << x << "," << y << " = " << solution << endl;
    return 2;
  }
  else return 1;
}

//checks every position to see if there is only one possible number it can be
int only_ans_sweep(){
  int change = 1;
  for(int y=0; y < 9; y++){
    for(int x=0; x < 9; x++){
      int check = only_ans_check(x,y);
      if(check == 0) return 0; //Pass that error up!
      else if(check == 2) change = 2;
    }
  }
  return change;
}

//checks every position to see if it is the only place a number in a sqaure/horizontal/vertical can go
int only_pos_sweep(){
  int change = 1;

  int tracker;
  int saver;
  bool set = false;

  //check each num for row, column, and square uniqueness in possibilities

  //number to check for iterator
  for(int num = 1; num < 10; num++){

    //look at rows
    for(int y=0; y < 9; y++){
      for(int x=0; x < 9; x++){
        if(Puzzle[x][y][num] == 1 && !is_set(x,y)){
          tracker++;
          saver = x;
        }
        if(Puzzle[x][y][0] == num){
          set = true;
        }
      }
      if(tracker == 1 && !set){
        Puzzle[saver][y][0] == num;
        cout << "Found an answer: " << saver << "," << y << " = " << num << endl;
        //print_puzzle();
        change = 2;
      }
      else if(tracker == 0 && !set) {
        cout << "Failed pos test " << saver << "," << y << "=" << num << endl;
        return 0;
      }
      tracker = 0;
      set = false;
    }
/*
    //look at columns
    for(int x=0; x < 9; x++){
      for(int y=0; y < 9; y++){
        if(Puzzle[x][y][num] == 1 && !is_set(x,y)){
          tracker++;
          saver = y;
        }
      }
      if(tracker == 1){
        Puzzle[x][saver][0] == num;
        cout << "Found an answer: " << x << "," << saver << " = " << num << endl;
        change = 2;
      }
      else if(tracker == 0) return 0;
      tracker = 0;
    }


    int savex;
    int savey;
    //look at squares
    for(int base_x = 0; base_x < 9; base_x += 3){
      for(int base_y = 0; base_y <9; base_y += 3){
        for(int x = 0; x < 3; x++){
          for(int y = 0; y < 3; y++){
            if(Puzzle[base_x+x][base_y+y][num] == 1 && !is_set(x,y)) tracker++;
            savex = x;
            savey = y;
          }
        }
        if(tracker == 1){
          Puzzle[savex][savey][0] == num;
          cout << "Found an answer: " << savex << "," << savey << " = " << num << endl;
          change = 2;
        }
        else if(tracker == 0) return 0;
        tracker = 0;
      }
    }
    */
  }

  return change;
}

//checks a single position on the board for collisions and falsifies impossible answers
int single_cell_check(int x, int y){
  int change = 1;

  int possibilities[10];
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
  if(x < 3) x_square = 0;
  else if(x > 5) x_square = 6;
  else x_square = 3;

  if(y < 3) y_square = 0;
  else if(y > 5) y_square = 6;
  else y_square = 3;

  //now go through sqaure for the check
  for(int i = x_square; i < (x_square+3); i++){
    for(int j = y_square; j < (y_square+3); j++){
      //we only check the x,y pairs that are in the square and not in a row/column because we already checked those
      if(i != x || j != y) possibilities[ Puzzle[i][j][0] ] = 0;
    }
  }

  //now we have an array with the possible things the cell can be in locations 1-9
  //let's set the Puzzle to reflect our findings
  for(int i = 1; i < 10; i++){
    if(Puzzle[x][y][i] != possibilities[i]){ //if they are different
      Puzzle[x][y][i] = possibilities[i];    //change the entry
      change = 2;                          //mark that we did something this round
      //cout << "Updated possibilities of " << x << "," << y << endl;
    }
  }

  //we do an error check here too
  //if the cell is set and it can't be the number it currently is
  //we give up and show the puzzle as is
  if(is_set(x,y)){
    if( possibilities[ Puzzle[x][y][0] ] == 0) return 0;
  }

  return change;
}

//does a single position check for the whole board
int whole_puzzle_check(){
  int change =1;
  for(int y=0; y < 9; y++){
    for(int x=0; x < 9; x++){
      int check = single_cell_check(x,y);
      if(check == 0) return 0;
      else if(check == 2) change = 2;
    }
  }
  return change;
}

int complete(){
  int change = 1;
  int check = whole_puzzle_check();
  if(check == 0) return 0;
  else if(check == 2) change = 2;

  for(int y=0; y < 9; y++){
    for(int x=0; x < 9; x++){
      if(!is_set(x,y)) return change;
    }
  }

  return 3;
}

//called to manage solving of puzzle
int solve_puzzle(){
  bool working = true;
  int check;
  int change = 1;
  int change_fails = 0;
  int count = 1;
  while(working){

      //check if the puzzle is full
      //this calls whole_puzzle check which updates possible answers for each cell while checking
      //3 if it is full and no error
      //2 if it isn't full but we updated something
      //1 if isnt full and we found nothing new
      //0 if error is found
      int done = complete();
      if(done == 3) return 1; //full and no error? WE SOLVED IT!
      else if(done == 0){
        cout << "failed complete check" << endl;
        return 0;
      } //shit...collision
      else if(done == 2) change = 2;
      cout << "Checked for complete " << count << " time(s)! Change = " << change << endl;

      //go through whole puzzle and set cells that can only be one thing
      check = only_ans_sweep();
      if(check == 0){
        cout << "Failed ans_sweep" << endl;
        return 0;
      }
      else if(check == 2) change = 2;
      cout << "Checked for sole answeres in cells " << count << " time(s)! Change = " << change << endl;

      done = complete();
      if(done == 3) return 1; //full and no error? WE SOLVED IT!
      else if(done == 0){
        cout << "failed complete check" << endl;
        return 0;
      } //shit...collision
      else if(done == 2) change = 2;
      cout << "Checked for complete " << count << " time(s)! Change = " << change << endl;

      //goes through the puzzle and checks each row, column, and square for a number that can only go in one place
      check = only_pos_sweep();
      if(check == 0){
        cout << "Failed pos_sweep" << endl;
        return 0;
      }
      else if(check == 2) change = 2;
      cout << "Checked for only possible positions in groups " << count << " time(s)! Change = " << change << endl;

      if(change == 1) change_fails++; //we didnt change anything this round and we didn't exit with a complete puzzle
      change = 1;
      count ++;
      if(change_fails == 3){
        cout << change_fails << " times failed to change anything" << endl;
        return 0;
      }
  }

  return 1; //SOLVED!
}

main (){

  cout << "Hello! Welcome to Sudoku Solver!" << endl;
  init_puzzle();
  enter_puzzle();
  cout << "Solving!" << endl;
  int check = solve_puzzle();
  if(check == 1){
    cout << endl << "Your puzzle has been solved!" << endl;
  }
  else{
    cout << "We couldn't solve your puzzle. " <<endl;

  }
  print_puzzle();

  return 0;
}
