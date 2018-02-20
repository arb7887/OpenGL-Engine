#include "Object.h"
#include <iostream>

using namespace std;
Object::Object()
{
	tag = "default";
	modelFilename = "models/box.obj";
	texFilename = "textures/TestTexture.png";
	cType = Colliderless;
	transform = Transform();
	transform.location = vec3(0);
	transform.rotation = vec3(0);
	transform.size = vec3(1);
	transform.rigidbody.velocity = vec3(0, 0, 0);
	transform.rigidbody.acceleration = vec3(0, 0, 0);
	transform.rigidbody.direction = vec3(0, 0, 0);
	transform.rigidbody.mass = 1.0f;
}

Object::Object(string mFilename, char* tFilename, string objTag, ColliderType collider)
{
	modelFilename = mFilename;
	texFilename = tFilename;
	tag = objTag;
	cType = collider;
	transform = Transform();
	transform.location = vec3(0);
	transform.rotation = vec3(0);
	transform.size = vec3(1);
	transform.rigidbody.velocity = vec3(0, 0, 0);
	transform.rigidbody.acceleration = vec3(0, 0, 0);
	transform.rigidbody.direction = vec3(0, 0, 0);
	transform.rigidbody.mass = 1.0f;
}

Object::~Object()
{
}

void Object::Load()
{
	model.Buffer(modelFilename);
	texture.Load(texFilename);
}

void Object::Update(float deltaTime)
{	
	ApplyFriction(1.5f);
	transform.rigidbody.velocity += transform.rigidbody.acceleration * deltaTime; //update velocity by acceleration
	transform.location += transform.rigidbody.velocity * deltaTime; //apply velocity to location

	if (transform.rigidbody.velocity != vec3(0, 0, 0))
	{
		transform.rigidbody.direction = normalize(transform.rigidbody.velocity); //update the direction vector
	}

	mat4 transmat = translate(transform.location);
	mat4 rotmat = yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);
	mat4 scalemat = scale(transform.size);

	transform.objWorldMatrix = transmat*rotmat*scalemat;

	transform.rigidbody.acceleration = vec3(0, 0, 0); //reset acceleration every frame.
}

void Object::Render(float deltaTime)
{
	//Rendering
	Update(deltaTime);
	model.Bind();
	texture.Update();
	glUniformMatrix4fv(5, 1, GL_FALSE, &transform.objWorldMatrix[0][0]);
	model.Render();
	//cout << "Rendering " << tag << endl;
}

bool Object::CollidesWith(const Object* other)
{
	if (other->cType == Colliderless)
	{
		return false;
	}
	if (cType == Sphere && other->cType == Sphere)
	{
		float z = transform.location.z - other->transform.location.z;
		float y = transform.location.y - other->transform.location.y;
		float x = transform.location.x - other->transform.location.x;
		float distance = pow(z, 2.0) + pow(x, 2.0) + pow(y, 2.0);
		distance = sqrt(distance);
		float radiiSum = transform.size.x + other->transform.size.x;
		if (distance > radiiSum)
		{
			return false;
		}
	}
	if (cType == AABB && other->cType == AABB)
	{
		float xDistance = transform.location.x - other->transform.location.x;
		float yDistance = transform.location.y - other->transform.location.y;
		float zDistance = transform.location.z - other->transform.location.z;
		float xSum = transform.size.x + other->transform.size.x;
		float ySum = transform.size.y + other->transform.size.y;
		float zSum = transform.size.z + other->transform.size.z;
		if (abs(xDistance) > xSum)
		{
			return false;
		}
		if (abs(yDistance) > ySum)
		{
			return false;
		}
		if (abs(zDistance) > zSum)
		{
			return false;
		}
	}
	if ((cType == AABB && other->cType == Sphere) || (cType == Sphere && other->cType == AABB))
	{

	}
	return true;
}

void Object::ApplyForce(vec3 force)
{
	transform.rigidbody.acceleration += force / transform.rigidbody.mass;
}

void Object::ApplyFriction(float coeff)
{
	vec3 friction = transform.rigidbody.velocity * -1.0f;
	normalize(friction);
	friction = friction * coeff;
	transform.rigidbody.acceleration += friction;
}

void Object::Delete()
{
	texture.Delete();
}
