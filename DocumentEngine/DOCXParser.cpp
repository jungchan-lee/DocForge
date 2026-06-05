#include "DOCXParser.h"

#include "Document.h"

#include "DOCXArchive.h"
#include "DOCXXMLParser.h"
#include "ImageParser.h"

#include <filesystem>

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

		//---------------------------------
		// document.xml 파싱
		//---------------------------------

		DOCXXMLParser XMLParser;

		bool bXMLSuccess = XMLParser.ParseDocumentXML(TempDirectory + "/word/document.xml", OutDocument);

		if (!bXMLSuccess)
		{
			return false;
		}

		//---------------------------------
		// media 폴더 OCR
		//---------------------------------

		std::string MediaDirectory = TempDirectory + "/word/media";

		if (std::filesystem::exists(MediaDirectory))
		{
			for (const auto& Entry : std::filesystem::directory_iterator(MediaDirectory))
			{
				if (!Entry.is_regular_file())
				{
					continue;
				}

				Core::Document ImageDocument;

				ImageParser Parser;

				bool bImageSuccess = Parser.ParseDocument(Entry.path().string(), ImageDocument);

				if (!bImageSuccess)
				{
					continue;
				}

				if (ImageDocument.Pages.empty())
				{
					continue;
				}

				//---------------------------------
				// OCRBlock 복사
				//---------------------------------

				for (auto& OCRBlock : ImageDocument.Pages[0].OCRBlocks)
				{
					OutDocument.Pages[0].OCRBlocks.push_back(OCRBlock);
				}

				//---------------------------------
				// ImageBlock 복사
				//---------------------------------

				for (auto& ImageBlock : ImageDocument.Pages[0].ImageBlocks)
				{
					OutDocument.Pages[0].ImageBlocks.push_back(ImageBlock);
				}
			}
		}

		return true;
    }
}