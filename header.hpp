#undef UNICODE
#define _M_IX86
#include <windows.h>
#include <iostream>
#include <string.h>
#include <tchar.h>
#include <cstdlib>      
#include <fstream>
#include <algorithm>



char fileNameCache[1024];
HWND saveAsButton;
HWND saveButton;
HWND loadButton;
HWND textEdit;
char text[100000];

void writeFile( LPSTR fileName,  LPSTR message);
std::string replaceCharacter(std::string source, char find, char replace);
void loadFile(LPSTR fileName);   