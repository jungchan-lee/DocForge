#pragma once

#include <string>

namespace DocEngine::Core
{
	class Document;
}

namespace DocEngine::Interface
{
	class IDocumentExporter
	{
	public:
		virtual ~IDocumentExporter() = default;

	public:
		virtual bool ExportDocument(
			const DocEngine::Core::Document& Document,
			const std::string& OutputPath) = 0;
	};
}