#pragma once

#include "BL_Core.h"

namespace BassLive
{
    template<class T>
    class Buffer
    {
    public:
        //================================================================
        Buffer()
        {
            bufferSize = 1;
            buffer = new T[bufferSize];
        }

        ~Buffer()
        {
            delete[] buffer;
        }

        //================================================================
        UInt size()
        {
            return bufferSize;
        }

        void resize(UInt size)
        {
            T* bufferToDelete = buffer;

            bufferSize = size > 0 ? size : 1;
            buffer = new T[bufferSize];

            delete[] bufferToDelete;
        }

        //================================================================
        T& operator[](UInt pointer)
        {
            return (pointer < bufferSize) ? buffer[pointer] : buffer[0];
        }

        const T& operator[](UInt pointer) const
        {
            return (pointer < bufferSize) ? buffer[pointer] : buffer[0];
        }
        
    private:
        //================================================================
        UInt bufferSize;
        T* buffer;
    };
}
