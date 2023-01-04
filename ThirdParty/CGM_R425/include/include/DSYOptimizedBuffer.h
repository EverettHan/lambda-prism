
// Make sure users DO NOT include this header which is implementation detail
#if !defined(DSYOptimizedBuffer_INTERNAL_DONT_INCLUDE)
#error This header is an INTERNAL dependency of other non-internal headers.
#endif  // DSYOptimizedBuffer_INTERNAL_DONT_INCLUDE

#ifndef DSYOptimizedBuffer_H
#define DSYOptimizedBuffer_H

#include <utility>      // std::swap, std::move
#include <type_traits>  // std::is_trivial

namespace DSY
{
    /**
     * Implementation details.
     * DO NOT USE!
     */
    namespace internal
    {
        /**
         * OptimizedBuffer.
         * T: buffer object type
         * N: the number of elements that can be held by the preallocated buffer
         * The main interest of this class over std::vector is the preallocated buffer to optimize performance.
         */
        template<typename T, size_t N>
        class OptimizedBuffer
        {
        public:
            static constexpr size_t SizPreAlloc = N;
            
            /**
             * OptimizedBuffer.
             * Builds an empty buffer object, that can be assigned to later on.
             */
            OptimizedBuffer() noexcept : m_pBuffer(nullptr), m_Size(0) {
                static_assert(std::is_trivial<T>::value, "This class only supports trivial types (cf. realloc/memcpy etc)");
                static_assert(SizPreAlloc > 0, "'N' must be a strictly positive number");
                // DO NOT assign m_pBuffer to m_local and m_Size to N in the default constructor!
                // Indeed, this would cripple performance of copy/move of unused/empty OptimizedBuffer instances
            }
            /**
             * OptimizedBuffer.
             * Builds a buffer object capable of holding 'iSize' number of elements. 
             * Call 'data' to get a pointer to the buffer.
             */
            OptimizedBuffer(size_t iSize) : OptimizedBuffer() {
                reset(iSize);   // buffer's pointer can be retrieved by calling member function 'data'
            }
            ~OptimizedBuffer();
            
            OptimizedBuffer(const OptimizedBuffer&);
            OptimizedBuffer(OptimizedBuffer && other);
            OptimizedBuffer & operator= ( OptimizedBuffer other);
            
            
            /**
             * data.
             * @return a pointer to the reserved buffer, or nullptr if the instance is empty: 
             *         neither ctor(size_t), nor reset, nor resize were called.
             */
            T *data() const noexcept { return m_pBuffer; }
            
            /**
             * reset.
             * Sets the buffer size to iSize, by expanding it or shrinking it as necessary, 
             * with no guarantee that the current contents of the buffer are preserved (if any).
             * @param iSize. If <= N, use internal buffer; if > N, use dynamically-allocated memory
             * @return a pointer to a buffer of size 'iSize'.
             * IMPORTANT: pointers obtained by previous calls to data/reset/resize must be considered invalidated.
             */
            T *reset (size_t iSize);
            
            /**
             * resize.
             * Sets the buffer size to iSize, by expanding it or shrinking it as necessary, 
             * with the guarantee that the current contents of the buffer are preserved (if any).
             * @see reset, preferred alternative if data preservation is not a requirement.
             * @param iSize. If <= N, use internal buffer; if > N, use dynamically-allocated memory
             * @return a pointer to a buffer of size 'iSize'.
             * IMPORTANT: pointers obtained by previous calls to data/reset/resize must be considered invalidated.
             */
            T *resize(size_t iSize);
            
            /**
             * detach.
             * Steal the data held by the instance, if applicable.
             * @return a pointer to a buffer that must be released with 'free', or nullptr if there is nothing to steal.
             */
            T *detach();
            
        private:
            T m_local[N];
            T *m_pBuffer;
            size_t m_Size;
        };  // class OptimizedBuffer
        
        
        template<typename T, size_t N>
        inline OptimizedBuffer<T,N>::~OptimizedBuffer()
        {
            if((m_pBuffer != m_local) && m_pBuffer)
                free(m_pBuffer);    // free(NULL) is allowed
        }
        
