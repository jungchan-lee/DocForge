#pragma once

#include <memory>
#include <unordered_map>

#include "IDocumentExporter.h"
#include "ExportFormatType.h"

namespace DocEngine::Exporter
{
	class ExporterRegistry
	{
	public:
		ExporterRegistry();

	public:
		Interface::IDocumentExporter* GetExporter(Core::EExportFormatType FormatType);

	private:
		std::unordered_map<Core::EExportFormatType, std::unique_ptr<Interface::IDocumentExporter>> Exporters;
	};
}

