#pragma once
#include <FreeImage.h>
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <iostream>
#include <string>

using namespace std;
class Texture
{
public:
	Texture();
	~Texture();

	unsigned int texInt;

	void Load(const char* path);
	void Update();
	void Delete();
};

