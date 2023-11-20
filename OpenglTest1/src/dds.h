
#include <stdio.h>
#include <gl/glew.h>
#include  <glfw3.h>
#include <iostream>

bool GLCreateCubeTextureFromDDS(const char* file, bool srgb, GLuint* out)
{
	DDS_Image_Info info;
	GLuint texid = OpenGLContentManager().IDTexture(file);

	if (texid != 0) {
		printf("Pointer %s\n", file);
		*out = texid;

		return true;
	}

	if (!LoadFromDDS(file, &info)) {
		std::cout << "Error: Could not load texture!\n";
		return false;
	}

	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texid);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (info.MipLevels > 1)
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	else
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLsizei pow2s = Math::NextPow2(info.Width);
	GLsizei facesize;
	GLenum format = info.Format;

	if (info.Format == GLFMT_DXT1 || info.Format == GLFMT_DXT5) {
		// compressed
		GLsizei size;
		GLsizei offset = 0;

		if (srgb) {
			if (format == GLFMT_DXT1)
				format = GLFMT_DXT1_sRGB;
			else
				format = GLFMT_DXT5_sRGB;
		}

		for (int i = 0; i < 6; ++i) {
			for (uint32_t j = 0; j < info.MipLevels; ++j) {
				size = Math::Max(1, pow2s >> j);
				facesize = GetCompressedLevelSize(info.Width, info.Height, j, info.Format);

				glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, j, map_Format_Internal[format],
					size, size, 0, facesize, (char*)info.Data + offset);

				offset += facesize;
			}
		}
	}
	else {
		// uncompressed
		GLsizei size;
		GLsizei offset = 0;
		GLsizei bytes = 4;

		if (info.Format == GLFMT_A16B16G16R16F)
			bytes = 8;

		for (int i = 0; i < 6; ++i) {
			for (uint32_t j = 0; j < info.MipLevels; ++j) {
				size = Math::Max(1, pow2s >> j);
				facesize = size * size * bytes;

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, j, map_Format_Internal[info.Format], size, size, 0,
					map_Format_Format[info.Format], map_Format_Type[info.Format], (char*)info.Data + offset);

				offset += facesize;
			}
		}
	}

	if (info.Data)
		free(info.Data);

	GLenum err = glGetError();

	if (err != GL_NO_ERROR) {
		glDeleteTextures(1, &texid);
		texid = 0;

		std::cout << "Error: Could not create texture!\n";
	}
	else {
		std::cout << "Created cube texture " << info.Width << "x" << info.Height << "\n";
	}

	*out = texid;
	OpenGLContentManager().RegisterTexture(file, texid);

	return (texid != 0);
}