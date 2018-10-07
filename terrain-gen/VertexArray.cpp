#include "VertexArray.h"


VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_ID));
}

VertexArray::~VertexArray()
{
	if (!m_copied)
	{
		GLCall(glDeleteVertexArrays(1, &m_ID));
	}
}


void VertexArray::Bind()
{
	GLCall(glBindVertexArray(m_ID));
}

void VertexArray::Unbind()
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const Buffer & vb, const BufferLayout & layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normailzed, layout.GetStride(), (void*)offset));
		offset += element.count * BufferElement::GetSizeOfType(element.type);
	}
}
