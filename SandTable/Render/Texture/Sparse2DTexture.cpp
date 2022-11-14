#include "Sparse2DTexture.h"

namespace SandTable 
{
	SparseTexture2D::SparseTexture2D(std::shared_ptr<SparseTexture2DInfo> spSparseTexture2DInfo):
		m_Width(spSparseTexture2DInfo->Width),m_Height(spSparseTexture2DInfo->Height),m_Path(spSparseTexture2DInfo->Path),
		m_DataFormat(GL_RGBA)
	{
		GLint glMax2DTextureSize;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMax2DTextureSize);

		GLint gl2DNumPageSizes;
		glGetInternalformativ(GL_TEXTURE_2D, GL_RGBA8, GL_NUM_VIRTUAL_PAGE_SIZES_ARB, sizeof(GLuint), &gl2DNumPageSizes);
		GLint gl2DPageSizeX[10], gl2DPageSizeY[10], gl2DPageSizeZ[10];
		glGetInternalformativ(GL_TEXTURE_2D, GL_RGBA8, GL_VIRTUAL_PAGE_SIZE_X_ARB, 1, gl2DPageSizeX);
		glGetInternalformativ(GL_TEXTURE_2D, GL_RGBA8, GL_VIRTUAL_PAGE_SIZE_Y_ARB, 1, gl2DPageSizeY);
		glGetInternalformativ(GL_TEXTURE_2D, GL_RGBA8, GL_VIRTUAL_PAGE_SIZE_Z_ARB, 1, gl2DPageSizeZ);


		GLint glMax3DTextureSize;
		glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &glMax3DTextureSize);

		GLint gl3DNumPageSizes;
		glGetInternalformativ(GL_TEXTURE_3D, GL_RGBA8, GL_NUM_VIRTUAL_PAGE_SIZES_ARB, sizeof(GLuint), &gl3DNumPageSizes);
		GLint gl3DPageSizeX[10], gl3DPageSizeY[10], gl3DPageSizeZ[10];
		glGetInternalformativ(GL_TEXTURE_3D, GL_RGBA8, GL_VIRTUAL_PAGE_SIZE_X_ARB, 1, gl3DPageSizeX);
		glGetInternalformativ(GL_TEXTURE_3D, GL_RGBA8, GL_VIRTUAL_PAGE_SIZE_Y_ARB, 1, gl3DPageSizeY);
		glGetInternalformativ(GL_TEXTURE_3D, GL_RGBA8, GL_VIRTUAL_PAGE_SIZE_Z_ARB, 1, gl3DPageSizeZ);

		size_t iTumorSize = spSparseTexture2DInfo->Width * spSparseTexture2DInfo->Height * 4;
		m_spImageData = std::shared_ptr<unsigned char>(new unsigned char[iTumorSize], std::default_delete<unsigned char[]>());
		auto pMemory = reinterpret_cast<char*>(m_spImageData.get());
		std::ifstream in(spSparseTexture2DInfo->Path, std::ios::in | std::ios::binary);
		if (!in.is_open())
		{
			LOG_DEV_ERROR("Texture failed to load at path:{0}", spSparseTexture2DInfo->Path);
			return;
		}
		in.read(pMemory, iTumorSize);
		in.close();

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SPARSE_ARB, GL_TRUE);
		glTexStorage2D(GL_TEXTURE_2D, spSparseTexture2DInfo->Level, GL_RGBA8,
			spSparseTexture2DInfo->PageX * m_Width, spSparseTexture2DInfo->PageY * m_Height);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	SparseTexture2D::~SparseTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void SparseTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void SparseTexture2D::Bind(uint32_t slot /*= 0*/) const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void SparseTexture2D::Commit(uint32_t uiPageX, uint32_t uiPageY, uint32_t uiLevel) const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexPageCommitmentARB(GL_TEXTURE_2D,
			uiLevel,
			uiPageX * m_Width, uiPageY * m_Height, 0,
			m_Width, m_Height, 1,
			GL_TRUE);
		glTexSubImage2D(GL_TEXTURE_2D,
			uiLevel,
			uiPageX * m_Width, uiPageY * m_Height,
			m_Width, m_Height,
			m_DataFormat, GL_UNSIGNED_BYTE,
			m_spImageData.get());
	}

	void SparseTexture2D::Freed(uint32_t uiPageX, uint32_t uiPageY, uint32_t uiLevel) const
	{
		glTexPageCommitmentARB(GL_TEXTURE_2D,
			uiLevel,
			uiPageX * m_Width, uiPageY * m_Height, 0,
			m_Width, m_Height, 1,
			GL_FALSE);
	}
}
