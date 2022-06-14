#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

void parse_inputFile(const std::string& filePath, std::vector<std::string>& vectorOutput){

  std::ifstream InputFile(filePath);

  std::string StringBuffer = {0};
  while(std::getline(InputFile, StringBuffer)){
    vectorOutput.push_back(StringBuffer);
  }

  InputFile.close();

  return;

}

int main(void){

  std::vector<std::string> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);


/* --------------TESTING PARSE----------------*/
//  for(auto i : ReportInputs){
//    std::cout << i << std::endl;
//  }
/* --------------TESTING PARSE----------------*/

  return 0;

}
