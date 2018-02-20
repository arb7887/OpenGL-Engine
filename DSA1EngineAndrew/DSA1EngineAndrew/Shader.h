#pragma once
#include <FreeImage.h>
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
class Shader
{
public:
	GLuint program, vprogram, fprogram;
	string filenamev = "shaders/vShader.glsl";
	string filenamef = "shaders/fShader.glsl";
	Shader();
	~Shader();

	bool load();
	bool compile(GLenum shaderType);
	void use();
	void unload();
};