        template<typename T, size_t N>
        inline OptimizedBuffer<T,N>::OptimizedBuffer(const OptimizedBuffer & other) : m_pBuffer(nullptr), m_Size(other.m_Size)
        {
            if(!m_Size) 
                return; // Nothing to copy => m_pBuffer stays null
            if(other.m_pBuffer != other.m_local)
            {
                m_pBuffer = (T *)malloc(m_Size * sizeof(T));
                memcpy(m_pBuffer, other.m_pBuffer,  m_Size * sizeof(T));
            }
            else
            {
                memcpy(m_local, other.m_local, m_Size * sizeof(T));
                m_pBuffer = m_local;
            }
        }
        
        template<typename T, size_t N>
        inline OptimizedBuffer<T,N>::OptimizedBuffer(OptimizedBuffer && other) : m_pBuffer(nullptr), m_Size(other.m_Size)
        {
            if(!m_Size) 
                return; // Nothing to move => m_pBuffer stays null
            if(other.m_pBuffer != other.m_local)
            {
                // Steal other's dynamically allocated buffer(other.m_pBuffer might be null)
                std::swap(m_pBuffer, other.m_pBuffer);
            }
            else
            {
                // Copy other's internal buffer
                memcpy(m_local, other.m_local, m_Size * sizeof(T));
                m_pBuffer = m_local;
                other.m_pBuffer = nullptr;   // for detach to return nullptr on moved instances...
            }
        }
        
        template<typename T, size_t N>
        inline OptimizedBuffer<T,N> & OptimizedBuffer<T,N>::operator= ( OptimizedBuffer<T,N> other)
        {
            this->~OptimizedBuffer<T,N>();
            new (this) OptimizedBuffer<T,N>(std::move(other));
            return *this;
        }
        
        template<typename T, size_t N>
        inline T * OptimizedBuffer<T,N>::reset(size_t iSize)
        {
            if(!iSize)
                return nullptr; // Zero size not allowed! To clear an existing instance, move assign a default-constructed instance to it
            m_Size = iSize;
            // Use internal buffer if possible; otherwise, dynamically-allocated memory
            if(m_Size <= N) {
                // Use internal buffer
                if(m_pBuffer != m_local) {
                    if(m_pBuffer) free(m_pBuffer);
                    m_pBuffer = m_local;
                }
            } else {
                // dynamically-allocated memory required
                m_pBuffer = (m_pBuffer == m_local) ? (T *)malloc(m_Size * sizeof(T)) : (T *)realloc(m_pBuffer, m_Size * sizeof(T));
            }
            return m_pBuffer;
        }
        
        template<typename T, size_t N>
        inline T * OptimizedBuffer<T,N>::resize(size_t iSize)
        {
            if(!iSize)
                return nullptr; // Zero size not allowed! To clear an existing instance, move assign a default-constructed instance to it
            // Use local/internal buffer if possible; otherwise, dynamically-allocated memory
            bool const bNewBufferIsLocal = (iSize <= N);
            if(!m_Size || 
                // The following condition is true if the buffer type does not change from/to 'm_local' buffer <=> dynamically-allocated buffer
                !( bNewBufferIsLocal ^ /*Current buffer is local*/(m_pBuffer == m_local) ) ) 
            {
                // If both the current/new buffers are dynamically allocated: copying data will be handled automatically by realloc
                // else: nothing to copy explicitely
                m_pBuffer = bNewBufferIsLocal ? m_local : (T *)realloc(m_pBuffer, iSize * sizeof(T));
            } else {
                // Buffer type changes => explicit copy of current data is required
                T *pNewBuffer = bNewBufferIsLocal ? m_local : (T *)malloc(iSize * sizeof(T));
                memcpy(pNewBuffer, m_pBuffer, ((m_Size < iSize) ? m_Size : iSize) * sizeof(T));   // Handle both expand & shrink
                if(bNewBufferIsLocal) free(m_pBuffer);  // Release previous buffer
                m_pBuffer = pNewBuffer;
            }
            m_Size = iSize;
            return m_pBuffer;
        }
        
        template<typename T, size_t N>
        inline T *OptimizedBuffer<T,N>::detach()
        {
            T *p = m_pBuffer;
            if(m_pBuffer == m_local)    // Implies m_Size > 0
            {
                p = (T *)malloc(m_Size * sizeof(T));
                memcpy(p, m_pBuffer, m_Size * sizeof(T));
            }
            m_pBuffer = nullptr;
            return p;
        }
        
    }   // namespace internal
}   // namespace DSY

#endif  // DSYOptimizedBuffer_H
