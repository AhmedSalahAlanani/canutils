
#ifndef SRC_BUFFER_IMPL_H
#define SRC_BUFFER_IMPL_H

#include "Buffer.h"

namespace Buffer
{

template<typename T>
class BufferImpl : public Buffer<T>
{
public:
    BufferImpl() = delete;
    BufferImpl( unsigned int size )  : _size(size)
    {
        
    }
    virtual ~BufferImpl()
    {
        
    }
        
    virtual int read(T& msg) override = 0;
    virtual int write(const T& msg) override = 0;
    
    virtual unsigned int size() const override
    {
        return _size;
    }
    virtual int resize( unsigned int size ) override = 0;
    
    virtual bool hasNext() const override = 0;
    virtual bool isFull()  const override = 0;
    virtual bool isEmpty() const override = 0;
    
    /* TODO virtual void clean() const override = 0 */
    
    virtual std::string implementation() const override = 0;
        
protected:
        unsigned int _size;
};

} /* namespace Buffer */

#endif /* SRC_BUFFER_IMPL_h */