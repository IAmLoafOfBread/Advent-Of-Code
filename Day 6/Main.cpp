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

std::uint64_t BETTERsimulate_schoolGrowth(const std::vector<std::uint32_t>& initialInput, const std::uint32_t& dayCount){

  std::uint64_t TotalCount = 0;
  for(std::uint32_t i = 0; i != initialInput.size(); i++){
    if(initialInput[i] < dayCount){
      TotalCount += pow(2, dayCount - initialInput[i]) - dayCount * 6;
    }else{
      TotalCount++;
    }
  }

  return TotalCount;

}

std::uint64_t simulate_schoolGrowth(const std::vector<std::uint32_t>& initialInput, const std::uint32_t& dayCount){

  std::vector<std::uint32_t> Result = initialInput;
  std::uint64_t OldCount = Result.size();
  for(std::uint32_t i = 0; i != dayCount; i++){
    for(std::uint32_t j = 0; j != OldCount; j++){
      if(Result[j] != 0){
        Result[j]--;
      }else{
        Result[j] = 6;
        Result.push_back(0);
      }
    }
    OldCount = Result.size();
  }

  return Result.size();

}

int main(void){

  std::vector<std::uint32_t> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);
  for(std::uint32_t i = 0; i != 2 + 1; i++){
    std::cout << "DIRECT: " << simulate_schoolGrowth(ReportInputs, i) << std::endl;
    std::cout << "BETTER: " << BETTERsimulate_schoolGrowth(ReportInputs, i) << std::endl;
    std::cout << std::endl;
  }

/* --------------TESTING PARSE----------------*/
//  for(auto i : ReportInputs){
//    std::cout << i << ',';
//  }
//  std::cout << std::endl;
/* --------------TESTING PARSE----------------*/

  return 0;

}
