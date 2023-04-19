static HMODULE OpenGL;
static struct
{
	unsigned int Major;
	unsigned int Minor;
} OpenGLVersion;

static void
SetOpenGLContext(HWND Window)
{
	PIXELFORMATDESCRIPTOR PFD = {0};
	PFD.nSize = sizeof(PFD);
	PFD.nVersion = 1;
	PFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	PFD.iPixelType = PFD_TYPE_RGBA;
	PFD.cColorBits = 32;
	PFD.cDepthBits = 24;
	PFD.cStencilBits = 8;
	PFD.iLayerType = PFD_MAIN_PLANE;
	HDC DeviceContext = GetDC(Window);
	int PixelFormat = ChoosePixelFormat(DeviceContext, &PFD);
	SetPixelFormat(DeviceContext, PixelFormat, &PFD);
	DescribePixelFormat(DeviceContext, PixelFormat, sizeof(PFD), &PFD);
	HGLRC OpenGLContext = wglCreateContext(DeviceContext);
	Assert(OpenGLContext);
	wglMakeCurrent(DeviceContext, OpenGLContext);
}

static void*
QueryOpenGLFunction(char* FunctionName)
{
	intptr_t Function = (intptr_t)wglGetProcAddress(FunctionName);
	int InvalidPointer = ((Function == -1) || (Function < 0x4));
	if(InvalidPointer)
	{
		Function = (intptr_t)GetProcAddress(OpenGL, FunctionName);
	}
	void* Result = (void*)Function;
	return Result;
}

static void
LoadOpenGL_1_0(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(1, 0));
	QUERY_OPENGL_FUNCTION(glCullFace);
	QUERY_OPENGL_FUNCTION(glFrontFace);
	QUERY_OPENGL_FUNCTION(glHint);
	QUERY_OPENGL_FUNCTION(glLineWidth);
	QUERY_OPENGL_FUNCTION(glPointSize);
	QUERY_OPENGL_FUNCTION(glPolygonMode);
	QUERY_OPENGL_FUNCTION(glScissor);
	QUERY_OPENGL_FUNCTION(glTexParameterf);
	QUERY_OPENGL_FUNCTION(glTexParameterfv);
	QUERY_OPENGL_FUNCTION(glTexParameteri);
	QUERY_OPENGL_FUNCTION(glTexParameteriv);
	QUERY_OPENGL_FUNCTION(glTexImage1D);
	QUERY_OPENGL_FUNCTION(glTexImage2D);
	QUERY_OPENGL_FUNCTION(glDrawBuffer);
	QUERY_OPENGL_FUNCTION(glClear);
	QUERY_OPENGL_FUNCTION(glClearColor);
	QUERY_OPENGL_FUNCTION(glClearStencil);
	QUERY_OPENGL_FUNCTION(glClearDepth);
	QUERY_OPENGL_FUNCTION(glStencilMask);
	QUERY_OPENGL_FUNCTION(glColorMask);
	QUERY_OPENGL_FUNCTION(glDepthMask);
	QUERY_OPENGL_FUNCTION(glDisable);
	QUERY_OPENGL_FUNCTION(glEnable);
	QUERY_OPENGL_FUNCTION(glFinish);
	QUERY_OPENGL_FUNCTION(glFlush);
	QUERY_OPENGL_FUNCTION(glBlendFunc);
	QUERY_OPENGL_FUNCTION(glLogicOp);
	QUERY_OPENGL_FUNCTION(glStencilFunc);
	QUERY_OPENGL_FUNCTION(glStencilOp);
	QUERY_OPENGL_FUNCTION(glDepthFunc);
	QUERY_OPENGL_FUNCTION(glPixelStoref);
	QUERY_OPENGL_FUNCTION(glPixelStorei);
	QUERY_OPENGL_FUNCTION(glReadBuffer);
	QUERY_OPENGL_FUNCTION(glReadPixels);
	QUERY_OPENGL_FUNCTION(glGetBooleanv);
	QUERY_OPENGL_FUNCTION(glGetDoublev);
	QUERY_OPENGL_FUNCTION(glGetError);
	QUERY_OPENGL_FUNCTION(glGetFloatv);
	QUERY_OPENGL_FUNCTION(glGetIntegerv);
	QUERY_OPENGL_FUNCTION(glGetString);
	QUERY_OPENGL_FUNCTION(glGetTexImage);
	QUERY_OPENGL_FUNCTION(glGetTexParameterfv);
	QUERY_OPENGL_FUNCTION(glGetTexParameteriv);
	QUERY_OPENGL_FUNCTION(glGetTexLevelParameterfv);
	QUERY_OPENGL_FUNCTION(glGetTexLevelParameteriv);
	QUERY_OPENGL_FUNCTION(glIsEnabled);
	QUERY_OPENGL_FUNCTION(glDepthRange);
	QUERY_OPENGL_FUNCTION(glViewport);
}

static void
LoadOpenGL_1_1(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(1, 1));
	QUERY_OPENGL_FUNCTION(glDrawArrays);
	QUERY_OPENGL_FUNCTION(glDrawElements);
	QUERY_OPENGL_FUNCTION(glPolygonOffset);
	QUERY_OPENGL_FUNCTION(glCopyTexImage1D);
	QUERY_OPENGL_FUNCTION(glCopyTexImage2D);
	QUERY_OPENGL_FUNCTION(glCopyTexSubImage1D);
	QUERY_OPENGL_FUNCTION(glCopyTexSubImage2D);
	QUERY_OPENGL_FUNCTION(glTexSubImage1D);
	QUERY_OPENGL_FUNCTION(glTexSubImage2D);
	QUERY_OPENGL_FUNCTION(glBindTexture);
	QUERY_OPENGL_FUNCTION(glDeleteTextures);
	QUERY_OPENGL_FUNCTION(glGenTextures);
	QUERY_OPENGL_FUNCTION(glIsTexture);
}

static void
LoadOpenGL_1_2(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(1, 2));
	QUERY_OPENGL_FUNCTION(glDrawRangeElements);
	QUERY_OPENGL_FUNCTION(glTexImage3D);
	QUERY_OPENGL_FUNCTION(glTexSubImage3D);
	QUERY_OPENGL_FUNCTION(glCopyTexSubImage3D);
}

static void
LoadOpenGL_1_3(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(1, 3));
	QUERY_OPENGL_FUNCTION(glActiveTexture);
	QUERY_OPENGL_FUNCTION(glSampleCoverage);
	QUERY_OPENGL_FUNCTION(glCompressedTexImage3D);
	QUERY_OPENGL_FUNCTION(glCompressedTexImage2D);
	QUERY_OPENGL_FUNCTION(glCompressedTexImage1D);
	QUERY_OPENGL_FUNCTION(glCompressedTexSubImage3D);
	QUERY_OPENGL_FUNCTION(glCompressedTexSubImage2D);
	QUERY_OPENGL_FUNCTION(glCompressedTexSubImage1D);
	QUERY_OPENGL_FUNCTION(glGetCompressedTexImage);
}

