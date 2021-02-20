#include <iostream>
#include <filesystem>

#include "windows.h"

using std::cout;
using std::endl;

//const char g_szClassName[] = "myWindowClass";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  std::filesystem::path p = std::filesystem::path(__FILE__)
      .parent_path()
      .parent_path()
      .parent_path()
      .append("test")
      .append("resources")
      .append("bmp")
      .append("CMakeInstall.bmp");

  cout << "0: " << p.string() << endl;
  cout << "1: " << hInstance << endl;
  //cout << "2: " << hInstance->i << endl;
  cout << "3: " << hPrevInstance << endl;
  //cout << "4: " << hPrevInstance->i << endl;
  cout << "5: " << lpCmdLine << endl;
  cout << "6: " << nCmdShow << endl;
  return 0;
}
