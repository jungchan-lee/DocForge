#include "DOCXParser.h"

#include "Document.h"

#include "DOCXArchive.h"
#include "DOCXXMLParser.h"

namespace DocEngine::Parser
{
	bool DOCXParser::ParseDocument(const std::string& FilePath, DocEngine::Core::Document& OutDocument)
	{
        OutDocument.DocumentType = Core::EDocumentType::DOCX;

        std::string TempDirectory = "./TempDOCX";

        DOCXArchive Archive;

        if (!Archive.ExtractArchive(FilePath, TempDirectory))
        {
            return false;
        }

        DOCXXMLParser XMLParser;

        return XMLParser.ParseDocumentXML(TempDirectory + "/word/document.xml", OutDocument);
	}
}