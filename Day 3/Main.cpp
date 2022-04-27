#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

struct byte_st{
  std::vector<bool> bits;
};

void parse_inputFile(const std::string& filePath, std::vector<struct byte_st>& vectorOutput){
  
  std::ifstream InputFile(filePath);

  std::string StringBuffer = {0};
  for(std::uint32_t i = 0; std::getline(InputFile, StringBuffer); i++){
    struct byte_st ByteBuffer;
    for(char c : StringBuffer){
      ByteBuffer.bits.push_back(c - 48);
    }
    vectorOutput.push_back(ByteBuffer);
  }

  InputFile.close();
  
  return;
  
}

std::int32_t convert_binary(const byte_st& byte){

  std::int32_t Result = 0;
  std::uint32_t IndexIncrement = 0;
  for(std::uint32_t i = byte.bits.size(); i > 0; i--){
    Result += byte.bits[IndexIncrement] * std::pow(2, i - 1);
    IndexIncrement++;
  }

  return Result;

}

std::uint32_t find_powerConsumption(const std::vector<byte_st> vectorInput){

  struct byte_st GammaRate;
  struct byte_st EpsilonRate;
  for(std::uint32_t i = 0; i < vectorInput[0].bits.size(); i++){
    std::uint32_t FalseCount = 0;
    std::uint32_t TrueCount = 0;
    for(std::uint32_t j = 0; j < vectorInput.size(); j++){
      if(vectorInput[j].bits[i] == 0){
        FalseCount++;
      }else{
        TrueCount++;
      }
    }
    if(FalseCount > TrueCount){
      GammaRate.bits.push_back(false);
      EpsilonRate.bits.push_back(true);
    }else if(FalseCount < TrueCount){
      GammaRate.bits.push_back(true);
      EpsilonRate.bits.push_back(false);
    }
  }

  return convert_binary(GammaRate) * convert_binary(EpsilonRate);

}

int main(void){

  std::vector<byte_st> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);
  std::cout << find_powerConsumption(ReportInputs) << std::endl;

/* --------------TESTING PARSE----------------*/
//  for(byte_st byte : ReportInputs){
//    for(bool bit : byte.bits){
//      std::cout << bit;
//    }
//    std::cout << std::endl;
//  }
/* --------------TESTING PARSE----------------*/

  return 0;

}
