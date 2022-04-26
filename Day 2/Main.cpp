#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>

template<typename t>
void parse_inputFile(const std::string& filePath, std::vector<t>& vectorOutput){
  
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

  InputFile.close();
  
  return;
  
}

template<typename t>
std::uint32_t slide_compare(const uint32_t& slide, const std::vector<t>& vectorInput){
  
  std::uint32_t IncreasedCount = 0;
  
  for(std::uint32_t i = 1; i < vectorInput.size() - (slide - 1); i++){
    std::uint32_t ComparendBuffer = 0;
    std::uint32_t ComparerBuffer = 0;
    for(std::uint32_t j = 0; j < slide; j++){
      ComparendBuffer += vectorInput[i + j];
      ComparerBuffer += vectorInput[(i - 1) + j];
    }
    if(ComparendBuffer > ComparerBuffer){
      IncreasedCount++;
    }
  }
  
  return IncreasedCount;
  
}

int main(void){
  
  std::vector<std::uint32_t> ReportInputs(0, 0);
  parse_inputFile("Input.txt", ReportInputs);
  std::cout << "PART 1: " << slide_compare(1, ReportInputs) << std::endl;
  std::cout << "PART 2: " << slide_compare(3, ReportInputs) << std::endl;

/* --------------TESTING PARSE----------------*/
//  for(uint32_t v : ReportInputs){
//    std::cout << v << std::endl;
//  }
//  std::cout << ReportInputs[0] << std::endl;
//  std::cout << ReportInputs[1] << std::endl;
//  std::cout << ReportInputs[2] << std::endl;
/* --------------TESTING PARSE----------------*/

  return 0;

}
