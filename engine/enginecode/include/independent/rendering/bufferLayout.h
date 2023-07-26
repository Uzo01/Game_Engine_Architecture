/** \file bufferLayout.h*/
#pragma once
#include "shaderDataType.h"
#include <vector>

namespace Engine
{
	/**
	\class which holds data about a single elemenet in a buffer layout 
	*/
	class BufferElement
	{
	public:
		ShaderDataType m_dataType;
		uint32_t m_size;
		uint32_t m_offset;
		bool m_normalised;

		BufferElement() {} //!< Default Constructor
		BufferElement(ShaderDataType dataType, bool normalised = false):
			m_dataType(dataType), m_size(SDT::size(dataType)), m_offset(0), m_normalised(normalised){}//!< Constructor with params
	};
	/** \class BufferLayout
	*	Abstraction of the notion of buffr layout 
	*/
	class BufferLayout
	{
	public:
		BufferLayout() {}; //!< Constructor
		BufferLayout(const std::initializer_list<BufferElement>& element) : m_element(element) { calcStrideAndOffset(); }
		inline uint32_t getStride()  const{ return m_stride; }
		void addElement(BufferElement element);
		 inline std::vector<BufferElement>::iterator begin() {return m_element.begin();} //!< begin iterator
		 inline std::vector<BufferElement>::iterator end() {return m_element.end();} //!< end iterator
		 inline std::vector<BufferElement>::const_iterator begin() const{return m_element.begin();}
		 inline std::vector<BufferElement>::const_iterator end() const{return m_element.end();}
	private:
		std::vector<BufferElement> m_element; //!< Buffer elements
		uint32_t m_stride; //!< Width is bytes of the a buffer line 
		void calcStrideAndOffset(); //!< Calculate stride and offsets based on elements
	};
	
}
