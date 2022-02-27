#ifndef MOHAWK_CRT_H
#define MOHAWK_CRT_H

#include <exec/types.h>

namespace Mohawk
{
    // Allocate and Release shared string memory pools 
    void AllocateSharedStringMemory();
    void ReleaseSharedStringMemory();

    // Light non-mutable garbage collected string
    class String
    {
        private:
            CONST_STRPTR mText;
            UWORD mLength;
            static const char sNull;

            void Release();

        public:
            String();
            ~String();

            // Allow Move
            String(String&&);
            String& operator=(String&&);

            // Disallow Copy
            String(const String&) = delete;
            String(String&) = delete;
            String& operator=(const String&) = delete;
            String& operator=(String&) = delete;

            inline UWORD GetLength() const { return mLength; }
            inline UWORD GetNumBytes() const { return mLength + 1; }
            CONST_STRPTR GetStrPtr() const;
    };

}

#endif
