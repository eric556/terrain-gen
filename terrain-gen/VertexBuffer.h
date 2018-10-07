#pragma once
#include <GL\glew.h>
#include "Buffer.h"
#include "GLUtil.h"

class VertexBuffer : public Buffer
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="VertexBuffer"/> class.
	/// </summary>
	/// <param name="data">The vertex data.</param>
	/// <param name="size">The size of the vertex data (bytes).</param>
	VertexBuffer(const void* data, unsigned int size);

	/// <summary>
	/// Finalizes an instance of the <see cref="VertexBuffer"/> class.
	/// </summary>
	~VertexBuffer();

	/// <summary>
	/// Binds this VBO.
	/// </summary>
	void Bind() const;

	/// <summary>
	/// Unbinds this VBO.
	/// </summary>
	void Unbind() const;

	/// <summary>
	/// Sets the VBO data.
	/// </summary>
	/// <param name="data">The vertex data.</param>
	/// <param name="size">The vertex data size (bytes).</param>
	void SetData(const void* data, unsigned int size);

	inline unsigned int GetID() const { return m_ID; }

	inline unsigned int GetCount() const { return m_Count; }
private:
	unsigned int m_Count;
	unsigned int m_ID;
	mutable bool m_copied;
};