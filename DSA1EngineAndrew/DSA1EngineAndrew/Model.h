#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Texture.h"
using namespace std;
struct Vertex 
{
	glm::vec3 location;
	glm::vec2 uv;
	glm::vec3 normal;
};
struct VertInd
{
	unsigned int locInd, uvInd, normInd;
};
class Model
{
private:
	unsigned int vertCount;
	GLuint vertArr;
public:
	Model();
	~Model();

	bool Buffer(string objFile);
	void Render();
	void Bind();
};

