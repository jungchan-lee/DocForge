#pragma once

#include "DocumentType.h"

#include <string>

namespace DocEngine::Exporter
{
	class JSONUtility
	{
	public:
		static std::string EscapeJSONString(const std::string& Input);
		static std::string DocumentTypeToString(Core::EDocumentType Type);
	};

}

