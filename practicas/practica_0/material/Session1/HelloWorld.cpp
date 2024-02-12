/** 
 * @file main.cpp
 * @author lcv
 * @date 10 de febrero de 2020, 12:59
 */

#include <iostream>
using namespace std;
class Helloworld {
private:
  string message;
public:
  Helloworld(){ 
    message="Hello world!";
  }
  void print() {
    cout << endl << message << endl;
  }
  void set(string s) {
    message = s;
  }
};

int main() {
  Helloworld hw;
  hw.set("Hola mundo!");
  hw.print();
  return 0;
}