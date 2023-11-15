/** \bufferLayout.h */
#pragma once

#include "shaderDataType.h"
#include <vector>

namespace Engine
{
	/**
	\class BufferElement
	A class which holds data about a single element in a buffer layout
	*/
	class BufferElement
	{
	public:
		ShaderDataType m_dataType;
		uint32_t m_size;
		uint32_t m_offset;
		bool m_normalised;
		BufferElement() {} //!< Default constructor
		BufferElement(ShaderDataType dataType, bool normalised = false) :
			m_dataType(dataType),
			m_size(SDT::size(dataType)),
			m_offset(0),
			m_normalised(normalised)
		{} //!< Constructor with params
	};

	/** \class BufferLayout
	* Abstraction of the notion of a buffer layout
	*/

	class BufferLayout
	{
	public:
		BufferLayout() {}; //!< Default constructor
		BufferLayout(const std::initializer_list<BufferElement>& element) : m_elements(element) { calcStrideAndOffset(); } //!< Constructor
		inline uint32_t getStride() { return m_stride; }
		inline std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		inline std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		inline std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
		void addElement(BufferElement elements)
		{
			m_elements.push_back(BufferElement(elements));
			calcStrideAndOffset();
		}
	private:
		std::vector<BufferElement> m_elements; //!< Buffer elements
		uint32_t m_stride; //!< Width is bytes of the buffer line
		void calcStrideAndOffset(); //!< Claculate stride and offset based on elements;

	};

	void BufferLayout::calcStrideAndOffset()
	{
		uint32_t l_offset = 0;

		for (auto& element : m_elements)
		{
			element.m_offset = l_offset;
			l_offset += element.m_size;
		}

		m_stride = l_offset;
	}
}