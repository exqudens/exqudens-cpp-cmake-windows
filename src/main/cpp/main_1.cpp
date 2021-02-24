#include <iostream>
#include <filesystem>
#include <string>

#include "windows.h"

using std::cout;
using std::endl;

//const char g_szClassName[] = "myWindowClass";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  std::string modulePath;
  std::string currentPath = std::filesystem::current_path().string();
  std::filesystem::path p = std::filesystem::path(__FILE__)
      .parent_path()
      .parent_path()
      .parent_path()
      .append("test")
      .append("resources")
      .append("bmp")
      .append("CMakeInstall.bmp");

  HMODULE hModule = GetModuleHandle(nullptr);
  if (hModule) {
    char path[10000] = "";
    GetModuleFileNameA(hModule, path, sizeof(path));
    modulePath = std::string(path);
  }

  cout << "0: " << modulePath << endl;
  cout << "1: " << currentPath << endl;
  cout << "2: " << p.string() << endl;
  cout << "3: " << hInstance << endl;
  cout << "4: " << hPrevInstance << endl;
  cout << "5: " << lpCmdLine << endl;
  cout << "6: " << nCmdShow << endl;

  //

  return 0;
}
