#pragma once

#include <memory>
#include <unordered_map>

#include "DocumentType.h"

namespace DocEngine::Interface
{
	class IDocumentParser;
}

namespace DocEngine::Parser
{
	class ParserRegistry
	{
	public:
		ParserRegistry();

		Interface::IDocumentParser* GetParser(Core::EDocumentType DocumentType);

	private:
		std::unordered_map<Core::EDocumentType, std::unique_ptr<Interface::IDocumentParser>> Parsers;
	};

}


