#include <iostream>
#include <string>
#include <sstream>
#include <initializer_list>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

class A {
  // TODO
};

template <typename Function, typename... T>
void sequential_foreach(Function f, T... args) {
  (void) std::initializer_list<int> {
    [&](const auto& arg) {
      f(arg);
      return 0;
    } (args)...
  };
}

template <typename T>
string to_string(T object) {
  stringstream s;
  s << object;
  return s.str();
}

template <typename... T>
vector<string> to_vector_string(T... args) {
  vector<string> v1;
  sequential_foreach([&](const auto& arg) { v1.push_back(to_string(arg)); }, args...);
  return v1;
}

template <typename... T>
void print_all(T... args) {
  vector<string> v1 = to_vector_string(args...);
  for (int i = 0; i < v1.size(); i++) {
    cout << v1.at(i) << endl;
  }
}

int main() {
  print_all(1, 1.5, "a");
  //A a;
  //print_all(1, "a", a);
  return 0;
}