static void
LoadOpenGL_1_4(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(1, 4));
	QUERY_OPENGL_FUNCTION(glBlendFuncSeparate);
	QUERY_OPENGL_FUNCTION(glMultiDrawArrays);
	QUERY_OPENGL_FUNCTION(glMultiDrawElements);
	QUERY_OPENGL_FUNCTION(glPointParameterf);
	QUERY_OPENGL_FUNCTION(glPointParameterfv);
	QUERY_OPENGL_FUNCTION(glPointParameteri);
	QUERY_OPENGL_FUNCTION(glPointParameteriv);
	QUERY_OPENGL_FUNCTION(glBlendColor);
	QUERY_OPENGL_FUNCTION(glBlendEquation);
}

static void
LoadOpenGL_1_5(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(1, 5));
	QUERY_OPENGL_FUNCTION(glGenQueries);
	QUERY_OPENGL_FUNCTION(glDeleteQueries);
	QUERY_OPENGL_FUNCTION(glIsQuery);
	QUERY_OPENGL_FUNCTION(glBeginQuery);
	QUERY_OPENGL_FUNCTION(glEndQuery);
	QUERY_OPENGL_FUNCTION(glGetQueryiv);
	QUERY_OPENGL_FUNCTION(glGetQueryObjectiv);
	QUERY_OPENGL_FUNCTION(glGetQueryObjectuiv);
	QUERY_OPENGL_FUNCTION(glBindBuffer);
	QUERY_OPENGL_FUNCTION(glDeleteBuffers);
	QUERY_OPENGL_FUNCTION(glGenBuffers);
	QUERY_OPENGL_FUNCTION(glIsBuffer);
	QUERY_OPENGL_FUNCTION(glBufferData);
	QUERY_OPENGL_FUNCTION(glBufferSubData);
	QUERY_OPENGL_FUNCTION(glGetBufferSubData);
	QUERY_OPENGL_FUNCTION(glMapBuffer);
	QUERY_OPENGL_FUNCTION(glUnmapBuffer);
	QUERY_OPENGL_FUNCTION(glGetBufferParameteriv);
	QUERY_OPENGL_FUNCTION(glGetBufferPointerv);
}

static void
LoadOpenGL_2_0(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(2, 0));
	QUERY_OPENGL_FUNCTION(glBlendEquationSeparate);
	QUERY_OPENGL_FUNCTION(glDrawBuffers);
	QUERY_OPENGL_FUNCTION(glStencilOpSeparate);
	QUERY_OPENGL_FUNCTION(glStencilFuncSeparate);
	QUERY_OPENGL_FUNCTION(glStencilMaskSeparate);
	QUERY_OPENGL_FUNCTION(glAttachShader);
	QUERY_OPENGL_FUNCTION(glBindAttribLocation);
	QUERY_OPENGL_FUNCTION(glCompileShader);
	QUERY_OPENGL_FUNCTION(glCreateProgram);
	QUERY_OPENGL_FUNCTION(glCreateShader);
	QUERY_OPENGL_FUNCTION(glDeleteProgram);
	QUERY_OPENGL_FUNCTION(glDeleteShader);
	QUERY_OPENGL_FUNCTION(glDetachShader);
	QUERY_OPENGL_FUNCTION(glDisableVertexAttribArray);
	QUERY_OPENGL_FUNCTION(glEnableVertexAttribArray);
	QUERY_OPENGL_FUNCTION(glGetActiveAttrib);
	QUERY_OPENGL_FUNCTION(glGetActiveUniform);
	QUERY_OPENGL_FUNCTION(glGetAttachedShaders);
	QUERY_OPENGL_FUNCTION(glGetAttribLocation);
	QUERY_OPENGL_FUNCTION(glGetProgramiv);
	QUERY_OPENGL_FUNCTION(glGetProgramInfoLog);
	QUERY_OPENGL_FUNCTION(glGetShaderiv);
	QUERY_OPENGL_FUNCTION(glGetShaderInfoLog);
	QUERY_OPENGL_FUNCTION(glGetShaderSource);
	QUERY_OPENGL_FUNCTION(glGetUniformLocation);
	QUERY_OPENGL_FUNCTION(glGetUniformfv);
	QUERY_OPENGL_FUNCTION(glGetUniformiv);
	QUERY_OPENGL_FUNCTION(glGetVertexAttribdv);
	QUERY_OPENGL_FUNCTION(glGetVertexAttribfv);
	QUERY_OPENGL_FUNCTION(glGetVertexAttribiv);
	QUERY_OPENGL_FUNCTION(glGetVertexAttribPointerv);
	QUERY_OPENGL_FUNCTION(glIsProgram);
	QUERY_OPENGL_FUNCTION(glIsShader);
	QUERY_OPENGL_FUNCTION(glLinkProgram);
	QUERY_OPENGL_FUNCTION(glShaderSource);
	QUERY_OPENGL_FUNCTION(glUseProgram);
	QUERY_OPENGL_FUNCTION(glUniform1f);
	QUERY_OPENGL_FUNCTION(glUniform2f);
	QUERY_OPENGL_FUNCTION(glUniform3f);
	QUERY_OPENGL_FUNCTION(glUniform4f);
	QUERY_OPENGL_FUNCTION(glUniform1i);
	QUERY_OPENGL_FUNCTION(glUniform2i);
	QUERY_OPENGL_FUNCTION(glUniform3i);
	QUERY_OPENGL_FUNCTION(glUniform4i);
	QUERY_OPENGL_FUNCTION(glUniform1fv);
	QUERY_OPENGL_FUNCTION(glUniform2fv);
	QUERY_OPENGL_FUNCTION(glUniform3fv);
	QUERY_OPENGL_FUNCTION(glUniform4fv);
	QUERY_OPENGL_FUNCTION(glUniform1iv);
	QUERY_OPENGL_FUNCTION(glUniform2iv);
	QUERY_OPENGL_FUNCTION(glUniform3iv);
	QUERY_OPENGL_FUNCTION(glUniform4iv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix2fv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix3fv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix4fv);
	QUERY_OPENGL_FUNCTION(glValidateProgram);
	QUERY_OPENGL_FUNCTION(glVertexAttrib1d);
	QUERY_OPENGL_FUNCTION(glVertexAttrib1dv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib1f);
	QUERY_OPENGL_FUNCTION(glVertexAttrib1fv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib1s);
	QUERY_OPENGL_FUNCTION(glVertexAttrib1sv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib2d);
	QUERY_OPENGL_FUNCTION(glVertexAttrib2dv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib2f);
	QUERY_OPENGL_FUNCTION(glVertexAttrib2fv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib2s);
	QUERY_OPENGL_FUNCTION(glVertexAttrib2sv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib3d);
	QUERY_OPENGL_FUNCTION(glVertexAttrib3dv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib3f);
	QUERY_OPENGL_FUNCTION(glVertexAttrib3fv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib3s);
	QUERY_OPENGL_FUNCTION(glVertexAttrib3sv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4Nbv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4Niv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4Nsv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4Nub);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4Nubv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4Nuiv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4Nusv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4bv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4d);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4dv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4f);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4fv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4iv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4s);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4sv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4ubv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4uiv);
	QUERY_OPENGL_FUNCTION(glVertexAttrib4usv);
	QUERY_OPENGL_FUNCTION(glVertexAttribPointer);
}

