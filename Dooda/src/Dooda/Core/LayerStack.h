#pragma once

#include "Dooda/Core/Layer.h"

namespace Dooda
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

	public: //Iterators
		std::vector<Layer*>::iterator begin() { return d_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return d_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return d_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return d_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return d_Layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return d_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return d_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return d_Layers.rend(); }

	private: //Variables
		std::vector<Layer*> d_Layers;
		unsigned 
			d_LayerInsertIndex = 0;
	};
}