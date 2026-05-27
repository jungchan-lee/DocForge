#pragma once

#include "IDocumentParser.h"

#include <memory>

namespace DocEngine::Parser
{
	class PDFParser : public Interface::IDocumentParser
	{
	public:
		virtual bool ParseDocument(const std::string& FilePath, Core::Document& OutDocument) override;

	};
}


