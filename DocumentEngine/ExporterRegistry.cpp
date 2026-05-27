#include "ExporterRegistry.h"

#include "TXTExporter.h"
#include "JSONExporter.h"

namespace DocEngine::Exporter
{
	ExporterRegistry::ExporterRegistry()
	{
		Exporters[Core::EExportFormatType::TXT] = std::make_unique<TXTExporter>();

		Exporters[Core::EExportFormatType::JSON] = std::make_unique<JSONExporter>();

		// Exporters[Core::EExportFormatType::Markdown] = std::make_unique<MarkdownExporter>();
	}

	Interface::IDocumentExporter* ExporterRegistry::GetExporter(Core::EExportFormatType FormatType)
	{
		auto Found = Exporters.find(FormatType);

		if (Found == Exporters.end())
		{
			return nullptr;
		}

		return Found->second.get();
	}
}