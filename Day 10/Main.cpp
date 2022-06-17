#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

struct chunkunit_st{
  char type;
  bool welcome;
  char connectType;
  struct chunkunit_st* connection;
  std::uint32_t index;
};

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

  std::vector<std::vector<chunkunit_st>> ChunkLines;
  for(auto stringed : vectorInput){
    std::vector<chunkunit_st> LineBuffer;
    for(std::uint32_t i = 0; i < stringed.size(); i++){
      bool WelcomeBuffer = stringed[i] == '(' || stringed[i] == '[' || stringed[i] == '{' || stringed[i] == '<' ? true : false;
      char ConnectTypeBuffer = WelcomeBuffer ? stringed[i] + 2 : stringed[i] - 2;
      if(stringed[i] == '(' || stringed[i] == ')'){
        ConnectTypeBuffer = WelcomeBuffer ? stringed[i] + 1 : stringed[i] - 1;
      }
      LineBuffer.push_back({stringed[i], WelcomeBuffer, ConnectTypeBuffer, nullptr, i});
    }
    ChunkLines.push_back(LineBuffer);
  }

  const std::uint32_t PARENTHESIS_SCORE = 3;
  const std::uint32_t SQUARE_BRACKET_SCORE = 57;
  const std::uint32_t CURLY_BRACKET_SCORE = 1197;
  const std::uint32_t ANGLE_BRACKET_SCORE = 25137;
  std::uint32_t Result = 0;
  for(auto& line : ChunkLines){
    std::vector<std::uint32_t> ErrorIndices;
    for(std::uint32_t i = 0; i < line.size(); i++){
      std::uint32_t WelcomeCounter = 1;
      if(line[i].welcome == true){
        for(std::uint32_t j = i + 1; j < line.size(); j++){
          WelcomeCounter += line[j].welcome == true ? 1 : 0;
          WelcomeCounter -= line[j].welcome == false ? 1 : 0;
          if(WelcomeCounter == 0){
            if(line[i].connectType != line[j].type){
              ErrorIndices.push_back(j);
            }
            line[i].connection = &line[j];
            line[j].connection = &line[i];
            break;
          }
        }
      }
    }
    std::uint32_t IndexBuffer = line.size();
    for(std::uint32_t i = 0; i < ErrorIndices.size(); i++){
      IndexBuffer = IndexBuffer > ErrorIndices[i] ? ErrorIndices[i] : IndexBuffer;
    }
    Result += line[IndexBuffer].type == ')' ? PARENTHESIS_SCORE : 0;
    Result += line[IndexBuffer].type == ']' ? SQUARE_BRACKET_SCORE : 0;
    Result += line[IndexBuffer].type == '}' ? CURLY_BRACKET_SCORE : 0;
    Result += line[IndexBuffer].type == '>' ? ANGLE_BRACKET_SCORE : 0;
  }

  return Result;

}
std::uint64_t calculate_completionScore(const std::vector<std::string>& vectorInput){

  std::vector<std::vector<chunkunit_st>> ChunkLines;
  for(auto stringed : vectorInput){
    std::vector<chunkunit_st> LineBuffer;
    for(std::uint32_t i = 0; i < stringed.size(); i++){
      bool WelcomeBuffer = stringed[i] == '(' || stringed[i] == '[' || stringed[i] == '{' || stringed[i] == '<' ? true : false;
      char ConnectTypeBuffer = WelcomeBuffer ? stringed[i] + 2 : stringed[i] - 2;
      if(stringed[i] == '(' || stringed[i] == ')'){
        ConnectTypeBuffer = WelcomeBuffer ? stringed[i] + 1 : stringed[i] - 1;
      }
      LineBuffer.push_back({stringed[i], WelcomeBuffer, ConnectTypeBuffer, nullptr, i});
    }
    ChunkLines.push_back(LineBuffer);
  }

  const std::uint32_t PARENTHESIS_SCORE = 1;
  const std::uint32_t SQUARE_BRACKET_SCORE = 2;
  const std::uint32_t CURLY_BRACKET_SCORE = 3;
  const std::uint32_t ANGLE_BRACKET_SCORE = 4;
  std::uint64_t Result = 0;
  std::vector<std::uint64_t> Scores;
  for(auto& line : ChunkLines){
    bool Corrupted = false;
    bool Complete = true;
    for(std::uint32_t i = 0; i < line.size(); i++){
      std::uint32_t WelcomeCounter = 1;
      if(line[i].welcome == true){
        for(std::uint32_t j = i + 1; j < line.size(); j++){
          WelcomeCounter += line[j].welcome == true ? 1 : 0;
          WelcomeCounter -= line[j].welcome == false ? 1 : 0;
          if(WelcomeCounter == 0){
            if(line[i].connectType != line[j].type){
              Corrupted = true;
              break;
            }
            line[i].connection = &line[j];
            line[j].connection = &line[i];
            break;
          }
        }
      }
      if(Corrupted){
        break;
      }
    }
    for(auto unit : line){
      if(unit.connection == nullptr){
        Complete = false;
        break;
      }
    }
    if(!Corrupted && !Complete){
      std::vector<char> TypeBuffer;
      for(std::uint32_t i = 0; i < line.size(); i++){
        if(line[i].connection == nullptr){
          TypeBuffer.push_back(line[i].connectType);
        }
      }
      std::uint64_t ScoreBuffer = 0;
      for(std::uint32_t i = TypeBuffer.size(); i > 0; i--){
        ScoreBuffer *= 5;
        ScoreBuffer += TypeBuffer[i - 1] == ')' ? PARENTHESIS_SCORE : 0;
        ScoreBuffer += TypeBuffer[i - 1] == ']' ? SQUARE_BRACKET_SCORE : 0;
        ScoreBuffer += TypeBuffer[i - 1] == '}' ? CURLY_BRACKET_SCORE : 0;
        ScoreBuffer += TypeBuffer[i - 1] == '>' ? ANGLE_BRACKET_SCORE : 0;
      }
      Scores.push_back(ScoreBuffer);
    }
  }

  if(Scores.size() >= 2){
    bool Complete = false;
    while(!Complete){
      std::vector<std::uint32_t> IndicesBuffer; 
      for(std::uint32_t i = 0; i < Scores.size(); i++){
        for(std::uint32_t j = i == 0 ? 1 : 0; j < (i == Scores.size() - 1 ? Scores.size() - 1 : Scores.size()); j += (j + 1 == i ? 2 : 1)){
          bool Taken = false;
          for(auto index : IndicesBuffer){
            if(index == j){
              Taken = true;
              break;
            }
          }
          if((!Taken && Scores[i] <= Scores[j]) || (Taken && j != 0 && Scores[i] <= Scores[j] && Scores[i] >= Scores[j - 1])){
            for(std::uint32_t k = i; k != (i < j ? j - 1 : j); k = (i < j ? k + 1 : k - 1)){
              std::uint64_t ScoreBuffer = Scores[k];
              Scores[k] = Scores[i < j ? k + 1 : k - 1];
              Scores[i < j ? k + 1 : k - 1] = ScoreBuffer;
            }
            IndicesBuffer.push_back(j);
            break;
          }
        }
      }
      for(std::uint32_t i = 0; i < Scores.size() - 1; i++){
        if(Scores[i] <= Scores[i + 1]){
          Complete = true;
        }else{
          Complete = false;
          break;
        }
      }
    }
    std::uint32_t MiddleIndex = (Scores.size() / 2);
    Result = Scores[MiddleIndex];
  }

  return Result;

}

int main(void){

  std::vector<std::string> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);
  std::cout << calculate_errorScore(ReportInputs) << std::endl;
  std::cout << calculate_completionScore(ReportInputs) << std::endl;


/* --------------TESTING PARSE----------------*/
//  for(auto i : ReportInputs){
//    std::cout << i << std::endl;
//  }
/* --------------TESTING PARSE----------------*/

  return 0;

}
