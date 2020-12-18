#include <filesystem>

#include "windows.h"

const char g_szClassName[] = "myWindowClass";

HBITMAP mainBitmap;

void wmPaint(HWND hwnd) {
  PAINTSTRUCT ps;
  HDC hdc;
  BITMAP bitmap;
  HDC hdcMem;
  HGDIOBJ oldBitmap;

  hdc = BeginPaint(hwnd, &ps);

  hdcMem = CreateCompatibleDC(hdc);
  HBITMAP bmp = mainBitmap;
  oldBitmap = SelectObject(hdcMem, mainBitmap);

  GetObject(bmp, sizeof(bitmap), &bitmap);

  RECT rect;
  rect.left = 0;
  rect.top = 0;
  rect.right = 64;
  rect.bottom = 64;

  HBITMAP hBmp = CreateCompatibleBitmap(
      hdc,                    // Handle to a device context
      rect.right - rect.left, // Bitmap width
      rect.bottom - rect.top  // Bitmap height
  );

  BitBlt(
      hdc,                    // Destination rectangle context handle
      0,                      // Destination rectangle x-coordinate
      0,                      // Destination rectangle y-coordinate
      rect.right - rect.left, // Destination rectangle width
      rect.bottom - rect.top, // Destination rectangle height
      hdcMem,                 // A handle to the source device context
      rect.left,              // Source rectangle x-coordinate
      rect.top,               // Source rectangle y-coordinate
      SRCCOPY                 // Raster-operation code
  );

  SelectObject(hdcMem, oldBitmap);
  DeleteDC(hdcMem);

  EndPaint(hwnd, &ps);
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_CLOSE:
      DestroyWindow(hwnd);
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_PAINT:
      wmPaint(hwnd);
      return 0;
    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
  }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  std::filesystem::path p = std::filesystem::path(__FILE__)
      .parent_path()
      .parent_path()
      .parent_path()
      .append("test")
      .append("resources")
      .append("bmp")
      .append("CMakeInstall.bmp");

  const char* pathname = strdup(p.string().c_str());

  // load our image
  mainBitmap = (HBITMAP) LoadImageA(   // load the bitmap from a file
      NULL,                            // not loading from a module, so this is NULL
      pathname,                        // the path we're loading from
      IMAGE_BITMAP,                    // we are loading a bitmap
      0, 0,                            // don't need to specify width/height
      LR_DEFAULTSIZE | LR_LOADFROMFILE // use the default bitmap size (whatever the file is), and load it from a file
  );


  WNDCLASSEX wc;
  HWND hwnd;
  MSG Msg;

  //Step 1: Registering the Window Class
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = 0;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = g_szClassName;
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  if (!RegisterClassEx(&wc)) {
    MessageBox(NULL, "Window Registration Failed!", "Error!",
               MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  // Step 2: Creating the Window
  hwnd = CreateWindowEx(
      WS_EX_CLIENTEDGE,
      g_szClassName,
      "The title of my window",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
      NULL, NULL, hInstance, NULL);

  if (hwnd == NULL) {
    MessageBox(NULL, "Window Creation Failed!", "Error!",
               MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  // Step 3: The Message Loop
  while (GetMessage(&Msg, NULL, 0, 0) > 0) {
    TranslateMessage(&Msg);
    DispatchMessage(&Msg);
  }
  return Msg.wParam;
}
