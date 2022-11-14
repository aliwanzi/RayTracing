#pragma once
#include "./../../Core/Common.h"
#include "./../Shader/Shader.h"
#include "RenderCommand.h"

namespace SandTable 
{
	class Render
	{
	public:
		static void Init();
		static void Shutdown();
		
		static void SetBackGround(const glm::vec4& vec4BackGround);
		static void ClearScreen();
		static void WindowResize(uint32_t width, uint32_t height);

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray,
			const glm::mat4& transform = glm::mat4(1.0f));
	};
}
