#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>

int main(int argc, char** argv) {
  int aSize, bSize, aGoal, bGoal, stateA, stateB, nextMove, i = 0;
  bool solved = false;


  if(argc < 3){
    std:cout << "usage: hw01 input output" << std:endl;
    exit(EXIT_FAILURE);
  }

  std::strand(std::time(nullptr));
  std::ifstream input(argv[1], std::ifstream::in);
  std::ofstream output(argv[2], std::ofstream::out);

  input >> aSize;
  input >> bSize;
  input >> stateA;
  input >> stateB;
  input >> aGoal;
  input >> bGoal;
  input.close();

  output << "Strategy A" << std:endl;
  output << "Starting out with " << aSize << "-gallon jug and a " << bSize << "-gallon jug" << "              -- state: (" << stateA << "," << stateB << ")" << std:endl;
  while(i < 251 && !solved){
    nextMove = std::rand() % 6;
    switch(nextMove){
      case 0: //dump A
        if(stateA > 0){
          stateA = 0;
          output << "Empty the " << aSize << "-gallon jug" << "                                          -- state: (" << stateA << "," << stateB << ")" << std:endl;
          i++;
        }
      break;
      case 1: //dump B
        if(stateB > 0){
          stateB = 0;
          output << "Empty the " << bSize << "-gallon jug" << "                                          -- state: (" << stateA << "," << stateB << ")" << std:endl;
          i++;
        }
      break;
      case 2: //pour A into B
        if(stateA > 0 && stateB < bSize){
          stateB = stateA + stateB;
          if(stateB > bSize) stateB = bSize;
          output << "Pour the " << aSize << "-gallon jug into the " << bSize << "-gallon jug         -- state: (" << stateA << "," << stateB << ")" << std:endl;
          i++;
        }
      break;
      case 3: //pour B into A
        if(stateB > 0 && stateA < aSize){
          stateA = stateA + stateB;
          if(stateA > aSize) stateA = aSize;
          output << "Pour the " << bSize << "-gallon jug into the " << aSize << "-gallon jug         -- state: (" << stateA << "," << stateB << ")" << std:endl;
          i++;
        }
      break;
      case 4: //fill A
        if(stateA < aSize){
          stateA = aSize;
          output << "FIll the " << aSize << "-gallon jug                                           -- state: (" << stateA << "," << stateB << ")" << std:endl;
          i++;
        }
      break;
      case 5: //fill B
        if(stateB < bSize){
          stateB = bSize;
          output << "FIll the " << bSize << "-gallon jug                                           -- state: (" << stateA << "," << stateB << ")" << std:endl;
          i++;
        }
      break;
      default:
        //this shouldn't happen
      break;
    }
    if(stateA == aGoal && stateB == bGoal) solved = true;
  }
}
