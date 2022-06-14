#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

struct sortelem_st{
  std::uint32_t value;
  std::uint32_t count;
};

void parse_inputFile(const std::string& filePath, std::vector<std::uint32_t>& vectorOutput){

  std::ifstream InputFile(filePath);

  std::string StringBuffer = {0};
  std::getline(InputFile, StringBuffer);
  for(std::uint32_t i = 0; i < StringBuffer.size(); i++){
    std::uint32_t DigitCount = 0;
    while((StringBuffer[i + DigitCount] != ',') && (StringBuffer[i + DigitCount] != '\0')){
      DigitCount++;
    }
    std::uint32_t IntBuffer = 0;
    std::uint32_t Multiplier = 1;
    for(std::uint32_t j = DigitCount; j != 0; j--){
      IntBuffer += (StringBuffer[i + (j - 1)] - 48) * Multiplier;
      Multiplier *= 10;
    }
    vectorOutput.push_back(IntBuffer);
    i += DigitCount;
  }

  InputFile.close();

  return;

}

void set_sort(const std::vector<std::uint32_t>& inputVector, std::vector<struct sortelem_st>& outputVector){

  std::uint32_t Index = 0;
LABEL_LOOPSTART:
  if(Index < inputVector.size()){
    for(auto& n : outputVector){
      if(n.value == inputVector[Index]){
        n.count++;
        Index++;
        goto LABEL_LOOPSTART;
      }
    }
    outputVector.push_back({inputVector[Index], 1});
    Index++;
    goto LABEL_LOOPSTART;
  }

  return;

}

float calculate_average(const std::vector<std::uint32_t>& inputVector){

  float Result = 0;
  for(auto v : inputVector){
    Result += v;
  }

  return Result / inputVector.size();

}

std::vector<std::uint32_t> calculate_medians(const std::vector<std::uint32_t>& inputVector){

  std::vector<std::uint32_t> SortVector = inputVector;
  if(SortVector.size() == 2){

    return {SortVector[0], SortVector[1]};

  }
  bool Complete = false;
  while(!(Complete)){
    for(std::uint32_t i = 0; i < SortVector.size(); i++){
      for(std::uint32_t j = i == 0 ? 1 : 0; j < SortVector.size() - (i + 1 == SortVector.size() ? 1 : 0); j += j + 1 == i ? 2 : 1){
        if(SortVector[j] > SortVector[i]){
          if(j == 0 || (SortVector[j - 1] <= SortVector[i])){
            for(std::uint32_t k = i; k > j; k--){
              std::uint32_t IntBuffer = SortVector[k - 1];
              SortVector[k - 1] = SortVector[k];
              SortVector[k] = IntBuffer;
            }
            break;
          }
          std::uint32_t IntBuffer = SortVector[j - 1];
          SortVector[j - 1] = SortVector[i];
          SortVector[i] = IntBuffer;
          break;
        }
      }
    }
    for(std::uint32_t i = SortVector.size() > 1; i < SortVector.size() - (SortVector.size() > 1); i+= i + 3 >= SortVector.size() ? 1 : 2){
      if(!(SortVector[i - (SortVector.size() > 1)] <= SortVector[i]) || !(SortVector[i + (SortVector.size() > 1)] >= SortVector[i])){
        Complete = false;
        break;
      }else if((SortVector[i - (SortVector.size() > 1)] <= SortVector[i]) && (SortVector[i + (SortVector.size() > 1)] >= SortVector[i])){
        Complete = true;
      }
    }
  }
  std::uint32_t Middle = SortVector.size() / 2;
  bool Plural = Middle == (float)SortVector.size() / 2 ? true : false;
  if(Plural){

    return {SortVector[Middle - 1], SortVector[Middle]};

  }

  return {SortVector[Middle]};

}

std::vector<std::uint32_t> calculate_modes(const std::vector<std::uint32_t>& inputVector){

  std::vector<struct sortelem_st> NodesBuffer;
  set_sort(inputVector, NodesBuffer);
  std::uint32_t PeakCount = 0;
  for(std::uint32_t i = 0; i < NodesBuffer.size(); i++){
    PeakCount = NodesBuffer[i].count > PeakCount ? NodesBuffer[i].count : PeakCount;
  }
  std::vector<std::uint32_t> ModeValues;
  for(std::uint32_t i = 0; i < NodesBuffer.size(); i++){
    if(NodesBuffer[i].count == PeakCount){
      ModeValues.push_back(NodesBuffer[i].value);
    }
  }

  return ModeValues;

}

std::uint32_t calculate_alignment(const std::vector<std::uint32_t>& inputVector, const std::uint32_t& alignValue, const bool& exponential){

  std::uint32_t FuelCost = 0;
  if(exponential){
    for(const auto& v : inputVector){
      std::uint32_t Base = v > alignValue ? (v - alignValue) + 1 : (alignValue - v) + 1;
      std::uint32_t Adder = 0;
      while(Base){
        FuelCost += Adder;
        Adder++;
        Base--;
      }
    }

    return FuelCost;

  }

  for(const auto& v : inputVector){
    FuelCost += v > alignValue ? v - alignValue : alignValue - v;
  }

  return FuelCost;

}

int main(void){

  std::vector<std::uint32_t> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);
  std::cout << "AVERAGE: " << calculate_average(ReportInputs) << std::endl;
  for(auto v : calculate_medians(ReportInputs)){
    std::cout << "MEDIANS: " << v << std::endl;
  }
  for(auto v : calculate_modes(ReportInputs)){
  std::cout << "MODES: " << v << std::endl;
  }
  std::cout << calculate_alignment(ReportInputs, calculate_average(ReportInputs), true) << std::endl;

/* --------------TESTING PARSE----------------*/
//  for(auto i : ReportInputs){
//    std::cout << i << ',';
//  }
//  std::cout << std::endl;
/* --------------TESTING PARSE----------------*/

  return 0;

}
