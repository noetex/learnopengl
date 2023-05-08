#define NOMINMAX
#include<windows.h>
#include<stdint.h>

#define _USE_MATH_DEFINES
#include<math.h>

#include"main.h"
#include"khrplatform.h"
#include"opengl.h"

#include"opengl.c"
#include"shader.c"
#include"vmath.c"
#include"camera.c"

#define HID_USAGE_PAGE_GENERIC 0x01
#define HID_USAGE_GENERIC_MOUSE 0x02

#define to_radians(Degrees) ((Degrees)/180.0f * (float)M_PI)

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

		case WM_INPUT:
		{
			RAWINPUT Device;
			HRAWINPUT Mouse = (HRAWINPUT)lParam;
			UINT InputBufferSize = sizeof(Device);
			UINT BytesCopied = GetRawInputData(Mouse, RID_INPUT, &Device, &InputBufferSize, sizeof(Device.header));
			Assert(BytesCopied == InputBufferSize);
			float MouseSensitivity = 0.001f;
			Assert(Device.data.mouse.usFlags == MOUSE_MOVE_RELATIVE);
			LONG DeltaX = Device.data.mouse.lLastX;
			LONG DeltaY = Device.data.mouse.lLastY;
			camera* Camera = (camera*)GetWindowLongPtrW(Window, GWLP_USERDATA);
			Assert(Camera);
			Camera->Yaw -= DeltaX * MouseSensitivity;
			Camera->Pitch -= DeltaY * MouseSensitivity;
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
	RECT WindowRect = {0, 0, 800, 600};
	AdjustWindowRect(&WindowRect, WindowStyle, 0);
	int Width = WindowRect.right - WindowRect.left;
	int Height = WindowRect.bottom - WindowRect.top;
	HWND Result = CreateWindowExW(0, WindowClass.lpszClassName, L"LearnOpenGL", WindowStyle, CW_USEDEFAULT, CW_USEDEFAULT, Width, Height, 0, 0, Instance, 0);
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

float Cube[] =
{
	// front
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

	// left
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

	// bottom
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f,

	// top
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

	// right
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

	// back
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
};

vector3 CubePositions[] =
{
	{0.0f, 0.0f, 0.0f},
	{2.0f, 5.0f, -15.0f},
	{-1.5f, -2.2f, -2.5f},
	{-3.8f, -2.0f, -12.3f},
	{2.4f, -0.4f, -3.5f},
	{-1.7f, 3.0f, -7.5f},
	{1.3f, -2.0f, -2.5f},
	{1.5f, 2.0f, -2.5f},
	{1.5f, 0.2f, -1.5f},
	{-1.3f, 1.0f, -1.5f},
};

static void
LockCursor(HWND Window)
{
	RECT WindowRect;
	GetClientRect(Window, &WindowRect);
	int CursorX = (WindowRect.right + WindowRect.left)/2;
	int CursorY = (WindowRect.bottom + WindowRect.top)/2;
	SetCursorPos(CursorX, CursorY);
}

static void
ProcessWindowsMessages(void)
{
	MSG Message;
	while(PeekMessageW(&Message, 0, 0, 0, PM_REMOVE))
	{
		if(Message.message == WM_QUIT)
		{
			ExitProcess(0);
		}
		TranslateMessage(&Message);
		DispatchMessageW(&Message);
	}
}

static void
SetupInput(HWND Window)
{
	RAWINPUTDEVICE Mouse = {0};
	Mouse.usUsagePage = HID_USAGE_PAGE_GENERIC;
	Mouse.usUsage = HID_USAGE_GENERIC_MOUSE;
	//Mouse.dwFlags = RIDEV_CAPTUREMOUSE
	Mouse.dwFlags = RIDEV_INPUTSINK;
	Mouse.hwndTarget = Window;
	RegisterRawInputDevices(&Mouse, 1, sizeof(Mouse));
}

void WinMainCRTStartup()
{
	DisableDPIScaling();
	HWND Window = CreateOpenGLWindow();
	HDC WindowDC = GetDC(Window);
	SetOpenGLContext(Window);
	LoadOpenGLFunctions();
	ShowCursor(FALSE);
	SetupInput(Window);

	GLuint VertexArray;
	GLuint VertexBuffer;
	glGenVertexArrays(1, &VertexArray);
	glGenBuffers(1, &VertexBuffer);

	glBindVertexArray(VertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Cube), Cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Contents = GetFileContents("../awesomeface.png", &FileSize);
	Data = stbi_load_from_memory(Contents, FileSize, &Width, &Height, &NumChannels, 0);
	Assert(Data);
	VirtualFree(Contents, 0, MEM_RELEASE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(Data);
	glUniform1i(glGetUniformLocation(ShaderProgram, "Texture1"), 0);
	glUniform1i(glGetUniformLocation(ShaderProgram, "Texture2"), 1);
	RECT WindowRect;
	GetClientRect(Window, &WindowRect);
	int WindowWidth = WindowRect.right - WindowRect.left;
	int WindowHeight = WindowRect.bottom - WindowRect.top;
	matrix4 Perspective = Matrix4_Perspective(to_radians(45.0f), (float)WindowHeight/WindowWidth, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "Perspective"), 1, GL_FALSE, (float*)&Perspective);
	glEnable(GL_DEPTH_TEST);

	camera Camera = {0};
	Camera.Position = (vector3){0, 0, 3};
	Camera.Right = Vector3_UnitX();
	Camera.Up = Vector3_UnitY();
	Camera.Front = Vector3_UnitZ();
	SetWindowLongPtrW(Window, GWLP_USERDATA, (LONG_PTR)&Camera);
	float CameraSpeed = 10.0f;

	LARGE_INTEGER Frequency = {0};
	LARGE_INTEGER T1 = {0};
	LARGE_INTEGER T2 = {0};
	QueryPerformanceFrequency(&Frequency);

	for(;;)
	{
		ProcessWindowsMessages();
		LockCursor(Window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		QueryPerformanceCounter(&T2);
		float DeltaTime = (float)(T2.QuadPart - T1.QuadPart)/Frequency.QuadPart;
		float MoveStep = CameraSpeed * DeltaTime;
		if(GetAsyncKeyState('W') >> 15)
		{
			vector3 Backward = Camera_AxisZ(Camera);
			vector3 Step = Vector3_Scale(Backward, -MoveStep);
			Camera.Position.X += Step.X;
			Camera.Position.Z += Step.Z;
		}
		if(GetAsyncKeyState('S') >> 15)
		{
			vector3 Backward = Camera_AxisZ(Camera);
			vector3 Step = Vector3_Scale(Backward, MoveStep);
			Camera.Position.X += Step.X;
			Camera.Position.Z += Step.Z;
		}
		if(GetAsyncKeyState('A') >> 15)
		{
			vector3 Left = Camera_AxisX(Camera);
			vector3 Step = Vector3_Scale(Left, -MoveStep);
			Camera.Position = Vector3_Add(Camera.Position, Step);
		}
		if(GetAsyncKeyState('D') >> 15)
		{
			vector3 Left = Camera_AxisX(Camera);
			vector3 Step = Vector3_Scale(Left, MoveStep);
			Camera.Position = Vector3_Add(Camera.Position, Step);
		}
		matrix4 View = CameraView(&Camera);
		glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "View"), 1, GL_FALSE, (float*)&(View));

		for(int Index = 0; Index < 10; Index += 1)
		{
			float Angle = 20.0f * Index;
			matrix4 Model = Matrix4_RotateAround((vector3){1.0f, 0.3f, 0.5f}, Angle);
			matrix4 Translation = Matrix4_Translate(CubePositions[Index]);
			Model = Matrix4_MultiplyMatrix4(Translation, Model);
			glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "Model"), 1, GL_FALSE, (float*)&Model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		SwapBuffers(WindowDC);
		T1 = T2;
	}
}