#ifndef __BUFFER_H_
#define __BUFFER_H_
#include "string.h"

namespace kcommon {

// a simple ring buffer without thread safety.
class RingBuffer {
public:
	RingBuffer() : m_buf(0), m_max(0), m_read(0), m_write(0) {}
	RingBuffer(int size) : m_buf(new char[size], m_max(size), m_read(0), m_write(0) {}
	~RingBuffer() { if (m_buf) delete []m_buf; }
	
	// maybe truncated or only write 0 bytes.(fail if truncated?)
	unsigned write(const char *data, unsigned len) {
		if (m_max - m_write < len && m_read > 0) sink();
		unsigned ret = (m_max - m_write) > len ? len : (m_max - m_write);
		
		// write hardly
		memcpy(m_buf + m_write, data, ret);
		m_write += ret;

		return ret;
	}

	unsigned read(char *out, unsigned len) {
		return read_impl(out, len);
	}

	// read data, but do not move the read index
	unsigned softRead(char *out, unsigned len) {
		return read_impl(out, len, false);
	}

	// size can read.
	unsigned readSize() { return m_write - m_read; } 
	
	// read buffer start
	const char* getStart() { return m_buf + m_read; }

	// skip read some bytes, return the length moved acturally
	unsigned move(unsigned len) {
		unsigned offset = readSize() > len ? len : readSize();
		m_read += offset;
		return offset;		
	}

	// give up all write and read contents
	void reset() {
		m_read = 0;
		m_write = 0;
	}

protected:
	// disable copy
	RingBuffer(const RingBuffer &rh) {}
	RingBuffer& operator = (const RingBuffer &rh) { return *this; }
	
private:	
	unsigned read_impl(char *out, unsigned len, bool move = true) {
		int ret = (m_write - m_read) > len ? len : (m_write - m_read);
		memcpy(out, m_buf + m_read, ret);
		if (move) m_read += ret;
		return ret;
	}

	void sink() {
		memcpy(m_buf, m_buf + m_read, m_write - m_read);
		m_write -= m_read;
		m_read = 0;
	}

private:
	char *m_buf;
	unsigned m_max;
	unsigned m_read;
	unsigned m_write;
};

} // end namespace kcommon
