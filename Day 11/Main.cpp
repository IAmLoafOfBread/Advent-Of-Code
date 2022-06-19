#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

struct gridunit_st{
  std::uint32_t value;
  std::uint32_t flashCount;
  std::uint32_t remainder;
  std::uint32_t chainedFlashes;
  std::uint32_t chainedRemainder;
};

void parse_inputFile(const std::string& filePath, std::vector<std::vector<std::uint32_t>>& vectorOutput){

  std::ifstream InputFile(filePath);

  std::string StringBuffer;
  while(std::getline(InputFile, StringBuffer)){
    std::vector<std::uint32_t> RowBuffer;
    for(auto ch : StringBuffer){
      RowBuffer.push_back(ch - 48);
    }
    vectorOutput.push_back(RowBuffer);
  }

  InputFile.close();

  return;

}

std::uint32_t calculate_flashes(const std::vector<std::vector<std::uint32_t>>& vectorInput, const std::uint32_t& stepCount){

  std::vector<std::vector<gridunit_st>> GridUnits;
  for(auto row : vectorInput){
    std::vector<gridunit_st> RowBuffer;
    for(auto unit : row){
      RowBuffer.push_back({unit, 0, 0, 0, 0});
    }
    GridUnits.push_back(RowBuffer);
  }
  const std::int32_t RowIndexerArray[] = {
    -1,
    0,
    1,
    -1,
    1,
    -1,
    0,
    1,
  };
  const std::int32_t UnitIndexerArray[] = {
    -1,
    -1,
    -1,
    0,
    0,
    1,
    1,
    1,
  };
  const std::uint32_t IndexerArraySize = sizeof(UnitIndexerArray) / sizeof(UnitIndexerArray[0]);

  std::uint32_t Result = 0;
  for(std::int32_t i = 0; i < GridUnits.size(); i++){
    for(std::int32_t j = 0; j < GridUnits[0].size(); j++){
      GridUnits[i][j].flashCount = (stepCount + GridUnits[i][j].value) / 10;
      GridUnits[i][j].remainder = (stepCount + GridUnits[i][j].value) % 10;
      for(std::uint32_t k = 0; k < IndexerArraySize; k++){
        if((i + RowIndexerArray[k] >= 0) && (i + RowIndexerArray[k] < GridUnits.size()) && (j + UnitIndexerArray[k] >= 0) && (j + UnitIndexerArray[k] < GridUnits[0].size())){
          GridUnits[i + RowIndexerArray[k]][j + UnitIndexerArray[k]].chainedFlashes += (stepCount + GridUnits[i][j].value) / 10;
          GridUnits[i + RowIndexerArray[k]][j + UnitIndexerArray[k]].chainedRemainder += (stepCount + GridUnits[i][j].value) % 10;
        }
      }
    }
  }
  for(auto row : GridUnits){
    for(auto unit : row){
      Result += unit.flashCount;
    }
  }

  return Result;

}

int main(void){

  std::vector<std::vector<std::uint32_t>> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);
  std::cout << calculate_flashes(ReportInputs, 100) << std::endl;

/* --------------TESTING PARSE----------------*/
//  for(auto row : ReportInputs){
//    for(auto unit : row){
//      std::cout << unit;
//    }
//    std::cout << std::endl;
//  }
/* --------------TESTING PARSE----------------*/

  return 0;

}