static void
LoadOpenGL_2_1(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(2, 1));
	QUERY_OPENGL_FUNCTION(glUniformMatrix2x3fv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix3x2fv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix2x4fv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix4x2fv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix3x4fv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix4x3fv);
}

static void
LoadOpenGL_3_0(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(3, 0));
	QUERY_OPENGL_FUNCTION(glColorMaski);
	QUERY_OPENGL_FUNCTION(glGetBooleani_v);
	QUERY_OPENGL_FUNCTION(glGetIntegeri_v);
	QUERY_OPENGL_FUNCTION(glEnablei);
	QUERY_OPENGL_FUNCTION(glDisablei);
	QUERY_OPENGL_FUNCTION(glIsEnabledi);
	QUERY_OPENGL_FUNCTION(glBeginTransformFeedback);
	QUERY_OPENGL_FUNCTION(glEndTransformFeedback);
	QUERY_OPENGL_FUNCTION(glBindBufferRange);
	QUERY_OPENGL_FUNCTION(glBindBufferBase);
	QUERY_OPENGL_FUNCTION(glTransformFeedbackVaryings);
	QUERY_OPENGL_FUNCTION(glGetTransformFeedbackVarying);
	QUERY_OPENGL_FUNCTION(glClampColor);
	QUERY_OPENGL_FUNCTION(glBeginConditionalRender);
	QUERY_OPENGL_FUNCTION(glEndConditionalRender);
	QUERY_OPENGL_FUNCTION(glVertexAttribIPointer);
	QUERY_OPENGL_FUNCTION(glGetVertexAttribIiv);
	QUERY_OPENGL_FUNCTION(glGetVertexAttribIuiv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI1i);
	QUERY_OPENGL_FUNCTION(glVertexAttribI2i);
	QUERY_OPENGL_FUNCTION(glVertexAttribI3i);
	QUERY_OPENGL_FUNCTION(glVertexAttribI4i);
	QUERY_OPENGL_FUNCTION(glVertexAttribI1ui);
	QUERY_OPENGL_FUNCTION(glVertexAttribI2ui);
	QUERY_OPENGL_FUNCTION(glVertexAttribI3ui);
	QUERY_OPENGL_FUNCTION(glVertexAttribI4ui);
	QUERY_OPENGL_FUNCTION(glVertexAttribI1iv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI2iv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI3iv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI4iv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI1uiv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI2uiv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI3uiv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI4uiv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI4bv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI4sv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI4ubv);
	QUERY_OPENGL_FUNCTION(glVertexAttribI4usv);
	QUERY_OPENGL_FUNCTION(glGetUniformuiv);
	QUERY_OPENGL_FUNCTION(glBindFragDataLocation);
	QUERY_OPENGL_FUNCTION(glGetFragDataLocation);
	QUERY_OPENGL_FUNCTION(glUniform1ui);
	QUERY_OPENGL_FUNCTION(glUniform2ui);
	QUERY_OPENGL_FUNCTION(glUniform3ui);
	QUERY_OPENGL_FUNCTION(glUniform4ui);
	QUERY_OPENGL_FUNCTION(glUniform1uiv);
	QUERY_OPENGL_FUNCTION(glUniform2uiv);
	QUERY_OPENGL_FUNCTION(glUniform3uiv);
	QUERY_OPENGL_FUNCTION(glUniform4uiv);
	QUERY_OPENGL_FUNCTION(glTexParameterIiv);
	QUERY_OPENGL_FUNCTION(glTexParameterIuiv);
	QUERY_OPENGL_FUNCTION(glGetTexParameterIiv);
	QUERY_OPENGL_FUNCTION(glGetTexParameterIuiv);
	QUERY_OPENGL_FUNCTION(glClearBufferiv);
	QUERY_OPENGL_FUNCTION(glClearBufferuiv);
	QUERY_OPENGL_FUNCTION(glClearBufferfv);
	QUERY_OPENGL_FUNCTION(glClearBufferfi);
	QUERY_OPENGL_FUNCTION(glGetStringi);
	QUERY_OPENGL_FUNCTION(glIsRenderbuffer);
	QUERY_OPENGL_FUNCTION(glBindRenderbuffer);
	QUERY_OPENGL_FUNCTION(glDeleteRenderbuffers);
	QUERY_OPENGL_FUNCTION(glGenRenderbuffers);
	QUERY_OPENGL_FUNCTION(glRenderbufferStorage);
	QUERY_OPENGL_FUNCTION(glGetRenderbufferParameteriv);
	QUERY_OPENGL_FUNCTION(glIsFramebuffer);
	QUERY_OPENGL_FUNCTION(glBindFramebuffer);
	QUERY_OPENGL_FUNCTION(glDeleteFramebuffers);
	QUERY_OPENGL_FUNCTION(glGenFramebuffers);
	QUERY_OPENGL_FUNCTION(glCheckFramebufferStatus);
	QUERY_OPENGL_FUNCTION(glFramebufferTexture1D);
	QUERY_OPENGL_FUNCTION(glFramebufferTexture2D);
	QUERY_OPENGL_FUNCTION(glFramebufferTexture3D);
	QUERY_OPENGL_FUNCTION(glFramebufferRenderbuffer);
	QUERY_OPENGL_FUNCTION(glGetFramebufferAttachmentParameteriv);
	QUERY_OPENGL_FUNCTION(glGenerateMipmap);
	QUERY_OPENGL_FUNCTION(glBlitFramebuffer);
	QUERY_OPENGL_FUNCTION(glRenderbufferStorageMultisample);
	QUERY_OPENGL_FUNCTION(glFramebufferTextureLayer);
	QUERY_OPENGL_FUNCTION(glMapBufferRange);
	QUERY_OPENGL_FUNCTION(glFlushMappedBufferRange);
	QUERY_OPENGL_FUNCTION(glBindVertexArray);
	QUERY_OPENGL_FUNCTION(glDeleteVertexArrays);
	QUERY_OPENGL_FUNCTION(glGenVertexArrays);
	QUERY_OPENGL_FUNCTION(glIsVertexArray);
}

