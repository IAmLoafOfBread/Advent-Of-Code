#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

struct ivec64_st{
  std::int32_t x;
  std::int32_t y;
};

void parse_inputFile(const std::string& filePath, std::vector<ivec64_st>& vectorOutput){

  std::ifstream InputFile(filePath);

  std::string StringBuffer = {0};
  while(std::getline(InputFile, StringBuffer)){
    
  }
  InputFile.close();

  return;

}

int main(void){

  std::vector<ivec64_st> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);

/* --------------TESTING PARSE----------------*/
/* --------------TESTING PARSE----------------*/

  return 0;

}
