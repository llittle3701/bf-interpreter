#include "brainfuck.h"
#include "iostream"
#include <algorithm>


BF::BF()
{
  reset();
}

void BF::reset()
{
  std::fill(mem_, mem_ + MEM_SIZE, 0);
  ptr_ = 0;
}

bool BF::interpret(const std::string &src)
{
  int src_size = src.length();
  int bracket_count = 0;
  char operation;
 
 //balance checking
  for (int i = 0 ; i < src_size; i++) {
    operation = src[i];
    if (operation == '[')
      bracket_count++;
    if (operation == ']')
      bracket_count--;
  }
  if (bracket_count != 0)
    return false;

  //Iterate through the source
  for (int i = 0 ; i < src_size; i++) {
    operation = src[i];
   
    switch (operation) {
    case '>' :
      if (ptr_ == MEM_SIZE - 1) {
	ptr_ = 0;
      } 
      else {
	++ptr_;
      }
      break;
    case '<' :
      if (ptr_ == 0) {
	ptr_ = MEM_SIZE - 1;
      }
      else {
	--ptr_;
      }
      break;
    case '+' :
      if (mem_[ptr_] == UINT8_MAX) {
      	mem_[ptr_] = 0;
      }
      else {
      	mem_[ptr_]++;
      }
         break;
    case '-' :
      if (mem_[ptr_] == 0)
	mem_[ptr_] = UINT8_MAX;
      else
	mem_[ptr_]--;
      break;
    case '.' :
      std::cout << mem_[ptr_];
      break;
    case ',' :
      std::cin >> mem_[ptr_];
      break;
    case '[' :
      bracket_count = 1;
      int j;
      if (mem_[ptr_] == 0) {
	//search for matching ], with consideration for nested loops
	for (j = i+1 ; j < src_size; j++) {
	  if (src[j] == '[')
	    bracket_count++;
	  if (src[j] == ']') 
	    bracket_count--;
	   
	  //Checking if there are as many [ as there are ]
	    if (bracket_count == 0) {
	      i = j;
	      break;
	    }
	}	
      }
      else {
      //while loop begins
      break;
      }

    case ']' :
      bracket_count = 1;
      int k;
      if (mem_[ptr_] != 0) {
	// search for the corresponding [, with regards to nested loops
	for (k = i-1 ; k >= 0; k--) {
	  if (src[k] == ']')
	    bracket_count++;
	  if (src[k] == '[') 
	    bracket_count--;

	  //Checking if there are as many ] as there are [
	  if (bracket_count == 0) {
	    i = k;
	    break;
	  }
	}		 
      }

      else {
      // continue normally if array element is 0
      break;
      }

      default:
	break;
    
    }
  }
  return true;
}

int main() {
 BF bf;
 //Hello World
  std::string src("++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.");
 //Fibonacci Sequence up to 100
 /* std::string src("+++++++++++>+>>>>++++++++++++++++++++++++++++++++++++++++++++>++++++++++++++++++++++++++++++++<<<<<<[>[>>>>>>+>"
		 "+<<<<<<<-]>>>>>>>[<<<<<<<+>>>>>>>-]<[>++++++++++[-<-[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]>[<<[>>>+<<<-]>>[-]]<<]>>>[>>+>+<<<-]>>>[<<<+>>>-]+<[>[-]<[-]]"
		 ">[<<+>>[-]]<<<<<<<]>>>>>[++++++++++++++++++++++++++++++++++++++++++++++++.[-]]++++++++++<[->-<]>++++++++++++++++++++++++++++++++++++++++++++++++.[-]<<"
		 "<<<<<<<<<<[>>>+>+<<<<-]>>>>[<<<<+>>>>-]<-[>>.>.<<<[-]]<<[>>+>+<<<-]>>>[<<<+>>>-]<<[<+>-]>[<+>-]<<<-]");
 */
 //Quine
 /* std::string src("->++>+++>+>+>++>>+>+>+++>>+>+>++>+++>+++>+>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>+>+>++>>>+++>>>>>+++>+>>>>>>>>>>>>>>>>>>>>>>+++>>>>>>>++>+++>+++>+>>+++>+++>+>+++>+>+++>+>++>+++>>>+>+>+>+>++>+++>+>+>>+++>>>>>>>+>+>>>+>+>++>+++>+++>+>>+++>+++>+>+++>+>++>+++>++>>+>+>++>+++>+>+>>+++>>>+++>+>>>++>+++>+++>+>>+++>>>+++>+>+++>+>>+++>>+++>>+[[>>+[>]+>+[<]<-]>>[>]<+<+++[<]<<+]>>>[>]+++[++++++++++>++[-<++++++++++++++++>]<.<-<]");
  */
  bf.interpret(src);
  
  return 0;
}

