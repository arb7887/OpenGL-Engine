#include "Texture.h"



Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::Load(const char* path)
{
	//Load texture using FreeImage
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(path, 0), path);
	if (image == nullptr)
	{
		cout << "The texture failed to load." << endl;
	}

	FIBITMAP* image32bit = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image);

	//Generate and Bind a new texture;
	glGenTextures(1, &texInt);
	glBindTexture(GL_TEXTURE_2D, texInt);

	//Upload Texture Bytes
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_SRGB_ALPHA,
		FreeImage_GetWidth(image32bit),
		FreeImage_GetHeight(image32bit),
		0,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(image32bit));

	//Set min filter to linear instead of mipmap linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//Clear the texture from RAM
	FreeImage_Unload(image32bit);

	//Unbind the texture when finished
	glBindTexture(GL_TEXTURE_2D, 0);
}

//Bind Texture while drawing it
void Texture::Update()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texInt);
}

//Delete textures when finished with them
void Texture::Delete()
{
	glDeleteTextures(1, &texInt);
}
