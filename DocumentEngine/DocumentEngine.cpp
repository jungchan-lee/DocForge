#include "DocumentEngine.h"

#include <fstream>
#include <iostream>

#include "FileTypeResolver.h"
#include "ExportFormatResolver.h"
#include "IDocumentParser.h"
#include "SimpleSectionDetector.h"

#include <fpdfview.h>
#include <fpdf_text.h>

namespace DocEngine::Engine
{
	DocumentEngine::DocumentEngine()
	{
		ChunkBuilder = std::make_unique<Chunk::FixedSizeChunkBuilder>(1000);

	}

	DocumentEngine::~DocumentEngine()
	{

	}

	bool DocumentEngine::Process(const std::string& InputPath, const std::string& OutputPath)
	{
		Document.Pages.clear();
		Document.Chunks.clear();
		Document.Sections.clear();

		if (!ParseDocument(InputPath))
		{
			std::cout << "Parse Failed\n";

			return false;
		}

		std::cout << "Page Count: " << Document.Pages.size() << "\n";

		if(!DetectSections())
		{
			std::cout << "Section Detection Failed\n";
			return false;
		}

		std::cout << "Section Count: " << Document.Sections.size() << "\n";

		if(!BuildChunks())
		{
			std::cout << "Chunk Building Failed\n";
			return false;
		}

		std::cout << "Chunk Count: " << Document.Chunks.size() << "\n";

		if (!ExportDocument(OutputPath))
		{
			std::cout << "Export Failed\n";
			return false;
		}

		return true;
	}

	bool DocumentEngine::ParseDocument(const std::string& FilePath)
	{
		Core::EDocumentType DocumentType = Parser::FileTypeResolver::ResolveFileType(FilePath);

		Document.DocumentType = DocumentType;

		Interface::IDocumentParser* DocumentParser = ParserRegistry.GetParser(DocumentType);

		if (!DocumentParser)
		{
			std::cout << "Unsupported File Type\n";

			return false;
		}

		return DocumentParser->ParseDocument(FilePath, Document);
	}

	bool DocumentEngine::ExportDocument(const std::string& OutputPath)
	{
		Core::EExportFormatType Format = Exporter::ExportFormatResolver::ResolveExportFormat(OutputPath);

		Interface::IDocumentExporter* DocumentExporter = ExporterRegistry.GetExporter(Format);

		if (!DocumentExporter)
		{
			std::cout << "Unsupported Export Format\n";

			return false;
		}

		return DocumentExporter->ExportDocument(Document, OutputPath);
	}

	bool DocumentEngine::BuildChunks()
	{
		if (!ChunkBuilder)
		{
			return false;
		}

		return ChunkBuilder->BuildChunks(Document);
	}

	bool DocumentEngine::DetectSections()
	{
		Section::SimpleSectionDetector Detector;

		return Detector.DetectSections(Document);
	}

}