static void
LoadOpenGL_3_1(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(3, 1));
	QUERY_OPENGL_FUNCTION(glDrawArraysInstanced);
	QUERY_OPENGL_FUNCTION(glDrawElementsInstanced);
	QUERY_OPENGL_FUNCTION(glTexBuffer);
	QUERY_OPENGL_FUNCTION(glPrimitiveRestartIndex);
	QUERY_OPENGL_FUNCTION(glCopyBufferSubData);
	QUERY_OPENGL_FUNCTION(glGetUniformIndices);
	QUERY_OPENGL_FUNCTION(glGetActiveUniformsiv);
	QUERY_OPENGL_FUNCTION(glGetActiveUniformName);
	QUERY_OPENGL_FUNCTION(glGetUniformBlockIndex);
	QUERY_OPENGL_FUNCTION(glGetActiveUniformBlockiv);
	QUERY_OPENGL_FUNCTION(glGetActiveUniformBlockName);
	QUERY_OPENGL_FUNCTION(glUniformBlockBinding);
	QUERY_OPENGL_FUNCTION(glBindBufferRange);
	QUERY_OPENGL_FUNCTION(glBindBufferBase);
	QUERY_OPENGL_FUNCTION(glGetIntegeri_v);
}

static void
LoadOpenGL_3_2(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(3, 2));
	QUERY_OPENGL_FUNCTION(glDrawElementsBaseVertex);
	QUERY_OPENGL_FUNCTION(glDrawRangeElementsBaseVertex);
	QUERY_OPENGL_FUNCTION(glDrawElementsInstancedBaseVertex);
	QUERY_OPENGL_FUNCTION(glMultiDrawElementsBaseVertex);
	QUERY_OPENGL_FUNCTION(glProvokingVertex);
	QUERY_OPENGL_FUNCTION(glFenceSync);
	QUERY_OPENGL_FUNCTION(glIsSync);
	QUERY_OPENGL_FUNCTION(glDeleteSync);
	QUERY_OPENGL_FUNCTION(glClientWaitSync);
	QUERY_OPENGL_FUNCTION(glWaitSync);
	QUERY_OPENGL_FUNCTION(glGetInteger64v);
	QUERY_OPENGL_FUNCTION(glGetSynciv);
	QUERY_OPENGL_FUNCTION(glGetInteger64i_v);
	QUERY_OPENGL_FUNCTION(glGetBufferParameteri64v);
	QUERY_OPENGL_FUNCTION(glFramebufferTexture);
	QUERY_OPENGL_FUNCTION(glTexImage2DMultisample);
	QUERY_OPENGL_FUNCTION(glTexImage3DMultisample);
	QUERY_OPENGL_FUNCTION(glGetMultisamplefv);
	QUERY_OPENGL_FUNCTION(glSampleMaski);
}

static void
LoadOpenGL_3_3(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(3, 3));
	QUERY_OPENGL_FUNCTION(glBindFragDataLocationIndexed);
	QUERY_OPENGL_FUNCTION(glGetFragDataIndex);
	QUERY_OPENGL_FUNCTION(glGenSamplers);
	QUERY_OPENGL_FUNCTION(glDeleteSamplers);
	QUERY_OPENGL_FUNCTION(glIsSampler);
	QUERY_OPENGL_FUNCTION(glBindSampler);
	QUERY_OPENGL_FUNCTION(glSamplerParameteri);
	QUERY_OPENGL_FUNCTION(glSamplerParameteriv);
	QUERY_OPENGL_FUNCTION(glSamplerParameterf);
	QUERY_OPENGL_FUNCTION(glSamplerParameterfv);
	QUERY_OPENGL_FUNCTION(glSamplerParameterIiv);
	QUERY_OPENGL_FUNCTION(glSamplerParameterIuiv);
	QUERY_OPENGL_FUNCTION(glGetSamplerParameteriv);
	QUERY_OPENGL_FUNCTION(glGetSamplerParameterIiv);
	QUERY_OPENGL_FUNCTION(glGetSamplerParameterfv);
	QUERY_OPENGL_FUNCTION(glGetSamplerParameterIuiv);
	QUERY_OPENGL_FUNCTION(glQueryCounter);
	QUERY_OPENGL_FUNCTION(glGetQueryObjecti64v);
	QUERY_OPENGL_FUNCTION(glGetQueryObjectui64v);
	QUERY_OPENGL_FUNCTION(glVertexAttribDivisor);
	QUERY_OPENGL_FUNCTION(glVertexAttribP1ui);
	QUERY_OPENGL_FUNCTION(glVertexAttribP1uiv);
	QUERY_OPENGL_FUNCTION(glVertexAttribP2ui);
	QUERY_OPENGL_FUNCTION(glVertexAttribP2uiv);
	QUERY_OPENGL_FUNCTION(glVertexAttribP3ui);
	QUERY_OPENGL_FUNCTION(glVertexAttribP3uiv);
	QUERY_OPENGL_FUNCTION(glVertexAttribP4ui);
	QUERY_OPENGL_FUNCTION(glVertexAttribP4uiv);
	QUERY_OPENGL_FUNCTION(glVertexP2ui);
	QUERY_OPENGL_FUNCTION(glVertexP2uiv);
	QUERY_OPENGL_FUNCTION(glVertexP3ui);
	QUERY_OPENGL_FUNCTION(glVertexP3uiv);
	QUERY_OPENGL_FUNCTION(glVertexP4ui);
	QUERY_OPENGL_FUNCTION(glVertexP4uiv);
	QUERY_OPENGL_FUNCTION(glTexCoordP1ui);
	QUERY_OPENGL_FUNCTION(glTexCoordP1uiv);
	QUERY_OPENGL_FUNCTION(glTexCoordP2ui);
	QUERY_OPENGL_FUNCTION(glTexCoordP2uiv);
	QUERY_OPENGL_FUNCTION(glTexCoordP3ui);
	QUERY_OPENGL_FUNCTION(glTexCoordP3uiv);
	QUERY_OPENGL_FUNCTION(glTexCoordP4ui);
	QUERY_OPENGL_FUNCTION(glTexCoordP4uiv);
	QUERY_OPENGL_FUNCTION(glMultiTexCoordP1ui);
	QUERY_OPENGL_FUNCTION(glMultiTexCoordP1uiv);
	QUERY_OPENGL_FUNCTION(glMultiTexCoordP2ui);
	QUERY_OPENGL_FUNCTION(glMultiTexCoordP2uiv);
	QUERY_OPENGL_FUNCTION(glMultiTexCoordP3ui);
	QUERY_OPENGL_FUNCTION(glMultiTexCoordP3uiv);
	QUERY_OPENGL_FUNCTION(glMultiTexCoordP4ui);
	QUERY_OPENGL_FUNCTION(glMultiTexCoordP4uiv);
	QUERY_OPENGL_FUNCTION(glNormalP3ui);
	QUERY_OPENGL_FUNCTION(glNormalP3uiv);
	QUERY_OPENGL_FUNCTION(glColorP3ui);
	QUERY_OPENGL_FUNCTION(glColorP3uiv);
	QUERY_OPENGL_FUNCTION(glColorP4ui);
	QUERY_OPENGL_FUNCTION(glColorP4uiv);
	QUERY_OPENGL_FUNCTION(glSecondaryColorP3ui);
	QUERY_OPENGL_FUNCTION(glSecondaryColorP3uiv);
}

