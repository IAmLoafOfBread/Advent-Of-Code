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
  

  InputFile.close();

  return;

}

int main(void){

  std::vector<std::uint32_t> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);

/* --------------TESTING PARSE----------------*/
//  for(auto i : ReportInputs){
//    std::cout << i << ',';
//  }
//  std::cout << std::endl;
/* --------------TESTING PARSE----------------*/

  return 0;

}
