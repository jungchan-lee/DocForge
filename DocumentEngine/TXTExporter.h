#pragma once

#include "IDocumentExporter.h"

namespace DocEngine::Exporter
{
	class TXTExporter : public Interface::IDocumentExporter
	{
	public:
		virtual bool ExportDocument(
			const DocEngine::Core::Document& Document,
			const std::string& OutputPath) override;
	};
}


