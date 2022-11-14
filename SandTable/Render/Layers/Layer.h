#pragma once

#include "./../../Core/Common.h"
#include "./../../Event/Event.h"

namespace SandTable 
{
	class Layer
	{
	public:
		Layer(const std::string& sLayerName = "Layer");
		virtual ~Layer() = default;

		virtual void Attach() = 0;
		virtual void Detach() = 0;
		virtual void ExecuteEvent(Event& event) = 0;
		virtual void Execute();    //≥°æ∞ªÊ÷∆
		virtual void ExecuteImGui();  //ImGuiªÊ÷∆

		const std::string& GetName() const;

	protected:
		std::string m_sLayerName;
	};
}