#include "TXTExporter.h"

#include <fstream>

#include "Document.h"

namespace DocEngine::Exporter
{
	bool TXTExporter::ExportDocument(const Core::Document& Document, const std::string& OutputPath)
	{
		std::ofstream OutFile(OutputPath, std::ios::binary);

		if (!OutFile.is_open())
		{
			return false;
		}

		unsigned char BOM[] =
		{
			0xEF,
			0xBB,
			0xBF
		};

		OutFile.write(reinterpret_cast<char*>(BOM), 3);

		for (const auto& Page : Document.Pages)
		{
			OutFile << "========== PAGE " << Page.PageIndex << " ==========\n";

			for (const auto& Block : Page.GetAllTextLikeBlocks())
			{
				OutFile << Block->GetText() << "\n";
			}

			OutFile << "\n";
		}

		OutFile.close();

		return true;
	}
	
}


