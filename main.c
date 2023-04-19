#include<windows.h>
#include<stdint.h>

#include"main.h"
#include"khrplatform.h"
#include"opengl.h"

#include"opengl.c"

#pragma comment(lib, "kernel32")
#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "opengl32")

static LRESULT CALLBACK
WindowProc(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;
	switch(Message)
	{
		case WM_SIZE:
		{
			break_if(glViewport == 0);
			RECT WindowRect = {0};
			GetWindowRect(Window, &WindowRect);
			int WindowWidth = WindowRect.right - WindowRect.left;
			int WindowHeight = WindowRect.bottom - WindowRect.top;
			glViewport(0, 0, WindowWidth, WindowHeight);
		} break;

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
CreateOpenGLWindow(void)
{
	HINSTANCE Instance = GetModuleHandleW(0);
	WNDCLASSEXW WindowClass = {0};
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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
	HWND Window = CreateOpenGLWindow();
	HDC WindowDC = GetDC(Window);
	SetOpenGLContext(Window);
	LoadOpenGLFunctions();
	MSG Message = {0};
	for(;;)
	{
		GetMessageW(&Message, 0, 0, 0);
		do
		{
			if(Message.message == WM_QUIT)
			{
				ExitProcess(0);
			}
			DispatchMessageW(&Message);
		} while(PeekMessageW(&Message, 0, 0, 0, PM_REMOVE));
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers(WindowDC);
	}
}