static void
LoadOpenGL_4_0(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(4, 0));
	QUERY_OPENGL_FUNCTION(glMinSampleShading);
	QUERY_OPENGL_FUNCTION(glBlendEquationi);
	QUERY_OPENGL_FUNCTION(glBlendEquationSeparatei);
	QUERY_OPENGL_FUNCTION(glBlendFunci);
	QUERY_OPENGL_FUNCTION(glBlendFuncSeparatei);
	QUERY_OPENGL_FUNCTION(glDrawArraysIndirect);
	QUERY_OPENGL_FUNCTION(glDrawElementsIndirect);
	QUERY_OPENGL_FUNCTION(glUniform1d);
	QUERY_OPENGL_FUNCTION(glUniform2d);
	QUERY_OPENGL_FUNCTION(glUniform3d);
	QUERY_OPENGL_FUNCTION(glUniform4d);
	QUERY_OPENGL_FUNCTION(glUniform1dv);
	QUERY_OPENGL_FUNCTION(glUniform2dv);
	QUERY_OPENGL_FUNCTION(glUniform3dv);
	QUERY_OPENGL_FUNCTION(glUniform4dv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix2dv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix3dv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix4dv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix2x3dv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix2x4dv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix3x2dv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix3x4dv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix4x2dv);
	QUERY_OPENGL_FUNCTION(glUniformMatrix4x3dv);
	QUERY_OPENGL_FUNCTION(glGetUniformdv);
	QUERY_OPENGL_FUNCTION(glGetSubroutineUniformLocation);
	QUERY_OPENGL_FUNCTION(glGetSubroutineIndex);
	QUERY_OPENGL_FUNCTION(glGetActiveSubroutineUniformiv);
	QUERY_OPENGL_FUNCTION(glGetActiveSubroutineUniformName);
	QUERY_OPENGL_FUNCTION(glGetActiveSubroutineName);
	QUERY_OPENGL_FUNCTION(glUniformSubroutinesuiv);
	QUERY_OPENGL_FUNCTION(glGetUniformSubroutineuiv);
	QUERY_OPENGL_FUNCTION(glGetProgramStageiv);
	QUERY_OPENGL_FUNCTION(glPatchParameteri);
	QUERY_OPENGL_FUNCTION(glPatchParameterfv);
	QUERY_OPENGL_FUNCTION(glBindTransformFeedback);
	QUERY_OPENGL_FUNCTION(glDeleteTransformFeedbacks);
	QUERY_OPENGL_FUNCTION(glGenTransformFeedbacks);
	QUERY_OPENGL_FUNCTION(glIsTransformFeedback);
	QUERY_OPENGL_FUNCTION(glPauseTransformFeedback);
	QUERY_OPENGL_FUNCTION(glResumeTransformFeedback);
	QUERY_OPENGL_FUNCTION(glDrawTransformFeedback);
	QUERY_OPENGL_FUNCTION(glDrawTransformFeedbackStream);
	QUERY_OPENGL_FUNCTION(glBeginQueryIndexed);
	QUERY_OPENGL_FUNCTION(glEndQueryIndexed);
	QUERY_OPENGL_FUNCTION(glGetQueryIndexediv);
}

