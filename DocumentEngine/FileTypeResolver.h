#pragma once

#include <string>

#include "DocumentType.h"

namespace DocEngine::Parser
{
	class FileTypeResolver
	{
	public:
		static Core::EDocumentType ResolveFileType(const std::string& FilePath);
	};

}


