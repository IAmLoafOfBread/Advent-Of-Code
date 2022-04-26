#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>

#define PART_2

template<typename t>
void parse_inputFile(const std::string& filePath, std::vector<t>& vectorOutput){
  
  {
      std::ifstream InputFile(filePath);
      std::string StringBuffer = {0};
      for(std::uint32_t i = 0; std::getline(InputFile, StringBuffer); i++){
        std::uint32_t NullIndex = 0;
        for(char& c : StringBuffer){
          NullIndex++;
        }
        std::uint32_t IntBuffer = 0;
        std::uint32_t Divisor = 1;
        for(std::uint32_t j = NullIndex; j != 0; j--){
          IntBuffer += (StringBuffer[j - 1] - 48) * Divisor;
          Divisor *= 10;
        }
        vectorOutput.push_back(IntBuffer);
      }
  }
  
  return;
  
}

int main(void){
  
  std::vector<std::uint32_t> ReportInputs(0, 0);
  parse_inputFile("Input.txt", ReportInputs);

/* --------------TESTING PARSE----------------*/
//  for(uint32_t v : ReportInputs){
//    std::cout << v << std::endl;
//  }
//  std::cout << ReportInputs[0] << std::endl;
//  std::cout << ReportInputs[1] << std::endl;
//  std::cout << ReportInputs[2] << std::endl;
/* --------------TESTING PARSE----------------*/

#if defined(PART_1)

  std::uint32_t IncreasedCount = 0;
  for(std::uint32_t i = 1; i < ReportInputs.size(); i++){
    if(ReportInputs[i] > ReportInputs[i -1]){
      IncreasedCount++;
    }
  }
  std::cout << IncreasedCount << std::endl;

#elif defined(PART_2)

  const std::uint32_t Slide = 3;
  std::uint32_t IncreasedCount = 0;
  for(std::uint32_t i = 1; i < ReportInputs.size() - (Slide - 1); i++){
    std::uint32_t ComparendBuffer = 0;
    std::uint32_t ComparerBuffer = 0;
    for(std::uint32_t j = 0; j < Slide; j++){
      ComparendBuffer += ReportInputs[i + j];
      ComparerBuffer += ReportInputs[(i - 1) + j];
    }
    if(ComparendBuffer > ComparerBuffer){
      IncreasedCount++;
    }
  }
  std::cout << IncreasedCount << std::endl;

#endif

  return 0;

}
