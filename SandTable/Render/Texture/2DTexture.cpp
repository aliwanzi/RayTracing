
#include "2DTexture.h"

namespace SandTable 
{
	Texture2D::Texture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_DataFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_DataFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
	}

	Texture2D::Texture2D(const std::string& path)
		: m_Path(path)
	{
		glGenTextures(1, &m_RendererID);

		int iComponent(0);
		stbi_set_flip_vertically_on_load(1);
		unsigned char* pImageData = stbi_load(path.c_str(), &m_Width, &m_Height, &iComponent, 0);
		if (pImageData != nullptr)
		{
			GLenum eFormat(GL_RED);
			switch (iComponent)
			{
			case 1:
			{
				eFormat = GL_RED;
				break;
			}
			case 3:
			{
				eFormat = GL_RGB;
				break;
			}
			case 4:
			{
				eFormat = GL_RGBA;
				break;
			}
			default:
				break;
			}

			glBindTexture(GL_TEXTURE_2D, m_RendererID);
			glTexImage2D(GL_TEXTURE_2D, 0, eFormat, m_Width, m_Height, 0, eFormat, GL_UNSIGNED_BYTE, pImageData);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, eFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, eFormat == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(pImageData);
		}
		else
		{
			LOG_DEV_ERROR("Texture failed to load at path:{0}", path);
			stbi_image_free(pImageData);
		}
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::Bind(uint32_t slot /*= 0*/) const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
}
