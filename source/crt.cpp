#include "crt.h"

#include <proto/exec.h>

namespace Mohawk
{
    // StringPool -------------------------------------------------------------

    static APTR sStringPool;

    void AllocateSharedStringMemory()
    {
        sStringPool = CreatePool(MEMF_ANY, 512, 256);
    }

    void ReleaseSharedStringMemory()
    {
        DeletePool(sStringPool);
        sStringPool = NULL;
    }

    // String -----------------------------------------------------------------

    const char String::sNull = 0;

    String::String()
     : mText(NULL), mLength(0)
    {
    }

    String::~String()
    {
        Release();
    }

    void String::Release()
    {
        if (mText != NULL && mLength != 0)
        {
            FreePooled(sStringPool, (APTR) mText, GetNumBytes());
            mText = NULL;
            mLength = 0;
        }
    }

    String::String(String&& other)
    {
        mText = other.mText;
        mLength = other.mLength;
        other.mText = NULL;
        other.mLength = 0;
    }

    String& String::operator=(String&& other)
    {
        Release();

        mText = other.mText;
        mLength = other.mLength;
        other.mText = NULL;
        other.mLength = 0;
    }

    CONST_STRPTR String::GetStrPtr() const
    {
        if (mText == NULL && mLength == 0)
        {
            return (CONST_STRPTR) &sNull;
        }
    }

}