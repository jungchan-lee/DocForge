#include "ParserRegistry.h"

#include "PDFParser.h"
#include "DOCXParser.h"
#include "ImageParser.h"

namespace DocEngine::Parser
{
	ParserRegistry::ParserRegistry()
	{
		Parsers[Core::EDocumentType::PDF] = std::make_unique<PDFParser>();

		Parsers[Core::EDocumentType::DOCX] = std::make_unique<DOCXParser>();

		Parsers[Core::EDocumentType::PNG] = std::make_unique<ImageParser>();
		Parsers[Core::EDocumentType::JPEG] = std::make_unique<ImageParser>();
		Parsers[Core::EDocumentType::JPG] = std::make_unique<ImageParser>();



		//추가되는 parser를 parsers에 등록
	}

	Interface::IDocumentParser* ParserRegistry::GetParser(Core::EDocumentType DocumentType)
	{
		auto Found = Parsers.find(DocumentType);

		if(Found == Parsers.end())
		{
			return nullptr;
		}

		return Found->second.get();
	}
}