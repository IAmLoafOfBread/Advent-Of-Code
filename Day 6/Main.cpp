#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

void parse_inputFile(const std::string& filePath, std::vector<std::uint32_t>& vectorOutput){

  std::ifstream InputFile(filePath);

  std::string StringBuffer = {0};
  std::getline(InputFile, StringBuffer);
  for(auto c : StringBuffer){
    if((c != ',') && (c != '\0')){
      vectorOutput.push_back(c - 48);
    }
  }
  InputFile.close();

  return;

}

void simulate_schoolGrowth(std::vector<std::uint32_t> initialInput, std::uint32_t dayCount){

  

  return;

}

int main(void){

  std::vector<std::uint32_t> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);
  simulate_schoolGrowth(ReportInputs, 80);

/* --------------TESTING PARSE----------------*/
//  for(auto i : ReportInputs){
//    std::cout << i << ',';
//  }
//  std::cout << std::endl;
/* --------------TESTING PARSE----------------*/

  return 0;

}
