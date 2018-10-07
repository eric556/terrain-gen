#pragma once
#include <gl\glew.h>
#include <iostream>

#define ASSERT(x) if(!(x)) __debugbreak();

#ifdef _DEBUG 
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall()) 
#else 
#define GLCall(x) x 
#endif

/// <summary>
/// Clear the GL error log
/// </summary>
static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

/// <summary>
/// Print the GL error log
/// </summary>
/// <returns></returns>
static bool GLLogCall()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL_Error] (" << error << ")\n";
		return false;
	}

	return true;
}