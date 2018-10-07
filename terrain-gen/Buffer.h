#pragma once

class Buffer {
public:
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
	virtual void SetData(const void* data, unsigned int count) = 0;
	virtual unsigned int GetID() const = 0;
	virtual unsigned int GetCount() const = 0;
};