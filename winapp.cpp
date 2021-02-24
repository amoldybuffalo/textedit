//#ifndef UNICODE

//#define UNICODE

//#endif 

#undef UNICODE
#define _M_IX86
#include <windows.h>
#include <iostream>
#include <string.h>
#include <tchar.h>
#include <cstdlib>      
#include <fstream>

char fileNameCache[1024];

HWND saveAsButton;

HWND saveButton;

HWND loadButton;

HWND textEdit;

constexpr long long hsaveAsButton = 5ll;
constexpr long long hsaveButton = 6ll;
constexpr long long hloadButton = 7ll;

char text[2000];

void writeFile( LPSTR fileName,  LPSTR message)

{

   std::ofstream file;
   file.open(fileName);
   file << message;
   file.close();

}

void loadFile(LPSTR fileName)    

{   std::string str;

    std::string fileContents;

    std::ifstream file;

    file.open(fileName);

    while (std::getline(file, str))
    {  

      fileContents += str; 

      fileContents += "\r\n";    

    }

    file.close();

    SetWindowText(textEdit, (LPSTR)fileContents.c_str());

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)

{

    // Register the window class.

    "Sample Window Class";
    WNDCLASS wc = { };
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = "Sample Window Class";

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowExA(

        0,                              // Optional window styles.

        "Sample Window Class",                     // Window class

        "Textedit rookie edition",    // Window text

        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // Parent window    
        NULL,       // Menu

        hInstance,  // Instance handle

        NULL        // Additional application data

        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {

    case WM_COMMAND:
    {
        if(LOWORD(wParam)==hsaveAsButton && HIWORD(wParam)==BN_CLICKED)
        {   GetWindowText(textEdit, text, sizeof(text));
            OPENFILENAME ofn;       // common dialog box structure
            TCHAR szFile[260] = { 0 };       // if using TCHAR macros

            // Initialize OPENFILENAME
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwnd;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST;

            if (GetSaveFileName(&ofn) == TRUE)
            {   strcpy(fileNameCache, (char*)ofn.lpstrFile);
                writeFile(ofn.lpstrFile, text);
                std::cout << fileNameCache;
            }
        }

        else if(LOWORD(wParam)==hsaveButton && HIWORD(wParam)==BN_CLICKED)
        {   
            GetWindowText(textEdit, text, sizeof(text));
            writeFile(fileNameCache, text);
        }

        else if(LOWORD(wParam)==hloadButton && HIWORD(wParam)==BN_CLICKED)
        {
            OPENFILENAME ofn;       // common dialog box structure
            TCHAR szFile[260] = { 0 };       // if using TCHAR macros

            // Initialize OPENFILENAME
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwnd;
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST;

            if (GetOpenFileName(&ofn) == TRUE)
            {   strcpy(fileNameCache, (char*)ofn.lpstrFile)
                loadFile(ofn.lpstrFile);
            }

        }
        return 0;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }

    case WM_CREATE:
    {
        saveAsButton = CreateWindow("BUTTON", "save as", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  10, 10, 90, 40, hwnd, (HMENU)hsaveAsButton, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);  
        saveButton = CreateWindow("BUTTON", "save", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  110, 10, 90, 40, hwnd, (HMENU)hsaveButton, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        loadButton = CreateWindow("BUTTON", "load", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  210, 10, 90, 40, hwnd, (HMENU)hloadButton, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        textEdit = CreateWindow("EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE | WS_VSCROLL, 5, 60, 1350, 650, hwnd, NULL,(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE) , NULL );
        return 0;     
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
        EndPaint(hwnd, &ps);
        return 0;
    }

        

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

     