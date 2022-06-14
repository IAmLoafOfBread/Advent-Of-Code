#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

#define MAX_HEIGHT 9

void parse_inputFile(const std::string& filePath, std::vector<std::vector<std::uint32_t>>& vectorOutput){

  std::ifstream InputFile(filePath);

  std::string StringBuffer = {0};
  while(std::getline(InputFile, StringBuffer)){
    std::vector<std::uint32_t> ExtraBuffer;
    for(auto c : StringBuffer){
      ExtraBuffer.push_back(c - 48);
    }
    vectorOutput.push_back(ExtraBuffer);
  }

  InputFile.close();

  return;

}

std::uint32_t calculate_riskLevels(const std::vector<std::vector<uint32_t>>& vectorInput){

  std::uint32_t Result = 0;
    for(std::uint32_t i = 0; i < vectorInput.size(); i++){
      for(std::uint32_t j = 0; j < vectorInput[i].size(); j++){
        bool Lows[4] = {false, false, false, false};
        Lows[0] = j > 0 ? vectorInput[i][j] < vectorInput[i][j - 1] ? true : false : true;
        Lows[1] = j < vectorInput[i].size() - 1 ? vectorInput[i][j] < vectorInput[i][j + 1] ? true : false : true;
        Lows[2] = i > 0 ? vectorInput[i][j] < vectorInput[i - 1][j] ? true : false : true;
        Lows[3] = i < vectorInput.size() - 1 ? vectorInput[i][j] < vectorInput[i + 1][j] ? true : false : true;
        std::uint32_t LowCount = 0;
        for(auto l : Lows){
          LowCount += l == true ? 1 : 0;
        }
        Result += LowCount == 4 ? vectorInput[i][j] + 1 : 0;
      }
    }

  return Result;

}

std::uint32_t calculate_largestBasins(const std::vector<std::vector<std::uint32_t>>& vectorInput, std::uint32_t count){

  struct heightElem_st{
    std::uint32_t height;
    bool searched;
  };

  std::uint32_t Result;
  std::vector<std::vector<heightElem_st>> HeightElements;
  for(auto row : vectorInput){
    std::vector<heightElem_st> ElemBuffer;
    for(auto unit : row){
      ElemBuffer.push_back({unit, false});
    }
    HeightElements.push_back(ElemBuffer);
  }
  std::vector<std::uint32_t> BasinValues;
  std::uint32_t IntBuffer = 0;
  for(std::uint32_t i = 0; i < HeightElements.size(); i++){
    for(std::uint32_t j = 0; j < HeightElements[i].size(); j++){
      if(HeightElements[i][j].searched == false){
        HeightElements[i][j].searched == true;
      }
    }
  }

  return Result;

}

int main(void){

  std::vector<std::vector<std::uint32_t>> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);
  std::cout << calculate_riskLevels(ReportInputs) << std::endl;
//  std::cout << calculate_largestBasins(ReportInputs, 3) << std::endl;


/* --------------TESTING PARSE----------------*/
//  for(auto row : ReportInputs){
//    for(auto unit : row){
//      std::cout << unit;
//    }
//    std::cout << std::endl;
//  }
//  for(auto row : ReportInputs){
//    for(auto unit : row){
//      if(unit == MAX_HEIGHT){
//        std::cout << '#';
//      }else{
//        std::cout << ' ';
//      }
//    }
//    std::cout << std::endl;
//  }
//      if(unit == 8){
//        std::cout << '@';
//      }
//      if(unit == 7){
//        std::cout << '&';
//      }
//      if(unit == 6){
//        std::cout << '$';
//      }
//      if(unit == 5){
//        std::cout << '=';
//      }
//      if(unit == 4){
//        std::cout << '+';
//      }
//      if(unit == 3){
//        std::cout << '%';
//      }
//      if(unit == 2){
//        std::cout << '*';
//      }
//      if(unit == 1){
//        std::cout << '-';
//      }
//      if(unit == 0){
//        std::cout << ' ';
//      }
//    }
//    std::cout << std::endl;
//  }
/* --------------TESTING PARSE----------------*/

  return 0;

}
