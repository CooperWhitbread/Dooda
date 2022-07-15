#pragma once

#include "Dooda/Core/Core.h"

namespace Dooda 
{

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind(UINT slot = 0) const = 0;

		virtual bool IsLoaded() const = 0;

	public: //Getters
		virtual UINT GetWidth() const = 0;
		virtual UINT GetHeight() const = 0;
		virtual UINT GetRendererID() const = 0;

	public: //Setters
		virtual void SetData(void* data, UINT size) = 0;

	public: //Operators
		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(UINT width, UINT height);
		static Ref<Texture2D> Create(const std::string& path);
	};

}
