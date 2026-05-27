#include "PDFEncoding.h"

#include <Windows.h>

namespace DocEngine::Parser
{
    std::string PDFEncoding::WideToUTF8(const std::wstring& WideString)
    {
        if (WideString.empty())
        {
            return "";
        }

        int SizeNeeded = WideCharToMultiByte(
                CP_UTF8,
                0,
                WideString.data(),
                (int)WideString.size(),
                nullptr,
                0,
                nullptr,
                nullptr);

        std::string Result(SizeNeeded, 0);

        WideCharToMultiByte(
            CP_UTF8,
            0,
            WideString.data(),
            (int)WideString.size(),
            Result.data(),
            SizeNeeded,
            nullptr,
            nullptr);

        return Result;
    }
}