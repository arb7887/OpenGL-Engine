#include "Camera.h"

Camera::Camera()
{
	//set world view to empty matrix
	worldView = glm::mat4();
}

Camera::~Camera()
{
}

void Camera::Upload()
{
	glUniformMatrix4fv(4, 1, GL_FALSE, &worldView[0][0]);
	glUniform3f(6, camLocation.x, camLocation.y, camLocation.z);
}

void Camera::Update()
{
	//updates rotation and position each frame
	rotationMatrix = (glm::mat3)glm::yawPitchRoll(camRotation.y, camRotation.x, camRotation.z);
	eye = camLocation;
	center = eye + rotationMatrix * glm::vec3(0, 0, -1);
	up = rotationMatrix * glm::vec3(0, 1, 0);
	lookAtMatrix = glm::lookAt(eye, center, up);
	
	worldView = perspectiveMatrix * lookAtMatrix;

	//upload matrix
	Upload();
}

//method for movement/looking with mouse and arrowkeys
void Camera::fpsControls(GLFWwindow * window, float & dt)
{
	//rotation using mouse movement
	float sens = .0005f;
	int w = 800, h = 600;
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	glfwGetWindowSize(window, &width, &height);

	camRotation.y -= sens * (x - width *.5f);
	camRotation.x -= sens * (y - height *.5f);
	camRotation.x = glm::clamp(camRotation.x, -.5f * 3.1415f, .5f * 3.1415f);
	glfwSetCursorPos(window, w*.5f, h*.5f);

	//movement using arrowkeys
	glm::vec3 cameraDirection;

	if (glfwGetKey(window, GLFW_KEY_A))
		cameraDirection.x -= 1;
	if (glfwGetKey(window, GLFW_KEY_D))
		cameraDirection.x += 1;
	if (glfwGetKey(window, GLFW_KEY_W))
		cameraDirection.z -= 1;
	if (glfwGetKey(window, GLFW_KEY_S))
		cameraDirection.z += 1;
	if (glfwGetKey(window, GLFW_KEY_SPACE))
		cameraDirection.y += 1;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		cameraDirection.y -= 1;
	float speed = 1.5f;
	if (cameraDirection != glm::vec3())
		cameraDirection = glm::normalize(cameraDirection);

	//sets velocity
	velocity = rotationMatrix * cameraDirection * speed;

	//updates the location and eye
	camLocation += velocity * dt;
	eye = camLocation;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
