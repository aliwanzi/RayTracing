#include "./../Buffer/VertexArray.h"
#include "Render.h"

namespace SandTable 
{
	void Render::Init()
	{
		RenderCommand::Init();
	}

	void Render::Shutdown()
	{

	}

	void Render::SetBackGround(const glm::vec4& vec4BackGround)
	{
		RenderCommand::ClearColor(vec4BackGround);
	}

	void Render::ClearScreen()
	{
		RenderCommand::Clear();
	}

	void Render::WindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::Viewport(0, 0, width, height);
	}

	void Render::BeginScene()
	{

	}

	void Render::EndScene()
	{
	}

	void Render::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, 
		const glm::mat4& transform)
	{
		shader->Bind();

		vertexArray->Bind();
		RenderCommand::DrawElement(vertexArray);
		//RenderCommand::DrawVertexArray(vertexArray);
	}

}
