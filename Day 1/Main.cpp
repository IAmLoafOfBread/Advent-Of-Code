#include <iostream>
#include <stdint.h>

#include "Test.hpp"

int main(){

  for(uint32_t i = 0; i < 12; i++){
    std::cout << "YOOO: " << i << std::endl;
  }
  test('z');

  return 0;

}
