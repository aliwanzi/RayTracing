#include "Layer.h"

namespace SandTable
{
	Layer::Layer(const std::string& sLayerName)
		: m_sLayerName(sLayerName)
	{
	}
	
	void Layer::Execute()
	{
	}

	void Layer::ExecuteImGui()
	{
	}

	const std::string& Layer::GetName() const
	{
		return m_sLayerName;
	}
}