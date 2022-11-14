#pragma once

#include "./../Render/Layers/Layer.h"
#include "./../Render/Shader/Shader.h"
#include "./../Render/Buffer/VertexArray.h"
#include "./../Render/Texture/2DTexture.h"

namespace SandTable
{
	class RenderLayer : public Layer
	{
	public:
		RenderLayer(const std::string& sLayerName = "RenderLayer");
		virtual ~RenderLayer();

		virtual void Attach() override;
		virtual void Detach() override;

		void ExecuteEvent(Event& e) override;
		void Execute() override;
		void ExecuteImGui() override;

	private:
		std::shared_ptr<ShaderLibrary> m_spShaderLibrary;
		std::shared_ptr<VertexArray> m_spVertexArray;
		std::shared_ptr<Texture2D> m_spTexture;
		std::shared_ptr<Shader> m_spShader;
		int m_iLevel;
	};
}