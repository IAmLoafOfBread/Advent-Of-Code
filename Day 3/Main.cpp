#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>

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

int main(void){

  std::vector<byte_st> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);

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
