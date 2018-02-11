#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>

int main(int argc, char** argv) {
  int aSize, bSize, aGoal, bGoal, aInt, bInt, stateA, stateB, nextStateA, nextStateB, nextMove, j, i = 0, loc = 0;
  std::vector<std::vector<int>> backtrack;
  std::vector<int> actions;
  std::string temp;
  bool solved = false, repeat = false, work = false;


  if(argc < 3){
    std::cout << "usage: hw01 input output" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::srand(std::time(nullptr));
  std::ifstream input(argv[1], std::ifstream::in);
  std::ofstream output(argv[2], std::ofstream::out);

  getline(input, temp, ':');
  input >> aSize;
  getline(input, temp, ':');
  input >> bSize;
  getline(input, temp, ':');
  input >> aInt;
  input >> bInt;
  getline(input, temp, ':');
  input >> aGoal;
  input >> bGoal;
  input.close();
  stateA = aInt;
  stateB = bInt;

  output << "Strategy A" << std::endl;
  output << "Starting out with " << aSize << "-gallon jug and a " << bSize << "-gallon jug" << "               -- state: (" << stateA << "," << stateB << ")" << std::endl;
  while(i < 250 && !solved){
    nextMove = std::rand() % 6;
    switch(nextMove){
      case 0: //dump A
        if(stateA > 0){
          stateA = 0;
          output << "Empty the " << aSize << "-gallon jug" << "                                          -- state: (" << stateA << "," << stateB << ")" << std::endl;
          i++;
        }
      break;
      case 1: //dump B
        if(stateB > 0){
          stateB = 0;
          output << "Empty the " << bSize << "-gallon jug" << "                                          -- state: (" << stateA << "," << stateB << ")" << std::endl;
          i++;
        }
      break;
      case 2: //pour A into B
        if(stateA > 0 && stateB < bSize){
          stateB = stateA + stateB;
          if(stateB > bSize){
            stateA = stateB - bSize;
            stateB = bSize;
          }
          output << "Pour the " << aSize << "-gallon jug into the " << bSize << "-gallon jug                     -- state: (" << stateA << "," << stateB << ")" << std::endl;
          i++;
        }
      break;
      case 3: //pour B into A
        if(stateB > 0 && stateA < aSize){
          stateA = stateA + stateB;
          if(stateA > aSize){
            stateB = stateA - aSize;
            stateA = aSize;
          }
          output << "Pour the " << bSize << "-gallon jug into the " << aSize << "-gallon jug                     -- state: (" << stateA << "," << stateB << ")" << std::endl;
          i++;
        }
      break;
      case 4: //fill A
        if(stateA < aSize){
          stateA = aSize;
          output << "FIll the " << aSize << "-gallon jug                                           -- state: (" << stateA << "," << stateB << ")" << std::endl;
          i++;
        }
      break;
      case 5: //fill B
        if(stateB < bSize){
          stateB = bSize;
          output << "FIll the " << bSize << "-gallon jug                                           -- state: (" << stateA << "," << stateB << ")" << std::endl;
          i++;
        }
      break;
      default:
        //this shouldn't happen
      break;
    }
    if((stateA == aGoal || aGoal == -1) && (stateB == bGoal || bGoal == -1)) solved = true;
  }

  //strategy B
  stateA = aInt;
  stateB = bInt;
  i = 0;
  output << std::endl << "Strategy B" << std::endl;
  output << "Starting out with " << aSize << "-gallon jug and a " << bSize << "-gallon jug" << "               -- state: (" << stateA << "," << stateB << ")" << std::endl;
  while(i < 250 && !solved){
    nextMove = std::rand() % 6;
    switch(nextMove){
      case 0: //dump A
        if(stateA > 0){
          nextStateA = 0;
          i++;
          work = true;
        }
      break;
      case 1: //dump B
        if(stateB > 0){
          nextStateB = 0;
          i++;
          work = true;
        }
      break;
      case 2: //pour A into B
        if(stateA > 0 && stateB < bSize){
          nextStateB = stateA + stateB;
          if(nextStateB > bSize){
            nextStateA = nextStateB - bSize;
            nextStateB = bSize;
          }
          i++;
          work = true;
        }
      break;
      case 3: //pour B into A
        if(stateB > 0 && stateA < aSize){
          nextStateA = stateA + stateB;
          if(nextStateA > aSize){
            nextStateB = nextStateA - aSize;
            nextStateA = aSize;
          }
          i++;
          work = true;
        }
      break;
      case 4: //fill A
        if(stateA < aSize){
          nextStateA = aSize;
          i++;
          work = true;
        }
      break;
      case 5: //fill B
        if(stateB < bSize){
          nextStateB = bSize;
          i++;
          work = true;
        }
      break;
      default:
        //this shouldn't happen
      break;
    }
    if(work){
      for(j = 0; j < (i - 1); j++){
        if(backtrack[j][0] == nextStateA && backtrack[j][1] == nextStateB && !repeat){
          repeat = true;
          loc = j;
        }
      }
      if(repeat){
        while(backtrack.size() != (loc + 1)) backtrack.pop_back();
        while(actions.size() != (loc + 1)) actions.pop_back();
        i = loc;
        repeat = false;
      } else {
        backtrack.push_back(std::vector<int>());
        backtrack[i].push_back(nextStateA);
        backtrack[i].push_back(nextStateB);
        actions.push_back(nextMove);
      }
      stateA = nextStateA;
      stateB = nextStateB;
      work = false;
    }
    if((stateA == aGoal || aGoal == -1) && (stateB == bGoal || bGoal == -1)) solved = true;
  }
  for(j = 0; j < backtrack.size(); j++){
    stateA = backtrack[j][0];
    stateB = backtrack[j][1];
    switch(actions.at(j)){
      case 0: //dump A
        output << "Empty the " << aSize << "-gallon jug" << "                                          -- state: (" << stateA << "," << stateB << ")" << std::endl;
      break;
      case 1: //dump B
        output << "Empty the " << bSize << "-gallon jug" << "                                          -- state: (" << stateA << "," << stateB << ")" << std::endl;
      break;
      case 2: //pour A into B
        output << "Pour the " << aSize << "-gallon jug into the " << bSize << "-gallon jug                     -- state: (" << stateA << "," << stateB << ")" << std::endl;
      break;
      case 3: //pour B into A
        output << "Pour the " << bSize << "-gallon jug into the " << aSize << "-gallon jug                     -- state: (" << stateA << "," << stateB << ")" << std::endl;
      break;
      case 4: //fill A
        output << "FIll the " << aSize << "-gallon jug                                           -- state: (" << stateA << "," << stateB << ")" << std::endl;
      break;
      case 5: //fill B
        output << "FIll the " << bSize << "-gallon jug                                           -- state: (" << stateA << "," << stateB << ")" << std::endl;
      break;
      default:
        //this shouldn't happen
      break;
    }
  }
  output.close();
  backtrack.clear();
  actions.clear();
}
