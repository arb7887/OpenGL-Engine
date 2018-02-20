#pragma once
#include <string>
#include "Model.h"
#include "Texture.h"

using namespace std;
using namespace glm;
struct Rigidbody
{
	vec3 velocity;
	vec3 acceleration;
	vec3 direction;
	float mass;
};
struct Transform
{
	vec3 location;
	vec3 rotation;
	vec3 size;
	mat4 objWorldMatrix;
	Rigidbody rigidbody;
};
enum ColliderType { Colliderless, AABB, Sphere };
class Object
{
private:
	char* texFilename;
	string modelFilename;
	Model model;
	Texture texture;
public:
	string tag;
	Transform transform;
	ColliderType cType;
	Object();
	Object(string mFilename, char* tFilename, string objtag, ColliderType collider);
	virtual ~Object();

	void Load();
	void Render(float deltaTime);
	void Update(float deltaTime);
	bool CollidesWith(const Object* other);
	void ApplyForce(vec3 force);
	void ApplyFriction(float coeff);
	void Delete();
};

