static GLuint
CreateOpenGLShader(char* Source, GLenum Type)
{
	HANDLE File = CreateFileA(Source, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	Assert(File != INVALID_HANDLE_VALUE);
	DWORD FileSize = GetFileSize(File, 0);
	char* String = VirtualAlloc(0, FileSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	DWORD BytesRead = 0;
	ReadFile(File, String, FileSize, &BytesRead, 0);
	Assert(BytesRead == FileSize);
	GLuint ShaderID = glCreateShader(Type);
	glShaderSource(ShaderID, 1, &String, 0);
	glCompileShader(ShaderID);
	GLint Status = 0;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Status);
	if(Status == GL_FALSE)
	{
		GLint LogLength = 0;
		glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &LogLength);
		char* ErrorLog = VirtualAlloc(0, LogLength, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		glGetShaderInfoLog(ShaderID, LogLength, 0, ErrorLog);
		MessageBoxA(0, ErrorLog, "Shader Error Log", MB_OK);
		VirtualFree(ErrorLog, 0, MEM_RELEASE);
	}
	VirtualFree(String, 0, MEM_RELEASE);
	return ShaderID;
}

static GLuint
CreateOpenGLProgram(GLuint VertexShader, GLuint FragmentShader)
{
	GLuint Program = glCreateProgram();
	glAttachShader(Program, VertexShader);
	glAttachShader(Program, FragmentShader);
	glLinkProgram(Program);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
	GLint Status = 0;
	glGetProgramiv(Program, GL_LINK_STATUS, &Status);
	if(&Status == GL_FALSE)
	{
		GLint LogLength = 0;
		glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &LogLength);
		char* ErrorLog = VirtualAlloc(0, LogLength, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		glGetProgramInfoLog(Program, sizeof(ErrorLog), 0, ErrorLog);
		MessageBoxA(0, ErrorLog, "Shader Error Log", MB_OK);
		VirtualFree(ErrorLog, 0, MEM_RELEASE);
	}
	return Program;
}
