#include<windows.h>

#pragma comment(lib, "kernel32")
#pragma comment(lib, "user32")

#define break_if(Condition) if(!(Condition)); else break
#define Assert(Condition) if(Condition); else __debugbreak()

static LRESULT CALLBACK
WindowProc(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;
	switch(Message)
	{
		case WM_CLOSE:
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		} break;
		default:
		{
			Result = DefWindowProcW(Window, Message, wParam, lParam);
		} break;
	}
	return Result;
}

static HWND
CreateMainWindow(void)
{
	HINSTANCE Instance = GetModuleHandleW(0);
	WNDCLASSEXW WindowClass = {0};
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.hInstance = Instance;
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.lpszClassName = L"wndclass_name";
	RegisterClassExW(&WindowClass);
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	HWND Result = CreateWindowExW(0, WindowClass.lpszClassName, L"Window", WindowStyle, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, Instance, 0);
	Assert(IsWindow(Result));
	return Result;
}

void WinMainCRTStartup()
{
	HWND Window = CreateMainWindow();
	MSG Message = {0};
	for(;;)
	{
		GetMessageW(&Message, 0, 0, 0);
		break_if(Message.message == WM_QUIT);
		DispatchMessageW(&Message);
	}
}