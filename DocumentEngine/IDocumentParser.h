#pragma once

#include <string>

namespace DocEngine::Core
{
	class Document;
}

namespace DocEngine::Interface
{
	class IDocumentParser
	{
	public:
		virtual ~IDocumentParser() = default;

	public:
		virtual bool ParseDocument(const std::string& FilePath, Core::Document& OutDocument) = 0;
	};
}