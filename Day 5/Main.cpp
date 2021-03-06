#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

struct uivec64_st{
  std::uint32_t x;
  std::uint32_t y;
};
struct lineSeg128_st{
  struct uivec64_st x1y1;
  struct uivec64_st x2y2;
};

struct gridPoint_st{
  struct uivec64_st coordinates;
  std::uint32_t value;
};

class grid_cl{
public:
  grid_cl(const std::uint32_t& rowCountInput, const std::uint32_t& columnCountInput, const bool& diagonalApplyInput){

    for(std::uint32_t i = 0; i < rowCountInput; i++){
      for(std::uint32_t j = 0; j < columnCountInput; j++){
        points.push_back({{i, j}, 0});
      }
    }
    rowCount = rowCountInput;
    columnCount = columnCountInput;
    diagonalApply = diagonalApplyInput;

  }
  ~grid_cl(){

    for(auto p : points){
      points.pop_back();
    }

  }

  void add_segments(const std::vector<struct lineSeg128_st>& lineInput){

    for(auto line : lineInput){
      if((line.x1y1.x == line.x2y2.x) || (line.x1y1.y == line.x2y2.y)){
        if((line.x1y1.x < line.x2y2.x) || (line.x1y1.y < line.x2y2.y)){
          for(std::int32_t i = line.x1y1.x + (line.x1y1.y * columnCount); i != ((line.x2y2.x + (line.x2y2.y * columnCount)) + (columnCount * (line.x1y1.x == line.x2y2.x))) + (line.x1y1.y == line.x2y2.y); i += (columnCount * (line.x1y1.y != line.x2y2.y)) + (line.x1y1.x != line.x2y2.x)){
            points[i].value++;
          }
        }else if((line.x1y1.x > line.x2y2.x) || (line.x1y1.y > line.x2y2.y)){
          for(std::int32_t i = line.x1y1.x + (line.x1y1.y * columnCount); i != ((line.x2y2.x + (line.x2y2.y * columnCount)) - (columnCount * (line.x1y1.x == line.x2y2.x))) - (line.x1y1.y == line.x2y2.y); i -= (columnCount * (line.x1y1.y != line.x2y2.y)) + (line.x1y1.x != line.x2y2.x)){
            points[i].value++;
          }
        }
      }else if(((line.x1y1.x - line.x2y2.x) + ((line.x1y1.x < line.x2y2.x) * ((line.x2y2.x - line.x1y1.x) * 2))) == ((line.x1y1.y - line.x2y2.y) + ((line.x1y1.y < line.x2y2.y) * ((line.x2y2.y - line.x1y1.y) * 2)))){
        if(diagonalApply == true){
          if((line.x1y1.x < line.x2y2.x) && (line.x1y1.y < line.x2y2.y)){
            for(std::uint32_t i = line.x1y1.x + (line.x1y1.y * columnCount); i != ((line.x2y2.x + (line.x2y2.y * columnCount)) + (columnCount + 1)); i += columnCount + 1){
              points[i].value++;
            }
          }else if((line.x1y1.x > line.x2y2.x) && (line.x1y1.y < line.x2y2.y)){
            for(std::int32_t i = line.x1y1.x + (line.x1y1.y * columnCount); i != ((line.x2y2.x + (line.x2y2.y * columnCount)) + (columnCount - 1)); i += columnCount - 1){
              points[i].value++;
            }
          }else if((line.x1y1.x > line.x2y2.x) && (line.x1y1.y > line.x2y2.y)){
            for(std::int32_t i = line.x1y1.x + (line.x1y1.y * columnCount); i != ((line.x2y2.x + (line.x2y2.y * columnCount)) - (columnCount + 1)); i -= columnCount + 1){
              points[i].value++;
            }
          }else if((line.x1y1.x < line.x2y2.x) && (line.x1y1.y > line.x2y2.y)){
            for(std::int32_t i = line.x1y1.x + (line.x1y1.y * columnCount); i != ((line.x2y2.x + (line.x2y2.y * columnCount)) - (columnCount - 1)); i -= columnCount - 1){
              points[i].value++;
            }
          }
        }
      }
    }

    return;

  }

