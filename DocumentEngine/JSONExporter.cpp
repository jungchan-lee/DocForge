#include "JSONExporter.h"

#include "Document.h"
#include "DocumentChunk.h"
#include "JSONUtility.h"
#include "BlockTypeUtility.h"

#include <fstream>


namespace DocEngine::Exporter
{
	bool JSONExporter::ExportDocument(const DocEngine::Core::Document& Document, const std::string& OutputPath)
	{
		std::ofstream OutFile(OutputPath);

		if (!OutFile.is_open())
		{
			return false;
		}

		OutFile << "{\n";

		// Document Type
		OutFile << "  \"documentType\": \"" << JSONUtility::DocumentTypeToString(Document.DocumentType) << "\",\n";

		// Pages
		/*OutFile << "  \"pages\": [\n";

		for (size_t i = 0; i < Document.Pages.size(); ++i)
		{
			const auto& Page = Document.Pages[i];

			OutFile << "    {\n";
			OutFile << "      \"pageIndex\": "
				<< Page.PageIndex
				<< ",\n";

			OutFile << "      \"blocks\": [\n";

			for (size_t j = 0; j < Page.Blocks.size(); ++j)
			{
				const auto& Block = Page.Blocks[j];

				OutFile << "        {\n";

				OutFile << "          \"text\": \""
					<< JSONUtility::EscapeJSONString(Block->GetText())
					<< "\"\n";

				OutFile << "        }";

				if (j != Page.Blocks.size() - 1)
				{
					OutFile << ",";
				}

				OutFile << "\n";
			}

			OutFile << "      ]\n";
			OutFile << "    }";

			if (i != Document.Pages.size() - 1)
			{
				OutFile << ",";
			}

			OutFile << "\n";
		}

		OutFile << "  ],\n";*/

		// Chunks
		OutFile << "  \"chunks\": [\n";

		for (size_t i = 0; i < Document.Chunks.size(); ++i)
		{
			const auto& Chunk = Document.Chunks[i];

			OutFile << "    {\n";

			OutFile << "      \"chunkId\": \""
				<< JSONUtility::EscapeJSONString(Chunk.ChunkId)
				<< "\",\n";

			OutFile << "      \"text\": \""
				<< JSONUtility::EscapeJSONString(Chunk.Text)
				<< "\",\n";

			OutFile << "      \"sectionName\": \""
				<< JSONUtility::EscapeJSONString(Chunk.SectionName)
				<< "\",\n";

			OutFile << "      \"startPage\": "
				<< Chunk.StartPage
				<< ",\n";

			OutFile << "      \"endPage\": "
				<< Chunk.EndPage
				<< ",\n";

			OutFile << "      \"tokenCount\": "
				<< Chunk.TokenCount
				<< ",\n";

			OutFile << "      \"characterCount\": "
				<< Chunk.CharacterCount
				<< "\n";

			OutFile << "    }";

			if (i != Document.Chunks.size() - 1)
			{
				OutFile << ",";
			}

			OutFile << "\n";
		}

		OutFile << "  ]\n";

		OutFile << "}\n";

		OutFile.close();

		return true;
	}
}