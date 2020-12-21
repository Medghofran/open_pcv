#include <functional>
#include <iostream>

int main() {
  (+[]() { std::cout << "professional retard\n"; })();
}