#version 430

layout(location = 3)uniform vec3 lightPos;
layout(location = 2)uniform float time;
layout(location = 6)uniform vec3 viewPos;

in vec2 TexCoord;
in float red;
in float green;
in vec3 Normal;
in vec3 FragPos;

vec3 objColor;
vec3 lightColor;

layout(location = 10)uniform sampler2D myTexture;

void main()
{
	lightColor = vec3(1.0f, 1.0f, 1.0f);
	
	//Ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;
	
	//Diffuse
	vec3 N = normalize(Normal);
	vec3 L = normalize(lightPos - FragPos);
	float diff = max(dot(N,L),0);
	vec3 diffuse = diff * lightColor;
	
	//Specular
	float specularStrength = 0.1f;
	vec3 V = normalize(viewPos - FragPos);
	vec3 R = reflect(-L, N);
	float spec = pow(max(dot(V, R), 0.0), 128);
	vec3 specular = specularStrength * spec * lightColor;
	
	//Texture
	vec4 texColor = texture(myTexture, TexCoord);
	
	float blue = (sin(time) + 1) / 2;
	//objColor = vec3(red,green,blue);
	objColor = vec3(1);
	
	vec3 result = (ambient + diffuse + specular) * objColor * vec3(texColor.x, texColor.y, texColor.z);
	gl_FragColor = vec4(result, 1);
	//gl_FragColor = vec4(TexCoord, 0, 1);
	//gl_FragColor = texColor;
}