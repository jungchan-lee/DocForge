#pragma once

#include <string>

#include "Document.h"
#include "ParserRegistry.h"
#include "ExporterRegistry.h"
#include "FixedSizeChunkBuilder.h"

namespace DocEngine::Engine
{
	class DocumentEngine
	{
    public:
		DocumentEngine();
        ~DocumentEngine();

    public:

        bool Process(const std::string& InputPath, const std::string& OutputPath);

		const Core::Document& GetDocument() const { return Document; }

        void SetChunkBuilder(std::unique_ptr<Interface::IChunkBuilder> InChunkBuilder)
        {
            ChunkBuilder = std::move(InChunkBuilder);
		}

    private:

        bool ParseDocument(const std::string& FilePath);

        bool ExportDocument(const std::string& OutputPath);

        bool BuildChunks();

        bool DetectSections();

    private:

        Core::Document Document;

        Parser::ParserRegistry ParserRegistry;

        Exporter::ExporterRegistry ExporterRegistry;;

        std::unique_ptr<Interface::IChunkBuilder> ChunkBuilder;
       

	};

}

