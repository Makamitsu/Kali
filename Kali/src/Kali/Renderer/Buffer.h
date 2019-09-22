#pragma once


namespace Kali {
	
	enum class ShaderDataType : uint8_t
	{
		None = 0,
		Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	constexpr uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return sizeof(float);
		case ShaderDataType::Float2:	return sizeof(float) * 2;
		case ShaderDataType::Float3:	return sizeof(float) * 3;
		case ShaderDataType::Float4:	return sizeof(float) * 4;
		case ShaderDataType::Mat3:		return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4:		return sizeof(float) * 4 * 4;
		case ShaderDataType::Int:		return sizeof(uint32_t);
		case ShaderDataType::Int2:		return sizeof(uint32_t) * 2;
		case ShaderDataType::Int3:		return sizeof(uint32_t) * 3;
		case ShaderDataType::Int4:		return sizeof(uint32_t) * 4;
		case ShaderDataType::Bool:		return sizeof(bool);
		}

		KL_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	struct BufferElement
	{
		BufferElement() = default;

		std::string Name;
		ShaderDataType Type;

		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement(ShaderDataType pType, const std::string& pName, bool pNormalized = false) :
			Name(pName), Type(pType), Size(ShaderDataTypeSize(pType)), Offset(0), Normalized(pNormalized)
		{}

		[[nodiscard]] uint32_t GetComponentCount() const
		{
			switch(Type)
			{
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
			}

			KL_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}

	};


	class BufferLayout
	{
	public:
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elements):
			m_Elements(elements)
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for(auto&& element: m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		[[nodiscard]] const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		auto begin() { return m_Elements.begin(); }
		auto end() { return m_Elements.end(); }
		uint32_t GetStride() const { return m_Stride; }
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0 ;
		virtual void Unbind() const  = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() = 0;

		static VertexBuffer* Create(float* vertices, size_t size);
	};



	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const  = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};


}
