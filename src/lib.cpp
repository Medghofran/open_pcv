#include <iostream>
#include <opcv/utils/timeblock.hpp>
#include <opcv/utils/logger.hpp>


void empty_procedure() {
  // do some heinous shit here
}

int main() {
  {
    opcv::utils::microtimer timer("Time taken inside the current scope ", std::cout);
    for (int i = 0; i++ < 100;)
      ;
  }


  opcv::utils::logger logger(std::cout);
  logger.logInfo("working like potatoes");
  logger.logInfo<short>("still working like potatoes");

  logger.logWarning("working like potatoes");
  logger.logWarning<short>("still working like potatoes");

  logger.logError("working like potatoes");
  logger.logError<short>("still working like potatoes");
  std::cout << "working" << std::endl;
}