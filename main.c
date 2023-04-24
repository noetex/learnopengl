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

#pragma function(memcpy)
static void*
memcpy(void* Dest, void* Src, size_t NumBytes)
{
	while(NumBytes > 0)
	{
		*(char*)Dest = *(char*)Src;
		(char*)Dest += 1;
		(char*)Src += 1;
		NumBytes -= 1;
	}
	return Dest;
}

static void*
Malloc(size_t Size)
{
	void* Result = VirtualAlloc(0, Size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	Assert(Result);
	return Result;
}

static void
Free(void* Memory)
{
	VirtualFree(Memory, 0, MEM_RELEASE);
}

static void*
Realloc(void* Memory, size_t OldSize, size_t NewSize)
{
	if(NewSize == 0)
	{
		Free(Memory);
		return 0;
	}
	if(Memory == 0)
	{
		Memory = Malloc(NewSize);
		return Memory;
	}
	if(NewSize <= OldSize)
	{
		return Memory;
	}
	void* Result = Malloc(NewSize);
	if(Result)
	{
		memcpy(Result, Memory, OldSize);
		Free(Memory);
	}
	return Result;
}

#define STB_IMAGE_IMPLEMENTATION
#define STBI_MALLOC(Size) Malloc(Size)
#define STBI_FREE(Memory) Free(Memory)
#define STBI_REALLOC_SIZED(Memory, OldSize, NewSize) Realloc(Memory, OldSize, NewSize)
//#define STBI_NO_STDIO
#include"stb_image.h"

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

static char*
GetFileContents(char* FileName, DWORD* FileSize)
{
	HANDLE File = CreateFileA(FileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	Assert(File != INVALID_HANDLE_VALUE);
	*FileSize = GetFileSize(File, 0);
	char* Result = VirtualAlloc(0, *FileSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	Assert(Result);
	DWORD BytesRead = 0;
	ReadFile(File, Result, *FileSize, &BytesRead, 0);
	if(BytesRead != *FileSize)
	{
		VirtualFree(Result, 0, MEM_RELEASE);
		Result = 0;
	}
	CloseHandle(File);
	return Result;
}

float Triangle[] =
{
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.45f, 0.45f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.45f, 0.55f,
	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.55f, 0.45f,
	0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.55f, 0.55f,
};

GLuint Indices[] =
{
	0, 1, 2,
	1, 2, 3,	
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
	GLuint IndexBuffer;
	glGenVertexArrays(1, &VertexArray);
	glGenBuffers(1, &VertexBuffer);
	glGenBuffers(1, &IndexBuffer);

	glBindVertexArray(VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	GLuint VertexShader = CreateOpenGLShader("../shader.vert", GL_VERTEX_SHADER);
	GLuint FragmentShader = CreateOpenGLShader("../shader.frag", GL_FRAGMENT_SHADER);
	GLuint ShaderProgram = CreateOpenGLProgram(VertexShader, FragmentShader);
	glUseProgram(ShaderProgram);

	GLuint Textures[2];
	glGenTextures(2, Textures);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	DWORD FileSize = 0;
	int Width;
	int Height;
	int NumChannels;
	char* Contents = GetFileContents("../container.jpg", &FileSize);
	stbi_set_flip_vertically_on_load(1);
	unsigned char* Data = stbi_load_from_memory(Contents, FileSize, &Width, &Height, &NumChannels, 0);
	Assert(Data);
	VirtualFree(Contents, 0, MEM_RELEASE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(Data);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	Contents = GetFileContents("../awesomeface.png", &FileSize);
	Data = stbi_load_from_memory(Contents, FileSize, &Width, &Height, &NumChannels, 0);
	Assert(Data);
	VirtualFree(Contents, 0, MEM_RELEASE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(Data);

	glUniform1i(glGetUniformLocation(ShaderProgram, "Texture1"), 0);
	glUniform1i(glGetUniformLocation(ShaderProgram, "Texture2"), 1);

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
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		SwapBuffers(WindowDC);
	}
}