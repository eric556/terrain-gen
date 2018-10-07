#pragma once
#include <GL\glew.h>
#include "Buffer.h"
#include "GLUtil.h"

class IndexBuffer : public Buffer
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="IndexBuffer"/> class.
	/// </summary>
	/// <param name="data">The index data.</param>
	/// <param name="count">The index data count.</param>
	IndexBuffer(const unsigned int* data, unsigned int count);

	/// <summary>
	/// Finalizes an instance of the <see cref="IndexBuffer"/> class.
	/// </summary>
	~IndexBuffer();

	/// <summary>
	/// Binds this IBO.
	/// </summary>
	void Bind() const;

	/// <summary>
	/// Unbinds this IBO.
	/// </summary>
	void Unbind() const;

	/// <summary>
	/// Sets the data of this IBO.
	/// </summary>
	/// <param name="data">The index data.</param>
	/// <param name="count">The index data count.</param>
	void SetData(const void* data, unsigned int count);

	/// <summary>
	/// Gets the GL identifier. 
	/// </summary>
	/// <returns>the GL identifier of the IBO</returns>
	inline unsigned int GetID() const { return m_ID; }

	/// <summary>
	/// Gets the data count.
	/// </summary>
	/// <returns>the data count</returns>
	inline unsigned int GetCount() const { return m_Count; }
private:
	unsigned int m_ID;
	unsigned int m_Count;
	mutable bool m_copied;
};