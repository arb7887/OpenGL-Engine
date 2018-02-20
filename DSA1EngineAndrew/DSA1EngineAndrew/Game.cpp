#include <iostream>
#include <vector>
#include <fstream> //file io

#include <FreeImage.h>
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

//#include "Engine.h"
//#include "Myobj.h"
#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
//Declare Assets

Shader shader;
vec3 lightPos(0, 5.0f, 0);
vec2 tableBounds(4.25f, -2.10f);
Object balls[16];
//Object tableBounds[12];
void CheckCollisions()
{
	//Check each balls' collision against every other ball
	for (int i = 0; i < 16; i++)
	{
		for (int j = 16; j > 0; j--)
		{
			if (j > i)
			{
				if (balls[i].CollidesWith(&balls[j]))
				{
					//Calculate momentum transfer on collision

					vec3 normal = normalize(balls[i].transform.location - balls[j].transform.location); //find the normal vectors between the two balls

					//Set objects' locations to prevent sticking
					float distance = length(balls[i].transform.location - balls[j].transform.location);
					float radiiSum = balls[i].transform.size.x + balls[j].transform.size.x;
					float shift = (distance - radiiSum)/2;
					vec3 shifti = shift * -normal;
					vec3 shiftj = shift * normal;
					balls[i].transform.location = balls[i].transform.location + shifti;
					balls[j].transform.location = balls[j].transform.location + shiftj;

					vec3 vi = balls[i].transform.rigidbody.velocity;
					vec3 vj = balls[j].transform.rigidbody.velocity;
					
					vec3 vni = dot(vi, normal) * normal; //find the normal components of each velocity
					vec3 vnj = dot(vj, -normal) * -normal;
					vec3 vti = vni - vi; //find the tangent components of each velocity
					vec3 vtj = vnj - vj;
					vi = vti + vnj; //find the new velocity in the new direction
					vj = vtj + vni;
					balls[i].transform.rigidbody.velocity = -vi;//set the new velocities
					balls[j].transform.rigidbody.velocity = vj;
				}
			}
		}
	}
}
int main() {

	//Engine.Start();
	//Initialize GLFW
	if (glfwInit() == GL_FALSE)
		return -1;

	//Create a windowed mode window.
	GLFWwindow* GLFWwindowPtr =
		glfwCreateWindow(800, 600, "Andrew Baron DSA1 Engine", NULL, NULL);

	//Make it the currently active window, or quit.
	if (GLFWwindowPtr != nullptr)
		glfwMakeContextCurrent(GLFWwindowPtr);
	else
	{
		glfwTerminate();
		return -1;
	}

	//Initialize GLEW or quit
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}

	
	//Engage Wire-frame rendering
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Object table = Object("models/ttable2.obj", "textures/grey.png", "Table", Colliderless);
	//Object CueGuide = Object("models/box.obj", "textures/2.png", "CueGuide", Colliderless);
	table.Load();
	//CueGuide.Load();

	//Pool Balls
	balls[0] = Object("models/sphere.obj", "textures/white.png", "Cue", Sphere);
	balls[1] = Object("models/sphere.obj", "textures/1.png", "1", Sphere);
	balls[2] = Object("models/sphere.obj", "textures/2.png", "2", Sphere);
	balls[3] = Object("models/sphere.obj", "textures/3.png", "3", Sphere);
	balls[4] = Object("models/sphere.obj", "textures/4.png", "4", Sphere);
	balls[5] = Object("models/sphere.obj", "textures/5.png", "5", Sphere);
	balls[6] = Object("models/sphere.obj", "textures/6.png", "6", Sphere);
	balls[7] = Object("models/sphere.obj", "textures/7.png", "7", Sphere);
	balls[8] = Object("models/sphere.obj", "textures/8.png", "8", Sphere);
	balls[9] = Object("models/sphere.obj", "textures/9.png", "9", Sphere);
	balls[10] = Object("models/sphere.obj", "textures/10.png", "10", Sphere);
	balls[11] = Object("models/sphere.obj", "textures/11.png", "11", Sphere);
	balls[12] = Object("models/sphere.obj", "textures/12.png", "12", Sphere);
	balls[13] = Object("models/sphere.obj", "textures/13.png", "13", Sphere);
	balls[14] = Object("models/sphere.obj", "textures/14.png", "14", Sphere);
	balls[15] = Object("models/sphere.obj", "textures/15.png", "15", Sphere);
	for (int i = 0; i < 16; i++)
	{
		balls[i].Load();
	}

	//Scaling
	for (int i = 0; i < 16; i++)
	{
		balls[i].transform.size = vec3(.1, .1, .1);
	}
	table.transform.size = vec3(3, 3, 3);
	//CueGuide.transform.size = vec3(.2, .005, .005);

	//positioning
	table.transform.location = vec3(0, 0, 0);
	balls[0].transform.location = vec3(2.5, .08, 0);
	//CueGuide.transform.location = balls[0].transform.location - vec3(CueGuide.transform.size.x / 2, 0, 0);
	balls[1].transform.location = vec3(-2, .08, 0);
	balls[2].transform.location = vec3(-2.175, .08, .11);
	balls[3].transform.location = vec3(-2.175, .08, -.11);
	balls[4].transform.location = vec3(-2.35, .08, .22);
	balls[5].transform.location = vec3(-2.35, .08, -.22);
	balls[6].transform.location = vec3(-2.525, .08, .11);
	balls[7].transform.location = vec3(-2.525, .08, -.11);
	balls[8].transform.location = vec3(-2.35, .08, 0);
	balls[9].transform.location = vec3(-2.525, .08, .33);
	balls[10].transform.location = vec3(-2.525, .08, -.33);
	balls[11].transform.location = vec3(-2.7, .08, 0);
	balls[12].transform.location = vec3(-2.7, .08, .22);
	balls[13].transform.location = vec3(-2.7, .08, -.22);
	balls[14].transform.location = vec3(-2.7, .08, .44);
	balls[15].transform.location = vec3(-2.7, .08, -.44);


	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	bool shaderIsLoaded = shader.load();
	if (shaderIsLoaded) shader.use();

	//upload light position information
	glUniform3f(3, lightPos.x, lightPos.y, lightPos.z);

	//Camera
	Camera camera = Camera();

	//time fields
	float frame0 = (float)glfwGetTime();
	float frame1 = 0;
	float deltaTime = 0;

	//game loop
	while (!glfwGetKey(GLFWwindowPtr, GLFW_KEY_ESCAPE))
	{
		//clear the canvas
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Time
		frame1 = (float)glfwGetTime(); //current time
		deltaTime = frame1 - frame0;
		frame0 = frame1;

		//Apply Forces before calling Render
		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_LEFT))
			balls[0].ApplyForce(vec3(-10, 0, 0));
		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_RIGHT))
			balls[0].ApplyForce(vec3(10, 0, 0));
		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_UP))
			balls[0].ApplyForce(vec3(0, 0, -10));
		if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_DOWN))
			balls[0].ApplyForce(vec3(0, 0, 10));

		CheckCollisions();
		//Object Rendering
		for (int i = 0; i < 16; i++)
		{
			//bounce within the bounds of the table
			if (balls[i].transform.location.x > tableBounds.x || balls[i].transform.location.x < -tableBounds.x)
			{
				balls[i].transform.rigidbody.velocity.x = -balls[i].transform.rigidbody.velocity.x;
			}
			if (balls[i].transform.location.z > -tableBounds.y || balls[i].transform.location.z < tableBounds.y)
			{
				balls[i].transform.rigidbody.velocity.z = -balls[i].transform.rigidbody.velocity.z;
			}
			balls[i].Render(deltaTime);
		}
		//CueGuide.transform.location = balls[0].transform.location + (balls[0].transform.rigidbody.direction + (CueGuide.transform.size.x / 2));
		//CueGuide.transform.rotation = balls[0].transform.rotation;
		//CueGuide.Render(deltaTime);
		table.Render(deltaTime);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Camera functions
		//camera.fpsControls(GLFWwindowPtr, deltaTime);
		camera.Update();

		//swap buffers
		glfwSwapBuffers(GLFWwindowPtr);
		glfwPollEvents();
	}

	//Delete Texture after game loop
	table.Delete();
	for (int i = 0; i < 16; i++) balls[i].Delete();
	glfwTerminate();
	return 0;
}
