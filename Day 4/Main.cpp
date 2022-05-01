#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

struct unitMatrix128_st{
  float value;
  std::uint32_t index;
  std::uint32_t rowIndex;
  std::uint32_t columnIndex;
};

class matrixDynamic_cl{
public:
  std::uint32_t unitCount;
  std::uint32_t rowCount;
  std::uint32_t columnCount;

  matrixDynamic_cl(bool fillDefault){

    if(fillDefault == true){
      std::uint32_t UnitIndex = 0;
      for(std::uint32_t i = 0; i < 3; i++){
        std::vector<unitMatrix128_st> DefaultFiller;
        for(std::uint32_t j = 0; j < 3; j++){
          if(i == j){
            DefaultFiller.push_back({1, UnitIndex, i, j});
          }else{
            DefaultFiller.push_back({0, UnitIndex, i, j});
          }
          UnitIndex++;
        }
        units.push_back(DefaultFiller);
      }
      update_matrixAttributes();

      built = true;
    }else{

      built = false;
    }

  }
  ~matrixDynamic_cl(){

    for(std::vector<unitMatrix128_st> r : units){
      for(unitMatrix128_st u : r){
        r.pop_back();
      }
      units.pop_back();
    }

  }

  void build(const std::vector<float>& inputVector, const std::uint32_t& rows, const std::uint32_t& columns){

    if(!(built)){
      std::uint32_t UnitIndex = 0;
      for(std::uint32_t i = 0; i < rows; i++){
        std::vector<unitMatrix128_st> vectorBuffer;
        for(std::uint32_t j = 0; j < columns; j++){
          vectorBuffer.push_back({inputVector[UnitIndex], UnitIndex, i, j});
          UnitIndex++;
        }
        units.push_back(vectorBuffer);
      }
      update_matrixAttributes();

      built = true;
    }

    return;

  }

  float acquire_value(std::uint32_t row, std::uint32_t column){

    return units[row][column].value;

  }
  float acquire_valueByIndex(std::uint32_t index){

    for(std::vector<unitMatrix128_st> r : units){
      for(unitMatrix128_st u : r){
        if(u.index == index){

          return u.value;

        }
      }
    }

  }

  void log(void){
    for(std::vector<unitMatrix128_st> r : units){
      std::cout << "{ ";
      for(std::uint32_t i = 0; i < r.size(); i++){
        if(i + 1 != r.size()){
          std::cout << r[i].value << ' ';
        }else{
          std::cout << r[i].value;
        }
      }
      std::cout << " }\n";
    }

    return;

  }

private:
  std::vector<std::vector<unitMatrix128_st>> units;
  bool built;

  void update_matrixAttributes(void){

    unitCount = units[0].size() * units.size();
    rowCount = units.size();
    columnCount = units[0].size();

    return;

  }
};

struct bingoBoard_st{
  matrixDynamic_cl matrix;
  std::vector<std::uint32_t> markedIndices;
};

class bingoGame_cl{
public:
  bingoGame_cl(std::vector<std::uint32_t> markersInput, std::vector<matrixDynamic_cl> boardsInput){
    markers = markersInput;
    for(matrixDynamic_cl m : boardsInput){
      boards.push_back({m, {0}});
    }
  }
  ~bingoGame_cl(){
  }

  void begin(){

    for(std::uint32_t marker : markers){
      for(std::uint32_t i = 0; i < boards.size(); i++){
        for(std::uint32_t j = 0; j < boards[0].matrix.unitCount; j++){
          if(boards[i].matrix.acquire_valueByIndex(j) == marker){
            boards[i].markedIndices.push_back(j);
          }
        }
      }
    }

  }

private:
  std::vector<std::uint32_t> markers;
  std::vector<bingoBoard_st> boards;
  std::uint32_t winnerIndex;
  std::uint32_t winnerScore;
};

void parse_inputFile(const std::string& filePath, std::vector<std::uint32_t>& comparerOutput, std::vector<matrixDynamic_cl>& vectorOutput){

  std::ifstream InputFile(filePath);

  std::string StringBuffer = {0};
  std::getline(InputFile, StringBuffer);
  StringBuffer.push_back('\n');
  for(std::uint32_t i = 0; i < StringBuffer.size(); i++){
    std::uint32_t DigitCount = 0;
    while((StringBuffer[i + DigitCount] != ',') && (StringBuffer[i + DigitCount] != '\n')){
      DigitCount++;
    }
    std::uint32_t IntBuffer = 0;
    std::uint32_t Multiplier = 1;
    for(std::uint32_t j = 0; j < DigitCount; j++){
      IntBuffer += (StringBuffer[i + ((DigitCount - 1) - j)] - 48) * Multiplier;
      Multiplier *= 10;
    }
    comparerOutput.push_back(IntBuffer);
    i += DigitCount;
  }
  std::uint32_t MatrixIndex = 0;
  for(std::uint32_t i = 0; std::getline(InputFile, StringBuffer); i++){
    StringBuffer.push_back('\n');
    std::vector<float> VectorBuffer;
    if(StringBuffer[0] == '\n'){
      for(std::uint32_t j = 0; j < 5; j++){
        std::getline(InputFile, StringBuffer);
        StringBuffer.push_back('\n');
        for(std::uint32_t k = 0; k < StringBuffer.size(); k++){
          if(StringBuffer[k] != ' '){
            std::uint32_t DigitCount = 0;
            while((StringBuffer[k + DigitCount] != ' ') && (StringBuffer[k + DigitCount] != '\n')){
              DigitCount++;
            }
            std::uint32_t Multiplier = 1;
            std::uint32_t IntBuffer = 0;
            for(std::uint32_t l = DigitCount; l > 0; l--){
              IntBuffer += (StringBuffer[k + (l - 1)] - 48) * Multiplier;
              Multiplier *= 10;
            }
            VectorBuffer.push_back(IntBuffer);
            k += DigitCount;
          }
        }
      }
      vectorOutput.push_back({0});
      vectorOutput[MatrixIndex].build(VectorBuffer, 5, 5);
      MatrixIndex++;
    }
  }
  InputFile.close();

  return;

}

int main(void){

  std::vector<std::uint32_t> ComparerInputs;
  std::vector<matrixDynamic_cl> MatrixInputs;
  parse_inputFile("Input.txt", ComparerInputs, MatrixInputs);

/* --------------TESTING PARSE----------------*/
//  for(matrixDynamic_cl m : MatrixInputs){
//    m.log();
//    std::cout << std::endl;
//  }
//  std::cout << "=============COMPARERS AND THE FIRST THREE========" << std::endl;
//  for(std::uint32_t v : ComparerInputs){
//    std::cout << v << ' ';
//  }
//  std::cout << std::endl;
//  std::cout << std::endl;
//  MatrixInputs[0].log();
//  std::cout << std::endl;
//  MatrixInputs[1].log();
//  std::cout << std::endl;
//  MatrixInputs[2].log();
/* --------------TESTING PARSE----------------*/

  return 0;

}
