/*
    Compile commands (extreme low memory, no CRT, Windows 95+ safe):

    GCC (MinGW‑w64) – 32‑bit:
      gcc -m32 -Os -nostdlib -e WinMainCRTStartup -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--stack,65536 -mwindows -o KeepScreenOn32.exe KeepScreenOn.c -lkernel32 -luser32 -lgdi32

    GCC (MinGW‑w64) – 64‑bit:
      gcc -m64 -Os -nostdlib -e WinMainCRTStartup -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--stack,65536 -mwindows -o KeepScreenOn64.exe KeepScreenOn.c -lkernel32 -luser32 -lgdi32

    MSVC – 32‑bit (x86 Native Tools Command Prompt):
      cl /Os /GS- /NODEFAULTLIB /FeKeepScreenOn32.exe KeepScreenOn.c /link /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup kernel32.lib user32.lib gdi32.lib

    MSVC – 64‑bit (x64 Native Tools Command Prompt):
      cl /Os /GS- /NODEFAULTLIB /FeKeepScreenOn64.exe KeepScreenOn.c /link /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup kernel32.lib user32.lib gdi32.lib

    Clang (MinGW target) – 32‑bit:
      clang -m32 -Os -nostdlib -e WinMainCRTStartup -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--stack,65536 -mwindows -o KeepScreenOn32.exe KeepScreenOn.c -lkernel32 -luser32 -lgdi32

    Clang (MinGW target) – 64‑bit:
      clang -m64 -Os -nostdlib -e WinMainCRTStartup -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--stack,65536 -mwindows -o KeepScreenOn64.exe KeepScreenOn.c -lkernel32 -luser32 -lgdi32

    Clang‑CL (MSVC‑compatible, x86 environment):
      clang-cl /Os /GS- /NODEFAULTLIB /FeKeepScreenOn32.exe KeepScreenOn.c /link /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup kernel32.lib user32.lib gdi32.lib

    Clang‑CL (MSVC‑compatible, x64 environment):
      clang-cl /Os /GS- /NODEFAULTLIB /FeKeepScreenOn64.exe KeepScreenOn.c /link /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup kernel32.lib user32.lib gdi32.lib
*/
// richie‑rich90454 2026

#include <windows.h>
static BOOL screen_is_on=FALSE;
static HWND button_handle=NULL;
static HWND status_handle=NULL;
static HWND credit_handle=NULL;
typedef DWORD (WINAPI *PSetThreadExecutionState)(DWORD);
static PSetThreadExecutionState pSetThreadExecutionState=NULL;
void ToggleScreenOn(HWND parent_window){
    if (screen_is_on){
        if (pSetThreadExecutionState) pSetThreadExecutionState(ES_CONTINUOUS);
        screen_is_on=FALSE;
        SetWindowText(button_handle, "Turn On");
        SetWindowText(status_handle, "Status: Off");
    }
    else{
        if (pSetThreadExecutionState) pSetThreadExecutionState(ES_DISPLAY_REQUIRED|ES_SYSTEM_REQUIRED|ES_CONTINUOUS);
        screen_is_on=TRUE;
        SetWindowText(button_handle, "Turn Off");
        SetWindowText(status_handle, "Status: On");
    }
}
LRESULT CALLBACK WindowProcedure(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param){
    switch (message){
    case WM_CREATE:{
        HINSTANCE instance=((LPCREATESTRUCT)l_param)->hInstance;
        button_handle=CreateWindow(
            "BUTTON",
            "Turn On",
            WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
            50, 50, 200, 40,
            window_handle,
            (HMENU)1,
            instance,
            NULL);
        status_handle=CreateWindow(
            "STATIC",
            "Status: Off",
            WS_CHILD|WS_VISIBLE|SS_CENTER,
            50, 100, 200, 30,
            window_handle,
            (HMENU)2,
            instance,
            NULL);
        credit_handle=CreateWindow(
            "STATIC",
            "KeepScreenOn by richie-rich90454 written in 2026",
            WS_CHILD|WS_VISIBLE|SS_LEFT,
            50, 140, 400, 25,
            window_handle,
            (HMENU)3,
            instance,
            NULL);
        break;
    }
    case WM_SIZE:{
        int client_width=LOWORD(l_param);
        int client_height=HIWORD(l_param);
        int pad_x=50;
        int button_width=client_width-2*pad_x;
        if (button_width<100) button_width=100;
        int button_height=40;
        int status_width=client_width-2*pad_x;
        if (status_width<100) status_width=100;
        int status_height=30;
        int credit_width=client_width-2*pad_x;
        if (credit_width<100) credit_width=100;
        int credit_height=25;
        MoveWindow(button_handle, pad_x, 50, button_width, button_height, TRUE);
        MoveWindow(status_handle, pad_x, 100, status_width, status_height, TRUE);
        MoveWindow(credit_handle, pad_x, 140, credit_width, credit_height, TRUE);
        InvalidateRect(button_handle, NULL, TRUE);
        InvalidateRect(status_handle, NULL, TRUE);
        InvalidateRect(credit_handle, NULL, TRUE);
        break;
    }
    case WM_GETMINMAXINFO:{
        MINMAXINFO* mmi=(MINMAXINFO*)l_param;
        mmi->ptMinTrackSize.x=450;
        mmi->ptMinTrackSize.y=220;
        break;
    }
    case WM_COMMAND:
        if (LOWORD(w_param)==1&&HIWORD(w_param)==BN_CLICKED){
            ToggleScreenOn(window_handle);
        }
        break;
    case WM_DESTROY:
        if (pSetThreadExecutionState) pSetThreadExecutionState(ES_CONTINUOUS);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(window_handle, message, w_param, l_param);
    }
    return 0;
}
void __stdcall WinMainCRTStartup(void){
    const char WINDOW_CLASS_NAME[]="ScreenAwakeClass";
    HMODULE kernel32=GetModuleHandleA("kernel32.dll");
    if (kernel32){
        pSetThreadExecutionState=(PSetThreadExecutionState)GetProcAddress(kernel32, "SetThreadExecutionState");
    }
    HINSTANCE current_instance=GetModuleHandleA(NULL);
    WNDCLASS window_class={0};
    window_class.lpfnWndProc=WindowProcedure;
    window_class.hInstance=current_instance;
    window_class.lpszClassName=WINDOW_CLASS_NAME;
    window_class.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
    window_class.hCursor=LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&window_class);
    HWND main_window=CreateWindowEx(
        0,
        WINDOW_CLASS_NAME,
        "KeepScreenOn",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 250,
        NULL,
        NULL,
        current_instance,
        NULL);
    if (main_window==NULL){
        ExitProcess(0);
    }
    ShowWindow(main_window, SW_SHOWDEFAULT);
    UpdateWindow(main_window);
    MSG message;
    while (GetMessage(&message, NULL, 0, 0)){
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
    ExitProcess((UINT)message.wParam);
}