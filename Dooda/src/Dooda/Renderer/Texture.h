#pragma once

#include "Dooda/Core/Core.h"

namespace Dooda {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind(uint32_t slot = 0) const = 0;

	public: //Getters
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

	public: //Setters
		virtual void SetData(void* data, uint32_t size) = 0;

	public: //Operators
		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
	};

}