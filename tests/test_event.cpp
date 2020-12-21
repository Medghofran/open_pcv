#include <iostream>
#include <opcv/utils/logger.hpp>
#include <opcv/utils/events.hpp>

int main() {
  opcv::utils::logger logger(std::cout);

  // define a custom delegate
  delegate(void, execute, (), ());
  // instantiate an event with the above defined delegate
  event(execute, onTimeExecute);

  // assign custom payload for the event
  onTimeExecute += [=]() {
    logger.logInfo("Triggered from inside the event");
  };

  // invoke the event
  onTimeExecute.invoke();

  return 0;
}