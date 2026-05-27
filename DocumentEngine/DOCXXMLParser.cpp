#include "DOCXXMLParser.h"

#include "Document.h"
#include "DocumentPage.h"
#include "TextBlock.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <pugixml.hpp>

namespace DocEngine::Parser
{
	bool DOCXXMLParser::ParseDocumentXML(const std::string& XMLPath, DocEngine::Core::Document& OutDocument)
	{
		std::ifstream File(XMLPath);

		if (!File.is_open())
		{
			std::cout << "Failed to open XML\n";

			return false;
		}

		std::stringstream Buffer;

		Buffer << File.rdbuf();

		std::string XMLContent = Buffer.str();

		pugi::xml_document XMLDocument;

		pugi::xml_parse_result Result = XMLDocument.load_string(XMLContent.c_str());

		if (!Result)
		{
			std::cout << "Failed to parse XML\n";

			return false;
		}

		pugi::xml_node DocumentNode = XMLDocument.child("w:document");

		pugi::xml_node BodyNode = DocumentNode.child("w:body");

		Core::DocumentPage Page;

		Page.PageIndex = 0;

		for (pugi::xml_node Paragraph : BodyNode.children("w:p"))
		{
			std::string ParagraphText;

			for (pugi::xml_node Run : Paragraph.children("w:r"))
			{
				pugi::xml_node TextNode = Run.child("w:t");

				if (TextNode)
				{
					ParagraphText += TextNode.text().as_string();

					ParagraphText += " ";
				}
			}

			auto TextBlock = std::make_shared<Core::TextBlock>();

			TextBlock->PageIndex = 0;
			TextBlock->Text = ParagraphText;

			Page.TextBlocks.push_back(TextBlock);

			std::cout << ParagraphText << "\n";
		}

		OutDocument.Pages.push_back(Page);

		return true;
	}
}