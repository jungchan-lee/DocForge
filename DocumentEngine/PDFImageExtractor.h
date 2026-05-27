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
	class PDFImageExtractor
	{
	public:
		// PDF에서 이미지 추출
		std::vector<std::shared_ptr<Core::ImageBlock>>
			ExtractImages(FPDF_DOCUMENT Document, int PageIndex);

	private:
		int Width = 0;
		int Height = 0;
	};
}