static void
LoadOpenGL_4_1(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(4, 1));
	QUERY_OPENGL_FUNCTION(glReleaseShaderCompiler);
	QUERY_OPENGL_FUNCTION(glShaderBinary);
	QUERY_OPENGL_FUNCTION(glGetShaderPrecisionFormat);
	QUERY_OPENGL_FUNCTION(glDepthRangef);
	QUERY_OPENGL_FUNCTION(glClearDepthf);
	QUERY_OPENGL_FUNCTION(glGetProgramBinary);
	QUERY_OPENGL_FUNCTION(glProgramBinary);
	QUERY_OPENGL_FUNCTION(glProgramParameteri);
	QUERY_OPENGL_FUNCTION(glUseProgramStages);
	QUERY_OPENGL_FUNCTION(glActiveShaderProgram);
	QUERY_OPENGL_FUNCTION(glCreateShaderProgramv);
	QUERY_OPENGL_FUNCTION(glBindProgramPipeline);
	QUERY_OPENGL_FUNCTION(glDeleteProgramPipelines);
	QUERY_OPENGL_FUNCTION(glGenProgramPipelines);
	QUERY_OPENGL_FUNCTION(glIsProgramPipeline);
	QUERY_OPENGL_FUNCTION(glGetProgramPipelineiv);
	QUERY_OPENGL_FUNCTION(glProgramParameteri);
	QUERY_OPENGL_FUNCTION(glProgramUniform1i);
	QUERY_OPENGL_FUNCTION(glProgramUniform1iv);
	QUERY_OPENGL_FUNCTION(glProgramUniform1f);
	QUERY_OPENGL_FUNCTION(glProgramUniform1fv);
	QUERY_OPENGL_FUNCTION(glProgramUniform1d);
	QUERY_OPENGL_FUNCTION(glProgramUniform1dv);
	QUERY_OPENGL_FUNCTION(glProgramUniform1ui);
	QUERY_OPENGL_FUNCTION(glProgramUniform1uiv);
	QUERY_OPENGL_FUNCTION(glProgramUniform2i);
	QUERY_OPENGL_FUNCTION(glProgramUniform2iv);
	QUERY_OPENGL_FUNCTION(glProgramUniform2f);
	QUERY_OPENGL_FUNCTION(glProgramUniform2fv);
	QUERY_OPENGL_FUNCTION(glProgramUniform2d);
	QUERY_OPENGL_FUNCTION(glProgramUniform2dv);
	QUERY_OPENGL_FUNCTION(glProgramUniform2ui);
	QUERY_OPENGL_FUNCTION(glProgramUniform2uiv);
	QUERY_OPENGL_FUNCTION(glProgramUniform3i);
	QUERY_OPENGL_FUNCTION(glProgramUniform3iv);
	QUERY_OPENGL_FUNCTION(glProgramUniform3f);
	QUERY_OPENGL_FUNCTION(glProgramUniform3fv);
	QUERY_OPENGL_FUNCTION(glProgramUniform3d);
	QUERY_OPENGL_FUNCTION(glProgramUniform3dv);
	QUERY_OPENGL_FUNCTION(glProgramUniform3ui);
	QUERY_OPENGL_FUNCTION(glProgramUniform3uiv);
	QUERY_OPENGL_FUNCTION(glProgramUniform4i);
	QUERY_OPENGL_FUNCTION(glProgramUniform4iv);
	QUERY_OPENGL_FUNCTION(glProgramUniform4f);
	QUERY_OPENGL_FUNCTION(glProgramUniform4fv);
	QUERY_OPENGL_FUNCTION(glProgramUniform4d);
	QUERY_OPENGL_FUNCTION(glProgramUniform4dv);
	QUERY_OPENGL_FUNCTION(glProgramUniform4ui);
	QUERY_OPENGL_FUNCTION(glProgramUniform4uiv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix2fv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix3fv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix4fv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix2dv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix3dv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix4dv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix2x3fv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix3x2fv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix2x4fv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix4x2fv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix3x4fv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix4x3fv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix2x3dv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix3x2dv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix2x4dv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix4x2dv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix3x4dv);
	QUERY_OPENGL_FUNCTION(glProgramUniformMatrix4x3dv);
	QUERY_OPENGL_FUNCTION(glValidateProgramPipeline);
	QUERY_OPENGL_FUNCTION(glGetProgramPipelineInfoLog);
	QUERY_OPENGL_FUNCTION(glVertexAttribL1d);
	QUERY_OPENGL_FUNCTION(glVertexAttribL2d);
	QUERY_OPENGL_FUNCTION(glVertexAttribL3d);
	QUERY_OPENGL_FUNCTION(glVertexAttribL4d);
	QUERY_OPENGL_FUNCTION(glVertexAttribL1dv);
	QUERY_OPENGL_FUNCTION(glVertexAttribL2dv);
	QUERY_OPENGL_FUNCTION(glVertexAttribL3dv);
	QUERY_OPENGL_FUNCTION(glVertexAttribL4dv);
	QUERY_OPENGL_FUNCTION(glVertexAttribLPointer);
	QUERY_OPENGL_FUNCTION(glGetVertexAttribLdv);
	QUERY_OPENGL_FUNCTION(glViewportArrayv);
	QUERY_OPENGL_FUNCTION(glViewportIndexedf);
	QUERY_OPENGL_FUNCTION(glViewportIndexedfv);
	QUERY_OPENGL_FUNCTION(glScissorArrayv);
	QUERY_OPENGL_FUNCTION(glScissorIndexed);
	QUERY_OPENGL_FUNCTION(glScissorIndexedv);
	QUERY_OPENGL_FUNCTION(glDepthRangeArrayv);
	QUERY_OPENGL_FUNCTION(glDepthRangeIndexed);
	QUERY_OPENGL_FUNCTION(glGetFloati_v);
	QUERY_OPENGL_FUNCTION(glGetDoublei_v);
}

static void
LoadOpenGL_4_2(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(4, 2));
	QUERY_OPENGL_FUNCTION(glDrawArraysInstancedBaseInstance);
	QUERY_OPENGL_FUNCTION(glDrawElementsInstancedBaseInstance);
	QUERY_OPENGL_FUNCTION(glDrawElementsInstancedBaseVertexBaseInstance);
	QUERY_OPENGL_FUNCTION(glGetInternalformativ);
	QUERY_OPENGL_FUNCTION(glGetActiveAtomicCounterBufferiv);
	QUERY_OPENGL_FUNCTION(glBindImageTexture);
	QUERY_OPENGL_FUNCTION(glMemoryBarrier);
	QUERY_OPENGL_FUNCTION(glTexStorage1D);
	QUERY_OPENGL_FUNCTION(glTexStorage2D);
	QUERY_OPENGL_FUNCTION(glTexStorage3D);
	QUERY_OPENGL_FUNCTION(glDrawTransformFeedbackInstanced);
	QUERY_OPENGL_FUNCTION(glDrawTransformFeedbackStreamInstanced);
}

static void
LoadOpenGL_4_3(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(4, 3));
	QUERY_OPENGL_FUNCTION(glClearBufferData);
	QUERY_OPENGL_FUNCTION(glClearBufferSubData);
	QUERY_OPENGL_FUNCTION(glDispatchCompute);
	QUERY_OPENGL_FUNCTION(glDispatchComputeIndirect);
	QUERY_OPENGL_FUNCTION(glCopyImageSubData);
	QUERY_OPENGL_FUNCTION(glFramebufferParameteri);
	QUERY_OPENGL_FUNCTION(glGetFramebufferParameteriv);
	QUERY_OPENGL_FUNCTION(glGetInternalformati64v);
	QUERY_OPENGL_FUNCTION(glInvalidateTexSubImage);
	QUERY_OPENGL_FUNCTION(glInvalidateTexImage);
	QUERY_OPENGL_FUNCTION(glInvalidateBufferSubData);
	QUERY_OPENGL_FUNCTION(glInvalidateBufferData);
	QUERY_OPENGL_FUNCTION(glInvalidateFramebuffer);
	QUERY_OPENGL_FUNCTION(glInvalidateSubFramebuffer);
	QUERY_OPENGL_FUNCTION(glMultiDrawArraysIndirect);
	QUERY_OPENGL_FUNCTION(glMultiDrawElementsIndirect);
	QUERY_OPENGL_FUNCTION(glGetProgramInterfaceiv);
	QUERY_OPENGL_FUNCTION(glGetProgramResourceIndex);
	QUERY_OPENGL_FUNCTION(glGetProgramResourceName);
	QUERY_OPENGL_FUNCTION(glGetProgramResourceiv);
	QUERY_OPENGL_FUNCTION(glGetProgramResourceLocation);
	QUERY_OPENGL_FUNCTION(glGetProgramResourceLocationIndex);
	QUERY_OPENGL_FUNCTION(glShaderStorageBlockBinding);
	QUERY_OPENGL_FUNCTION(glTexBufferRange);
	QUERY_OPENGL_FUNCTION(glTexStorage2DMultisample);
	QUERY_OPENGL_FUNCTION(glTexStorage3DMultisample);
	QUERY_OPENGL_FUNCTION(glTextureView);
	QUERY_OPENGL_FUNCTION(glBindVertexBuffer);
	QUERY_OPENGL_FUNCTION(glVertexAttribFormat);
	QUERY_OPENGL_FUNCTION(glVertexAttribIFormat);
	QUERY_OPENGL_FUNCTION(glVertexAttribLFormat);
	QUERY_OPENGL_FUNCTION(glVertexAttribBinding);
	QUERY_OPENGL_FUNCTION(glVertexBindingDivisor);
	QUERY_OPENGL_FUNCTION(glDebugMessageControl);
	QUERY_OPENGL_FUNCTION(glDebugMessageInsert);
	QUERY_OPENGL_FUNCTION(glDebugMessageCallback);
	QUERY_OPENGL_FUNCTION(glGetDebugMessageLog);
	QUERY_OPENGL_FUNCTION(glPushDebugGroup);
	QUERY_OPENGL_FUNCTION(glPopDebugGroup);
	QUERY_OPENGL_FUNCTION(glObjectLabel);
	QUERY_OPENGL_FUNCTION(glGetObjectLabel);
	QUERY_OPENGL_FUNCTION(glObjectPtrLabel);
	QUERY_OPENGL_FUNCTION(glGetObjectPtrLabel);
	QUERY_OPENGL_FUNCTION(glGetPointerv);
}

