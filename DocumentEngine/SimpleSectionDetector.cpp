#include "SimpleSectionDetector.h"

#include "Document.h"
#include "DocumentPage.h"
#include "DocumentBlock.h"
#include "DocumentSection.h"

namespace DocEngine::Section
{
	bool SimpleSectionDetector::DetectSections(Core::Document& Document)
	{
        Document.Sections.clear();

        for (const auto& Page : Document.Pages)
        {
            for (const auto& Block : Page.GetAllTextLikeBlocks())
            {
                if (!Block)
                {
                    continue;
                }

                if (IsSectionTitle(Block->GetText()))
                {
                    Core::DocumentSection NewSection;

                    NewSection.Title = Block->GetText();

                    NewSection.StartPage = Page.PageIndex;
                    NewSection.EndPage = Page.PageIndex;

                    Document.Sections.push_back(NewSection);
                }
            }
        }

        return true;
	}

	bool SimpleSectionDetector::IsSectionTitle(const std::string& Text) const
	{
        if (Text.find("¡¶ ") != std::string::npos &&
            Text.find("¿Â") != std::string::npos)
        {
            return true;
        }

        if (Text.find("Chapter") != std::string::npos)
        {
            return true;
        }

        return false;
	}
}