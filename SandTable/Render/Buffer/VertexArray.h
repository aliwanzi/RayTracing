#pragma once
#include "Buffer.h"
#include "./../../Core/Common.h"

namespace SandTable 
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers();
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer();
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};

}
