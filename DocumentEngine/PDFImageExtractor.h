#pragma once

#include <vector>
#include <memory>

#include <fpdfview.h>

namespace DocEngine::Core
{
	class ImageBlock;
}

namespace DocEngine::Parser
{
	struct ExtractedImage
	{
		std::shared_ptr<Core::ImageBlock> ImageBlock;
		FPDF_BITMAP Bitmap = nullptr;
	};

	class PDFImageExtractor
	{
	public:
		// PDF에서 이미지 추출
		/*std::vector<std::shared_ptr<Core::ImageBlock>>
			ExtractImages(FPDF_DOCUMENT Document, int PageIndex);*/

		std::vector<std::shared_ptr<Core::ImageBlock>> ExtractImages(FPDF_PAGE Page, int PageIndex);

	};
}


