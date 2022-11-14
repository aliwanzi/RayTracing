#pragma once

#include "../../Core/Common.h"
#include "./../Buffer/VertexArray.h"

namespace SandTable 
{
	class RenderCommand
	{
	public:
		static void Init();

		static void Viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		static void ClearColor(const glm::vec4& color);

		static void Clear();

		static void DrawElement(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0);

		static void DrawVertexArray(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0);
	};

}
