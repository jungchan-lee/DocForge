#include "PDFImageExtractor.h"


#include <string>
#include <fpdf_edit.h>
#include <fpdf_transformpage.h>

#include "PDFPageRenderer.h"
#include "ImageBlock.h"
#include "IOCRProcessor.h"

namespace DocEngine::Parser
{
	/*std::vector<std::shared_ptr<Core::ImageBlock>> PDFImageExtractor::ExtractImages(FPDF_DOCUMENT Document, int PageIndex)
	{
        std::vector<std::shared_ptr<Core::ImageBlock>> Result;

        PDFPageRenderer Renderer;

        PDFPageRenderer::RenderResult RenderResult;

        std::string ImagePath = "page_" + std::to_string(PageIndex) + ".png";


        bool bSuccess = Renderer.RenderPageToImage(
                Document,
                PageIndex,
                ImagePath,
                RenderResult);

        if (!bSuccess)
        {
            return Result;
        }

        auto Block = std::make_shared<Core::ImageBlock>();

        Block->PageIndex = PageIndex;
        Block->ImagePath = ImagePath;
		Block->Width = RenderResult.Width;
		Block->Height = RenderResult.Height;

        Result.push_back(Block);

        return Result;
	}*/

    std::vector<std::shared_ptr<Core::ImageBlock>> PDFImageExtractor::ExtractImages(FPDF_PAGE Page, int PageIndex)
    {
		std::vector<std::shared_ptr<Core::ImageBlock>> Result;

		const int ObjectCount =
			FPDFPage_CountObjects(Page);

		for (int i = 0; i < ObjectCount; ++i)
		{
			FPDF_PAGEOBJECT Obj =
				FPDFPage_GetObject(Page, i);

			if (!Obj)
			{
				continue;
			}

			const int Type =
				FPDFPageObj_GetType(Obj);

			if (Type != FPDF_PAGEOBJ_IMAGE)
			{
				continue;
			}

			FS_FLOAT Left;
			FS_FLOAT Bottom;
			FS_FLOAT Right;
			FS_FLOAT Top;

			FPDFPageObj_GetBounds(
				Obj,
				&Left,
				&Bottom,
				&Right,
				&Top);

			auto Block =
				std::make_shared<Core::ImageBlock>();

			Block->PageIndex = PageIndex;

			Block->Left = Left;
			Block->Bottom = Bottom;
			Block->Right = Right;
			Block->Top = Top;

			Block->Width =
				static_cast<int>(Right - Left);

			Block->Height =
				static_cast<int>(Top - Bottom);

			Result.push_back(Block);
		}

		return Result;
    }
}