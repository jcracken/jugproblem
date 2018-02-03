#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>

int main(int argc, char** argv) {
  int aSize, bSize, intlState1, intlState2, aGoal, bGoal;
  if(argc < 3){
    std:cout << "usage: hw01 input output" << std:endl;
    exit(EXIT_FAILURE);
  }
  std::ifstream input(argv[1], std::ifstream::in);
  std::ofstream output(argv[2], std::ofstream::out);
  input >> aSize;
  input >> bSize;
  input >> intlState1;
  input >> intlState2;
  input >> aGoal;
  input >> bGoal;
  input.close();
  
}
