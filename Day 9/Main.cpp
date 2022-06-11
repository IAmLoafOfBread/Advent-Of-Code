#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

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

std::uint32_t calculate_riskLevel(const std::vector<std::vector<uint32_t>>& vectorInput){

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

int main(void){

  std::vector<std::vector<std::uint32_t>> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);
  std::cout << calculate_riskLevel(ReportInputs) << std::endl;


/* --------------TESTING PARSE----------------*/
//  for(auto row : ReportInputs){
//    for(auto unit : row){
//      std::cout << unit;
//    }
//    std::cout << std::endl;
//  }
/* --------------TESTING PARSE----------------*/

  return 0;

}
