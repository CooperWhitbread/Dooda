#include "ddpch.h"
#include "LayerStack.h"

namespace Dooda
{

	LayerStack::~LayerStack()
	{
		for (Layer* layer : d_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		d_Layers.emplace(d_Layers.begin() + d_LayerInsertIndex, layer);
		d_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		d_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(d_Layers.begin(), d_Layers.begin() + d_LayerInsertIndex, layer);
		if (it != d_Layers.begin() + d_LayerInsertIndex)
		{
			layer->OnDetach();
			d_Layers.erase(it);
			d_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(d_Layers.begin() + d_LayerInsertIndex, d_Layers.end(), overlay);
		if (it != d_Layers.end())
		{
			overlay->OnDetach();
			d_Layers.erase(it);
		}
	}
}