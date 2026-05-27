#include "PDFImageExtractor.h"


#include <string>

#include "PDFPageRenderer.h"
#include "ImageBlock.h"

namespace DocEngine::Parser
{
	std::vector<std::shared_ptr<Core::ImageBlock>> PDFImageExtractor::ExtractImages(FPDF_DOCUMENT Document, int PageIndex)
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
	}
}