#pragma once
#include "Texture.h"

namespace SandTable 
{
	struct SparseTexture2DInfo
	{
		std::string Path;
		int Width;
		int Height;
		int PageX;
		int PageY;
		int Level;
	};

	class SparseTexture2D :public Texture
	{
	public:
		SparseTexture2D(std::shared_ptr<SparseTexture2DInfo> spSparseTexture2DInfo);
		virtual ~SparseTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual const std::string& GetPath() const override { return m_Path; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool IsLoaded() const override { return m_IsLoaded; }

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererID == other.GetRendererID();
		}

		void Commit(uint32_t uiPageX, uint32_t uiPageY, uint32_t uiLevel)  const;
		void Freed(uint32_t uiPageX, uint32_t uiPageY, uint32_t uiLevel) const;

	private:
		std::string m_Path;
		bool m_IsLoaded = false;
		int m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
		std::shared_ptr<unsigned char> m_spImageData;
	};
}
