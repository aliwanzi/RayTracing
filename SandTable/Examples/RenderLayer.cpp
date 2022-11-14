#include "RenderLayer.h"
#include "./../Render/Command/Render.h"
namespace SandTable
{
	RenderLayer::RenderLayer(const std::string& sLayerName)
		: Layer(sLayerName), m_iLevel(0)
	{
		//VertexArray
		m_spVertexArray = std::make_shared<VertexArray>();

		//VertexBuffer
		float vertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		auto spVertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		};
		spVertexBuffer->SetLayout(layout);

		//IndexBuffer
		uint32_t indices[6] = { 0, 1, 2, 2,3,0 };
		auto spIndexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));


		m_spVertexArray->AddVertexBuffer(spVertexBuffer);
		m_spVertexArray->SetIndexBuffer(spIndexBuffer);

		//Shader
		m_spShaderLibrary = std::make_shared<ShaderLibrary>();
		m_spShader = m_spShaderLibrary->AddShader("Texture", "./../resource/shaders/Texture.glsl");

		//Texture
		m_spTexture = std::make_shared<Texture2D>("./../resource/textures/awesomeface.png");
		m_spShader->Bind();
		m_spShader->SetInt("texture_diffuse1", 0);
	}

	RenderLayer::~RenderLayer()
	{

	}

	void RenderLayer::Attach()
	{

	}

	void RenderLayer::Detach()
	{

	}

	void RenderLayer::ExecuteEvent(Event& e)
	{
	}

	void RenderLayer::Execute()
	{
		// Render
		Render::ClearScreen();
		Render::SetBackGround({ 0.2f, 0.3f, 0.3f, 1.0f });
		m_spShader->Bind();
		m_spShader->SetInt("Level", m_iLevel);
		m_spTexture->Bind();
		Render::Submit(m_spShader, m_spVertexArray);
	}

	void RenderLayer::ExecuteImGui()
	{
		bool bShowImgui(true);
		ImGui::ShowDemoWindow(&bShowImgui);
	}
}