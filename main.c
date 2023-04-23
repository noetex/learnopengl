#include<windows.h>
#include<stdint.h>
#include<math.h>

#include"main.h"
#include"khrplatform.h"
#include"opengl.h"

#include"opengl.c"
#include"shader.c"

#pragma comment(lib, "kernel32")
#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "libucrt")

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
			GetClientRect(Window, &WindowRect);
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
	HWND Result = CreateWindowExW(0, WindowClass.lpszClassName, L"Window", WindowStyle, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, Instance, 0);
	Assert(IsWindow(Result));
	return Result;
}

static void
DisableDPIScaling(void)
{
	HMODULE Library = LoadLibraryW(L"user32.dll");
	void* Function = GetProcAddress(Library, "SetProcessDpiAwarenessContext");
	if(Function)
	{
		typedef BOOL new_function(DPI_AWARENESS_CONTEXT);
		new_function* SetProcessDpiAwarenessContext = Function;
		SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
		return;
	}
	Function = GetProcAddress(Library, "SetProcessDpiAware");
	if(Function)
	{
		typedef BOOL old_function(void);
		old_function* SetProcessDpiAware = Function;
		SetProcessDpiAware();
	}
}

float Triangle[] =
{
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.5f,	0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
};

void WinMainCRTStartup()
{
	DisableDPIScaling();
	HWND Window = CreateOpenGLWindow();
	HDC WindowDC = GetDC(Window);
	SetOpenGLContext(Window);
	LoadOpenGLFunctions();

	GLuint VertexArray;
	GLuint VertexBuffer;
	glGenVertexArrays(1, &VertexArray);
	glGenBuffers(1, &VertexBuffer);

	glBindVertexArray(VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	GLuint VertexShader = CreateOpenGLShader("../shader.vert", GL_VERTEX_SHADER);
	GLuint FragmentShader = CreateOpenGLShader("../shader.frag", GL_FRAGMENT_SHADER);
	GLuint ShaderProgram = CreateOpenGLProgram(VertexShader, FragmentShader);
	glUseProgram(ShaderProgram);
	int OffsetLocation = glGetUniformLocation(ShaderProgram, "Offset");
	MSG Message = {0};
	for(;;)
	{
		while(PeekMessageW(&Message, 0, 0, 0, PM_REMOVE))
		{
			if(Message.message == WM_QUIT)
			{
				ExitProcess(0);
			}
			DispatchMessageW(&Message);
		}
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		SwapBuffers(WindowDC);
	}
}