static void
LoadOpenGL_4_4(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(4, 4));
	QUERY_OPENGL_FUNCTION(glBufferStorage);
	QUERY_OPENGL_FUNCTION(glClearTexImage);
	QUERY_OPENGL_FUNCTION(glClearTexSubImage);
	QUERY_OPENGL_FUNCTION(glBindBuffersBase);
	QUERY_OPENGL_FUNCTION(glBindBuffersRange);
	QUERY_OPENGL_FUNCTION(glBindTextures);
	QUERY_OPENGL_FUNCTION(glBindSamplers);
	QUERY_OPENGL_FUNCTION(glBindImageTextures);
	QUERY_OPENGL_FUNCTION(glBindVertexBuffers);
}

static void
LoadOpenGL_4_5(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(4, 5));
	QUERY_OPENGL_FUNCTION(glClipControl);
	QUERY_OPENGL_FUNCTION(glCreateTransformFeedbacks);
	QUERY_OPENGL_FUNCTION(glTransformFeedbackBufferBase);
	QUERY_OPENGL_FUNCTION(glTransformFeedbackBufferRange);
	QUERY_OPENGL_FUNCTION(glGetTransformFeedbackiv);
	QUERY_OPENGL_FUNCTION(glGetTransformFeedbacki_v);
	QUERY_OPENGL_FUNCTION(glGetTransformFeedbacki64_v);
	QUERY_OPENGL_FUNCTION(glCreateBuffers);
	QUERY_OPENGL_FUNCTION(glNamedBufferStorage);
	QUERY_OPENGL_FUNCTION(glNamedBufferData);
	QUERY_OPENGL_FUNCTION(glNamedBufferSubData);
	QUERY_OPENGL_FUNCTION(glCopyNamedBufferSubData);
	QUERY_OPENGL_FUNCTION(glClearNamedBufferData);
	QUERY_OPENGL_FUNCTION(glClearNamedBufferSubData);
	QUERY_OPENGL_FUNCTION(glMapNamedBuffer);
	QUERY_OPENGL_FUNCTION(glMapNamedBufferRange);
	QUERY_OPENGL_FUNCTION(glUnmapNamedBuffer);
	QUERY_OPENGL_FUNCTION(glFlushMappedNamedBufferRange);
	QUERY_OPENGL_FUNCTION(glGetNamedBufferParameteriv);
	QUERY_OPENGL_FUNCTION(glGetNamedBufferParameteri64v);
	QUERY_OPENGL_FUNCTION(glGetNamedBufferPointerv);
	QUERY_OPENGL_FUNCTION(glGetNamedBufferSubData);
	QUERY_OPENGL_FUNCTION(glCreateFramebuffers);
	QUERY_OPENGL_FUNCTION(glNamedFramebufferRenderbuffer);
	QUERY_OPENGL_FUNCTION(glNamedFramebufferParameteri);
	QUERY_OPENGL_FUNCTION(glNamedFramebufferTexture);
	QUERY_OPENGL_FUNCTION(glNamedFramebufferTextureLayer);
	QUERY_OPENGL_FUNCTION(glNamedFramebufferDrawBuffer);
	QUERY_OPENGL_FUNCTION(glNamedFramebufferDrawBuffers);
	QUERY_OPENGL_FUNCTION(glNamedFramebufferReadBuffer);
	QUERY_OPENGL_FUNCTION(glInvalidateNamedFramebufferData);
	QUERY_OPENGL_FUNCTION(glInvalidateNamedFramebufferSubData);
	QUERY_OPENGL_FUNCTION(glClearNamedFramebufferiv);
	QUERY_OPENGL_FUNCTION(glClearNamedFramebufferuiv);
	QUERY_OPENGL_FUNCTION(glClearNamedFramebufferfv);
	QUERY_OPENGL_FUNCTION(glClearNamedFramebufferfi);
	QUERY_OPENGL_FUNCTION(glBlitNamedFramebuffer);
	QUERY_OPENGL_FUNCTION(glCheckNamedFramebufferStatus);
	QUERY_OPENGL_FUNCTION(glGetNamedFramebufferParameteriv);
	QUERY_OPENGL_FUNCTION(glGetNamedFramebufferAttachmentParameteriv);;
	QUERY_OPENGL_FUNCTION(glCreateRenderbuffers);
	QUERY_OPENGL_FUNCTION(glNamedRenderbufferStorage);
	QUERY_OPENGL_FUNCTION(glNamedRenderbufferStorageMultisample);
	QUERY_OPENGL_FUNCTION(glGetNamedRenderbufferParameteriv);
	QUERY_OPENGL_FUNCTION(glCreateTextures);
	QUERY_OPENGL_FUNCTION(glTextureBuffer);
	QUERY_OPENGL_FUNCTION(glTextureBufferRange);
	QUERY_OPENGL_FUNCTION(glTextureStorage1D);
	QUERY_OPENGL_FUNCTION(glTextureStorage2D);
	QUERY_OPENGL_FUNCTION(glTextureStorage3D);
	QUERY_OPENGL_FUNCTION(glTextureStorage2DMultisample);
	QUERY_OPENGL_FUNCTION(glTextureStorage3DMultisample);
	QUERY_OPENGL_FUNCTION(glTextureSubImage1D);
	QUERY_OPENGL_FUNCTION(glTextureSubImage2D);
	QUERY_OPENGL_FUNCTION(glTextureSubImage3D);
	QUERY_OPENGL_FUNCTION(glCompressedTextureSubImage1D);
	QUERY_OPENGL_FUNCTION(glCompressedTextureSubImage2D);
	QUERY_OPENGL_FUNCTION(glCompressedTextureSubImage3D);
	QUERY_OPENGL_FUNCTION(glCopyTextureSubImage1D);
	QUERY_OPENGL_FUNCTION(glCopyTextureSubImage2D);
	QUERY_OPENGL_FUNCTION(glCopyTextureSubImage3D);
	QUERY_OPENGL_FUNCTION(glTextureParameterf);
	QUERY_OPENGL_FUNCTION(glTextureParameterfv);
	QUERY_OPENGL_FUNCTION(glTextureParameteri);
	QUERY_OPENGL_FUNCTION(glTextureParameterIiv);
	QUERY_OPENGL_FUNCTION(glTextureParameterIuiv);
	QUERY_OPENGL_FUNCTION(glTextureParameteriv);
	QUERY_OPENGL_FUNCTION(glGenerateTextureMipmap);
	QUERY_OPENGL_FUNCTION(glBindTextureUnit);
	QUERY_OPENGL_FUNCTION(glGetTextureImage);
	QUERY_OPENGL_FUNCTION(glGetCompressedTextureImage);
	QUERY_OPENGL_FUNCTION(glGetTextureLevelParameterfv);
	QUERY_OPENGL_FUNCTION(glGetTextureLevelParameteriv);
	QUERY_OPENGL_FUNCTION(glGetTextureParameterfv);
	QUERY_OPENGL_FUNCTION(glGetTextureParameterIiv);
	QUERY_OPENGL_FUNCTION(glGetTextureParameterIuiv);
	QUERY_OPENGL_FUNCTION(glGetTextureParameteriv);
	QUERY_OPENGL_FUNCTION(glCreateVertexArrays);
	QUERY_OPENGL_FUNCTION(glDisableVertexArrayAttrib);
	QUERY_OPENGL_FUNCTION(glEnableVertexArrayAttrib);
	QUERY_OPENGL_FUNCTION(glVertexArrayElementBuffer);
	QUERY_OPENGL_FUNCTION(glVertexArrayVertexBuffer);
	QUERY_OPENGL_FUNCTION(glVertexArrayVertexBuffers);
	QUERY_OPENGL_FUNCTION(glVertexArrayAttribBinding);
	QUERY_OPENGL_FUNCTION(glVertexArrayAttribFormat);
	QUERY_OPENGL_FUNCTION(glVertexArrayAttribIFormat);
	QUERY_OPENGL_FUNCTION(glVertexArrayAttribLFormat);
	QUERY_OPENGL_FUNCTION(glVertexArrayBindingDivisor);
	QUERY_OPENGL_FUNCTION(glGetVertexArrayiv);
	QUERY_OPENGL_FUNCTION(glGetVertexArrayIndexediv);
	QUERY_OPENGL_FUNCTION(glGetVertexArrayIndexed64iv);
	QUERY_OPENGL_FUNCTION(glCreateSamplers);
	QUERY_OPENGL_FUNCTION(glCreateProgramPipelines);
	QUERY_OPENGL_FUNCTION(glCreateQueries);
	QUERY_OPENGL_FUNCTION(glGetQueryBufferObjecti64v);
	QUERY_OPENGL_FUNCTION(glGetQueryBufferObjectiv);
	QUERY_OPENGL_FUNCTION(glGetQueryBufferObjectui64v);
	QUERY_OPENGL_FUNCTION(glGetQueryBufferObjectuiv);
	QUERY_OPENGL_FUNCTION(glMemoryBarrierByRegion);
	QUERY_OPENGL_FUNCTION(glGetTextureSubImage);
	QUERY_OPENGL_FUNCTION(glGetCompressedTextureSubImage);
	QUERY_OPENGL_FUNCTION(glGetGraphicsResetStatus);
	QUERY_OPENGL_FUNCTION(glGetnCompressedTexImage);
	QUERY_OPENGL_FUNCTION(glGetnTexImage);
	QUERY_OPENGL_FUNCTION(glGetnUniformdv);
	QUERY_OPENGL_FUNCTION(glGetnUniformfv);
	QUERY_OPENGL_FUNCTION(glGetnUniformiv);
	QUERY_OPENGL_FUNCTION(glGetnUniformuiv);
	QUERY_OPENGL_FUNCTION(glReadnPixels);
	QUERY_OPENGL_FUNCTION(glGetnMapdv);
	QUERY_OPENGL_FUNCTION(glGetnMapfv);
	QUERY_OPENGL_FUNCTION(glGetnMapiv);
	QUERY_OPENGL_FUNCTION(glGetnPixelMapfv);
	QUERY_OPENGL_FUNCTION(glGetnPixelMapuiv);
	QUERY_OPENGL_FUNCTION(glGetnPixelMapusv);
	QUERY_OPENGL_FUNCTION(glGetnPolygonStipple);
	QUERY_OPENGL_FUNCTION(glGetnColorTable);
	QUERY_OPENGL_FUNCTION(glGetnConvolutionFilter);
	QUERY_OPENGL_FUNCTION(glGetnSeparableFilter);
	QUERY_OPENGL_FUNCTION(glGetnHistogram);
	QUERY_OPENGL_FUNCTION(glGetnMinmax);
	QUERY_OPENGL_FUNCTION(glTextureBarrier);
}

