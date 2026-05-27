#pragma once
#include "IDocumentParser.h"

#include <string>

namespace DocEngine::Core
{
	class Document;
}

namespace DocEngine::Parser
{
    class DOCXParser : public Interface::IDocumentParser
	{
	public:
		// docx Ã³¸® ÃÑ°ý
        bool ParseDocument(
            const std::string& FilePath,
            DocEngine::Core::Document& OutDocument) override;        
	};
}


