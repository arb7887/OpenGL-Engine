#version 430 

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 4) uniform mat4 worldView;
layout (location = 5) uniform mat4 modelWorld;

out vec2 TexCoord;
out float red;
out float green;
out vec3 Normal;
out vec3 FragPos;

void main()
{
   gl_Position = worldView * modelWorld * vec4(position,1);
   FragPos = vec3(modelWorld * vec4(position,1));
   red = (position.x +1) / 2;
   green = (position.y +1) / 2;
   TexCoord = uv;
   
   Normal = mat3(transpose(inverse(modelWorld))) * normal;
   //Normal = normal;
}