  std::uint32_t count_overlaps(void){

    std::uint32_t OverlapCount = 0;
    for(auto p : points){
      if(p.value >= 2){
        OverlapCount++;
      }
    }

    return OverlapCount;

  }

private:
  std::vector<gridPoint_st> points;
  std::uint32_t rowCount;
  std::uint32_t columnCount;
  bool diagonalApply;
};

void parse_inputFile(const std::string& filePath, std::vector<struct uivec64_st>& vectorOutput){

  std::ifstream InputFile(filePath);

  std::string StringBuffer = {0};
  while(std::getline(InputFile, StringBuffer)){
    for(std::uint32_t i = 0; i < StringBuffer.size(); i++){
      std::uint32_t DigitCount = 0;
      while(StringBuffer[i + DigitCount] != ','){
        DigitCount++;
      }
      std::uint32_t XBuffer = 0;
      std::uint32_t Multiplier = 1;
      for(std::uint32_t j = DigitCount; j != 0; j--){
        XBuffer += (StringBuffer[i + (j - 1)] - 48) * Multiplier;
        Multiplier *= 10;
      }
      i += DigitCount + 1;
      DigitCount = 0;
      while((StringBuffer[i + DigitCount] != ' ') && (StringBuffer[i + DigitCount] != '\0')){
        DigitCount++;
      }
      std::uint32_t YBuffer = 0;
      Multiplier = 1;
      for(std::uint32_t j = DigitCount; j != 0; j--){
        YBuffer += (StringBuffer[i + (j - 1)] - 48) * Multiplier;
        Multiplier *= 10;
      }
      i += (DigitCount + 1) + 2;
      vectorOutput.push_back({XBuffer, YBuffer});
    }
  }
  InputFile.close();

  return;

}

void convert_pointsToSegment(const std::vector<struct uivec64_st>& vectorInput, std::vector<struct lineSeg128_st>& vectorOutput){

  for(std::uint32_t i = 0; i < vectorInput.size(); i += 2){
    vectorOutput.push_back({vectorInput[i], vectorInput[i + 1]});
  }

  return;

}

void find_overlaps(){
  
}

int main(void){

  std::vector<struct uivec64_st> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);
  std::vector<struct lineSeg128_st> SegmentVector;
  convert_pointsToSegment(ReportInputs, SegmentVector);
  grid_cl MainGrid(1000, 1000, true);
  MainGrid.add_segments(SegmentVector);
  std::cout << MainGrid.count_overlaps() << std::endl;

/* --------------TESTING PARSE----------------*/
//  for(auto line : SegmentVector){
//    std::cout << '{' << line.x1y1.x << ',' << line.x1y1.y << '}' << "->" << '{' << line.x2y2.x << ',' << line.x2y2.y << '}' << std::endl;
//  }
//  std::cout << std::endl;
//  std::cout << "===================FIRST THREE=================" << std::endl;
//  std::cout << '{' << SegmentVector[0].x1y1.x << ',' << SegmentVector[0].x1y1.y << '}' << "->" << '{' << SegmentVector[0].x2y2.x << ',' << SegmentVector[0].x2y2.y << '}' << std::endl;
//  std::cout << '{' << SegmentVector[1].x1y1.x << ',' << SegmentVector[1].x1y1.y << '}' << "->" << '{' << SegmentVector[1].x2y2.x << ',' << SegmentVector[1].x2y2.y << '}' << std::endl;
//  std::cout << '{' << SegmentVector[2].x1y1.x << ',' << SegmentVector[2].x1y1.y << '}' << "->" << '{' << SegmentVector[2].x2y2.x << ',' << SegmentVector[2].x2y2.y << '}' << std::endl;
/* --------------TESTING PARSE----------------*/

  return 0;

}