static void
LoadOpenGL_4_6(void)
{
	return_if(OPENGL_VERSION_IS_BELOW(4, 6));
	QUERY_OPENGL_FUNCTION(glSpecializeShader);
	QUERY_OPENGL_FUNCTION(glMultiDrawArraysIndirectCount);
	QUERY_OPENGL_FUNCTION(glMultiDrawElementsIndirectCount);
	QUERY_OPENGL_FUNCTION(glPolygonOffsetClamp);
}

static void
LoadOpenGLFunctions(void)
{
	OpenGL = LoadLibraryA("opengl32.dll");
	QUERY_OPENGL_FUNCTION(glGetIntegerv);
	Assert(glGetIntegerv);
	glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion.Major);
	glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion.Minor);
	LoadOpenGL_1_0();
	LoadOpenGL_1_1();
	LoadOpenGL_1_2();
	LoadOpenGL_1_3();
	LoadOpenGL_1_4();
	LoadOpenGL_1_5();
	LoadOpenGL_2_0();
	LoadOpenGL_2_1();
	LoadOpenGL_3_0();
	LoadOpenGL_3_1();
	LoadOpenGL_3_2();
	LoadOpenGL_3_3();
	LoadOpenGL_4_0();
	LoadOpenGL_4_1();
	LoadOpenGL_4_2();
	LoadOpenGL_4_3();
	LoadOpenGL_4_4();
	LoadOpenGL_4_5();
	LoadOpenGL_4_6();
	// TODO: extensions
}