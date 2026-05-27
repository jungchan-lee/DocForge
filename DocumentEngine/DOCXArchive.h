#pragma once

#include <string>

namespace DocEngine::Parser
{
	class DOCXArchive
	{
	public:
		// 압축 해제
		bool ExtractArchive(
			const std::string& FilePath,
			const std::string& OutputDirectory);
	};

}

