#pragma once

#include "BL_Core.h"

namespace BassLive
{
    template<class ValueType>
    class Buffer
    {
    public:
        Buffer()
        {
            bufferSize = 1;
            buffer = new ValueType[bufferSize];
        }

        ~Buffer()
        {
            delete[] buffer;
        }

        UInt size()
        {
            return bufferSize;
        }

        void resize(UInt newSize)
        {
            if (newSize < 1)
                newSize = 1;

            UInt oldSize = bufferSize;

            ValueType* newBuffer = new ValueType[newSize];
            ValueType* oldBuffer = buffer;

            for (UInt i = 0; i < newSize && i < oldSize; ++i)
                newBuffer[i] = oldBuffer[i];

            buffer = newBuffer;
            bufferSize = newSize;

            delete[] oldBuffer;
        }

        ValueType& operator[](UInt pointer)
        {
            return (pointer < bufferSize) ? buffer[pointer] : buffer[0];
        }

        const ValueType& operator[](UInt pointer) const
        {
            return (pointer < bufferSize) ? buffer[pointer] : buffer[0];
        }
        
    private:
        ValueType* buffer;
        UInt bufferSize;
    };
}
