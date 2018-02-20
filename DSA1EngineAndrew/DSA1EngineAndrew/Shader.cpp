#include "Shader.h"


Shader::Shader()
{
}


Shader::~Shader()
{
}

bool Shader::load()
{
	bool fbool = compile(GL_FRAGMENT_SHADER);
	bool vbool = compile(GL_VERTEX_SHADER);
	if (!fbool || !vbool) // if either shader didnt compile, return false
	{
		return false;
	}
	program = glCreateProgram();
	glAttachShader(program, vprogram);
	glAttachShader(program, fprogram);
	glLinkProgram(program);
	GLint results;
	glGetProgramiv(program, GL_LINK_STATUS, &results);
	if (results != 0) return true;
	else
	{
		GLint loglength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &loglength);
		GLchar* log = new char[loglength];
		glGetProgramInfoLog(program, loglength, 0, log);
		glDeleteProgram(program);
		delete[] log;
		return false;
	}
	return false;
}

bool Shader::compile(GLenum shaderType)
{
	//reading text in
	ifstream instream;
	if (shaderType == GL_VERTEX_SHADER)
	{
		instream.open(filenamev, ios::binary);
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		instream.open(filenamef, ios::binary);
	}
	if (!instream.is_open())
	{
		cout << "There was an error opening the shader file." << endl;
		return 0;
	}
	instream.seekg(0, ios::end);
	int length = instream.tellg();
	instream.seekg(0, ios::beg);

	char* text = new char[length + 1];
	text[length] = '\0';
	instream.read(text, length);
	instream.close();

	//Compiling Shaders

	//if Vertex
	if (shaderType == GL_VERTEX_SHADER)
	{
		vprogram = glCreateShader(shaderType);
		glShaderSource(vprogram, 1, &text, 0);
		glCompileShader(vprogram);
		delete[] text;

		GLint results;
		glGetShaderiv(vprogram, GL_COMPILE_STATUS, &results);
		if(results != 0) return true;
		else
		{
			GLint loglength;
			glGetShaderiv(vprogram, GL_INFO_LOG_LENGTH, &loglength);
			GLchar* log = new GLchar[loglength];
			glGetShaderInfoLog(vprogram, loglength, 0, &log[0]);
			cout << log << endl;
			glDeleteShader(vprogram);
			delete[] log;
			return false;
		}
	}

	//if Fragment
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		fprogram = glCreateShader(shaderType);
		glShaderSource(fprogram, 1, &text, 0);
		glCompileShader(fprogram);

		delete[] text;
		GLint results;
		glGetShaderiv(fprogram, GL_COMPILE_STATUS, &results);
		if (results != 0) return true;
		else
		{
			GLint loglength;
			glGetShaderiv(fprogram, GL_INFO_LOG_LENGTH, &loglength);
			GLchar* log = new GLchar[loglength];
			glGetShaderInfoLog(fprogram, loglength, 0, &log[0]);
			cout << log << endl;
			glDeleteShader(fprogram);
			delete[] log;
			return false;
		}
	}
	
	return false;
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::unload()
{
	glDeleteProgram(program);
	glDeleteShader(vprogram);
	glDeleteShader(fprogram);
	program = 0;
	vprogram = 0;
	fprogram = 0;
}
