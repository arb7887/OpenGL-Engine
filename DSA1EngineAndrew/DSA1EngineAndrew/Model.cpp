#include "Model.h"

Model::Model()
{
	//tex = Texture();
}


Model::~Model()
{
}

bool Model::Buffer(string objFile)
{
	//Step 1: Define Vertex Locations
	vector<glm::vec3> locs;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;
	vector<VertInd> vertInds;

	//Open the file for reading
	ifstream instream;
	instream.open(objFile);
	string line;

	//check to see if the file is open first
	if (instream.is_open())
	{
		while (getline(instream, line))
		{
			istringstream sstream(line);
			string label;
			sstream >> label;

			//Get Locations
			if (label == "v")
			{
				float one, two, three;
				sstream >> one >> two >> three;
				locs.push_back(glm::vec3(one, two, three));
			}

			//Get UVs
			else if (label == "vt")
			{
				float one, two;
				sstream >> one >> two;
				uvs.push_back(glm::vec2(one, two));
			}

			//Get Normals
			else if (label == "vn")
			{
				float one, two, three;
				sstream >> one >> two >> three;
				normals.push_back(glm::vec3(one, two, three));
			}

			//Get Indicies
			else if (label == "f")
			{
				//Do it 3 times
				for (int i = 0; i < 3; i++)
				{
					unsigned int one, two, three;
					char slash;
					sstream >> one >> slash >> two >> slash >> three;
					one--;
					two--;
					three--;
					VertInd vi;
					vi.locInd = one;
					vi.uvInd = two;
					vi.normInd = three;
					vertInds.push_back(vi);
				}
			}
		}

		//After there are no more lines, close the stream
		instream.close();
	}
	else
	{
		cout << "Error reading Object File" << endl;
	}

	//Step 2: Define a Series of Location indicies to "connect the dots"
	vertCount = vertInds.size();

	//Step 3: Iterate over the Location Vertices, filling the Vertex Buffer with non-unique locations
	vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
		vertBufData[i] = { locs[vertInds[i].locInd], uvs[vertInds[i].uvInd], normals[vertInds[i].normInd] };

	//Step 4: Declare a GLuint vertex Buffer
	GLuint vertBuf;

	//Step 5: Generating a Vertex Array and Buffer
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	//Step 6: Bind Vertex Array and Buffer
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	//Step 7: Upload the Buffer Data
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertex) * vertCount,
		&vertBufData[0],
		GL_STATIC_DRAW);

	//Step 8: Describe how data is packed in the Buffer
	glEnableVertexAttribArray(0);
	
	//position
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		0);

	//uv
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof(glm::vec3));

	//normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindVertexArray(0);
	return true;
}

void Model::Render()
{
	//Render
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);
}

void Model::Bind()
{
	glBindVertexArray(vertArr);
}
