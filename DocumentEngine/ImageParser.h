#pragma once

#include <string>

#include "IDocumentParser.h"

namespace DocEngine::Core
{
	class Document;
}

namespace DocEngine::Parser
{
	class ImageParser : public Interface::IDocumentParser
	{
	public:
		virtual bool ParseDocument(const std::string& FilePath, Core::Document& Document) override;
	};
}


