#include <iostream>
#include "repository.hpp"

int main() {

  try{
    Repository repository{}; 
    repository.PrintCounties();
  }

  catch (std::exception &e) {
    std::cerr << e.what();
  }

  return 0;
}
