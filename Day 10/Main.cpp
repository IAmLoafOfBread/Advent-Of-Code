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

std::uint32_t calculate_errorScore(const std::vector<std::string>& vectorInput){

struct chunkunit_st{
  char type;
  bool welcome;
  char connectType;
  struct chunkunit_st* connection;
  std::uint32_t index;
  bool searched;
};

  std::vector<std::vector<chunkunit_st>> ChunkLines;
  for(auto stringed : vectorInput){
    std::vector<chunkunit_st> LineBuffer;
    for(std::uint32_t i = 0; i < stringed.size(); i++){
      bool WelcomeBuffer = stringed[i] == '(' || stringed[i] == '[' || stringed[i] == '{' || stringed[i] == '<' ? true : false;
      char ConnectTypeBuffer = WelcomeBuffer ? stringed[i] + 2 : stringed[i] - 2;
      if(stringed[i] == '(' || stringed[i] == ')'){
        ConnectTypeBuffer = WelcomeBuffer ? stringed[i] + 1 : stringed[i] - 1;
      }
      LineBuffer.push_back({stringed[i], WelcomeBuffer, ConnectTypeBuffer, nullptr, i, false});
    }
    ChunkLines.push_back(LineBuffer);
  }

  const std::uint32_t PARENTHESIS_SCORE = 3;
  const std::uint32_t SQUARE_BRACKET_SCORE = 57;
  const std::uint32_t CURLY_BRACKET_SCORE = 1197;
  const std::uint32_t ANGLE_BRACKET_SCORE = 25137;
  std::uint32_t Result = 0;
  for(auto& line : ChunkLines){
    for(std::uint32_t i = 0; i < line.size(); i++){
      std::uint32_t TypeCounter = 1;
      if(line[i].searched == false && line[i].welcome == true){
        for(std::uint32_t j = i + 1; j < line.size(); j++){
          TypeCounter += line[j].type == line[i].type ? 1 : 0;
          TypeCounter -= line[j].type == line[i].connectType ? 1 : 0;
          if(TypeCounter == 0){
            line[i].connection = &line[j];
            line[j].connection = &line[i];
            line[i].searched = true;
            line[j].searched = true;
            break;
          }
        }
      }
      line[i].searched = true;
    }
  }
  for(auto& line : ChunkLines){
    for(std::uint32_t i = 0; i < line.size(); i++){
      if(line[i].connection == nullptr){
        std::cout << i << ' ' << "NULL" << std::endl;
      }else{
        std::cout << i << ' ' << line[i].connection->index << std::endl;
      }
      bool ErrorFound = false;
      if(line[i].connection != nullptr && line[i].welcome == true){
        for(std::uint32_t j = line[i].connection->index - 1; j > i; j--){
          if(line[j].connection == nullptr){
            Result += line[i].type == '(' ? PARENTHESIS_SCORE : 0;
            Result += line[i].type == '[' ? SQUARE_BRACKET_SCORE : 0;
            Result += line[i].type == '{' ? CURLY_BRACKET_SCORE : 0;
            Result += line[i].type == '<' ? ANGLE_BRACKET_SCORE : 0;
            ErrorFound = true;
            break;
          }
          if(line[j].connection->index > line[i].connection->index){
            Result += line[j].type == ')' ? PARENTHESIS_SCORE : 0;
            Result += line[j].type == ']' ? SQUARE_BRACKET_SCORE : 0;
            Result += line[j].type == '}' ? CURLY_BRACKET_SCORE : 0;
            Result += line[j].type == '>' ? ANGLE_BRACKET_SCORE : 0;
            ErrorFound = true;
            break;
          }
        }
      }
      ErrorFound = line[i].connection == nullptr && line[i].welcome == false ? true : ErrorFound;
      if(ErrorFound){
        break;
      }
    }
  }

  return Result;

}

int main(void){

  std::vector<std::string> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);
  std::cout << calculate_errorScore(ReportInputs) << std::endl;


/* --------------TESTING PARSE----------------*/
//  for(auto i : ReportInputs){
//    std::cout << i << std::endl;
//  }
/* --------------TESTING PARSE----------------*/

  return 0;

}
