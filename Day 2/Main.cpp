#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <fstream>

#define PART_2

enum class DIRECTION{
  NOT_SET = -1,
  FORWARD = 0,
  UP = 1,
  DOWN = 2,
};

struct intvec64_st{
  std::int32_t x;
  std::int32_t y;
};

struct velunit_st{
  DIRECTION direction;
  std::uint32_t speed;
};

class submarine{
public:
  submarine():coordinates({0, 0}), aim(0){}
  ~submarine(){
    coordinates.x = 0;
    coordinates.y = 0;
  }
#if defined(PART_1)
  void move(const std::uint32_t& value){
  
    coordinates.x += value;
  
    return;
  
  }
  void change_depth(const std::int32_t& value){
  
    coordinates.y += value;
  
    return;
  
  }
#elif defined(PART_2)
  void move(const std::uint32_t& value){
    
    coordinates.x += value;
    coordinates.y += value * aim;
    
    return;
    
  }
  void change_depth(const std::int32_t& value){
  
    aim += value;
  
    return;
  
  }
#endif
  
  struct intvec64_st get_coordinates(){
  
    return coordinates;
  
  }
  
private:
  struct intvec64_st coordinates;
  std::int32_t aim;
};

void parse_inputFile(const std::string& filePath, std::vector<struct velunit_st>& vectorOutput){
  
  std::ifstream InputFile(filePath);

  std::string StringBuffer = {0};
  for(std::uint32_t i = 0; std::getline(InputFile, StringBuffer); i++){
    std::uint32_t IntBuffer = 0;
    IntBuffer = StringBuffer[StringBuffer.length() - 1] - 48;
    if(StringBuffer[0] == 'f'){
        vectorOutput.push_back({DIRECTION::FORWARD, IntBuffer});
    }else if(StringBuffer[0] == 'u'){
      vectorOutput.push_back({DIRECTION::UP, IntBuffer});
    }else if(StringBuffer[0] == 'd'){
      vectorOutput.push_back({DIRECTION::DOWN, IntBuffer});
    }
  }

  InputFile.close();
  
  return;
  
}

int main(void){

  std::vector<velunit_st> ReportInputs;
  parse_inputFile("Input.txt", ReportInputs);
  
  submarine MainSub;
  for(velunit_st v : ReportInputs){
    if(v.direction == DIRECTION::FORWARD){
      MainSub.move(v.speed);
    }else if(v.direction == DIRECTION::UP){
      MainSub.change_depth(v.speed * -1);
    }else if(v.direction == DIRECTION::DOWN){
      MainSub.change_depth(v.speed);
    }
  }
  
  std::cout << "{" << MainSub.get_coordinates().x << ", "<< MainSub.get_coordinates().y << "}" << " == " << MainSub.get_coordinates().x * MainSub.get_coordinates().y << std::endl;

/* --------------TESTING PARSE----------------*/
//  for(velunit_st v : ReportInputs){
//    if(v.direction == DIRECTION::FORWARD){
//      std::cout << "FORWARD: " << v.speed << std::endl;
//    }else if(v.direction == DIRECTION::UP){
//      std::cout << "UP: " << v.speed << std::endl;
//    }else if(v.direction == DIRECTION::DOWN){
//      std::cout << "DOWN: " << v.speed << std::endl;
//    }
//  }
/* --------------TESTING PARSE----------------*/

  return 0;

}
