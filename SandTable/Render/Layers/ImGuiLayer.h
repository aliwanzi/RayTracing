#pragma once

#include "Layer.h"
#include "./../../Event/Event.h"

namespace SandTable
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void Attach() override;
		virtual void Detach() override;
		virtual void ExecuteEvent(Event& event) override;

		void Begin();
		void End();
	};

}
