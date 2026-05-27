#pragma once

#include <string>

namespace DocEngine::Parser
{
	class PDFEncoding
	{
	public:
		//UTF Ã³¸®
		static std::string WideToUTF8(const std::wstring& WideString);
	};

}

