#pragma once
#include "ddpch.h"

#include <glm/glm.hpp>

namespace Dooda 
{

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

	public: //Getters
		virtual const std::string& GetName() const = 0;

	public: //Setters
		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, UINT count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

	public: //Static Functions
		static Ref<Shader> SD_Create(const std::string& filepath);
		static Ref<Shader> SD_Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);

		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		bool Exists(const std::string& name) const;

	public: //Getters
		Ref<Shader> Get(const std::string& name);

	private: //Variables
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}
