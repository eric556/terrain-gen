#pragma once
#include "Buffer.h"
#include "BufferLayout.h"
#include "GLUtil.h"

class VertexArray
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="VertexArray"/> class.
	/// </summary>
	VertexArray();

	/// <summary>
	/// Finalizes an instance of the <see cref="VertexArray"/> class.
	/// </summary>
	~VertexArray();

	/// <summary>
	/// Binds this VAO.
	/// </summary>
	void Bind();

	/// <summary>
	/// Unbinds this VAO.
	/// </summary>
	void Unbind();

	/// <summary>
	/// Adds a VBO with the given layout to the VAO
	/// </summary>
	/// <param name="vb">The vbo.</param>
	/// <param name="layout">The vbo layout.</param>
	void AddBuffer(const Buffer& vb, const BufferLayout& layout);

	inline unsigned int GetID() const { return m_ID; }
private:
	unsigned int m_ID;
	mutable bool m_copied;
};