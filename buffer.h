#ifndef __BUFFER_H_
#define __BUFFER_H_
#include "string.h"

namespace kcommon {

class CircularBuffer {
public:
	CircularBuffer() : m_buf(0), m_max(0), m_read(0), m_write(0) {}
	CircularBuffer(int size) : m_buf(new char[2*size], m_max(size), m_read(0), m_write(0) {}
	
	int write(const char *data, unsigned len) {
	
	}

	int read(char *buff, unsigned len) {
		int ret = len
	}

private:
	CircularBuffer(const CircularBuffer &rh) {}
	CircularBuffer& operator = (const CircularBuffer &rh) { return *this; }

	int writeAvailable() {
		return m_max - m_write;
	}

	int readAvailable() {
		return m_write - m_read;
	}

private:
	char *m_buf;
	unsigned m_max;
	unsigned m_read;
	unsigned m_write;
};

template<int __BUFFER_LEN = 0x4000>
class Block {
public:
	Block() { clear(); } 

	virtual ~Block() { }
	
	// construct with an exist data.
	Block(const char *data, int len) {
		m_writeIndex = len > __BUFFER_LEN ? __BUFFER_LEN : len;
		memcpy(m_data, data, m_writeIndex);
	}

	Block(const Block &rh) {
		*this = rh;
	}

	BufferBlock& operator = (const BufferBlock &rh) {
		if (this != &rh) {
			*this = rh;
		}
		return *this;
	}

	int read(char *buffer, int size) {
		int ret = m_writeIndex - m_readIndex;
	   	ret = ret > size ? size : ret;
		memcpy(buffer, m_data + m_readIndex, ret);
		m_readIndex += ret;
		return ret;
	}

	int write(const char *data, int len) {
		int ret = __BUFFER_LEN - m_writeIndex;
		ret = len > ret ? ret : len;
		memcpy(m_data + m_writeIndex, data, ret);
		m_writeIndex += ret;
		return ret;
	}

	void clear() {
		memset(this, 0, *this);
	}

private:
	char m_data[__BUFFER_LEN];
	int m_readIndex;
	int m_writeIndex;
};

template<typename _AL = KDefaultAllocator, typename _LOCK = KNoneLock>
class RawBuffer : public _LOCK {
struct Node {
	Node *next;
	Block data;
};

public:


}
// end namespace kcommon
