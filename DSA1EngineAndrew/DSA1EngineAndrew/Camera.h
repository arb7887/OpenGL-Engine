#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>

class Camera
{
private:
	//world view matrix
	glm::mat4 worldView;

	//lookat matrix
	glm::vec3 camLocation = { 0,4,6 };
	glm::vec3 camRotation = { -.52,0,0 };
	glm::mat3 rotationMatrix = (glm::mat3)glm::yawPitchRoll(camRotation.y, camRotation.x, camRotation.z);
	glm::vec3 eye = camLocation;
	glm::vec3 center = eye + rotationMatrix * glm::vec3(0, 0, -1);
	glm::vec3 up = rotationMatrix * glm::vec3(0, 1, 0);
	glm::mat4 lookAtMatrix = glm::lookAt(eye, center, up);
	
	//velocity 
	glm::vec3 velocity;
	
	//perspective projection
	float zoom = 1.0f;
	int width = 800;
	int height = 600;
	float fov = 0.4 * 3.14 / zoom;
	float aspect = (float)width / (float)height;
	float zNear = 0.1f;
	float zFar = 1000.0f;
	glm::mat4 perspectiveMatrix = glm::perspective(fov, aspect, zNear, zFar);

public:
	Camera();
	virtual ~Camera();
	void Upload();
	void Update();
	void fpsControls(GLFWwindow * window, float &dt);
};

