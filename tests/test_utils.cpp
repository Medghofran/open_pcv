#include <functional>

int main() {
  (+[]() { std::cout << "professional retard\n"; })();
}