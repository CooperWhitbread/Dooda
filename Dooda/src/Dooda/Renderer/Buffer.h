#pragma once

namespace Dooda {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t S_ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		DD_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
	public:
		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(S_ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

	public: //Getters
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			DD_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}

	public: //Variables
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: d_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

	public: //Getters
		inline uint32_t GetStride() const { return d_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return d_Elements; }

	public: //Iterators
		std::vector<BufferElement>::iterator begin() { return d_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return d_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return d_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return d_Elements.end(); }

	private: //Private Variables
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			d_Stride = 0;
			for (auto& element : d_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				d_Stride += element.Size;
			}
		}

	private: //Variables
		std::vector<BufferElement> d_Elements;
		uint32_t d_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

	public: //Getters
		virtual const BufferLayout& GetLayout() const = 0;

	public: //Setters
		virtual void SetLayout(const BufferLayout& layout) = 0;

	public: // Static Functions
		static Ref<VertexBuffer> Create(float* verticies, uint32_t size); 
		
	};

	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

	public: //Getters
		virtual uint32_t GetCount() const = 0;

	public: // Static Functions
		static Ref<IndexBuffer> Create(uint32_t* indicies, uint32_t count);
	};

}