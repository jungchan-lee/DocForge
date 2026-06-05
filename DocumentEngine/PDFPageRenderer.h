#pragma once

#include <string>
#include <vector>

#include <fpdfview.h>

namespace DocEngine::Parser
{
	//PDF 페이지 -> 이미지(Bitmap) 렌더링 클래스
	class PDFPageRenderer
	{
	public:
		struct RenderResult
		{
			int Width = 0;
			int Height = 0;
		};

		bool RenderPageToImage(FPDF_DOCUMENT Document, int PageIndex, const std::string& OutputPath, RenderResult& OutResult);

		FPDF_BITMAP RenderRegionToBitmap(
			FPDF_PAGE Page,
			float Left,
			float Top,
			float Right,
			float Bottom);

	private:
		int RenderWidth = 1920;
		int RenderHeight = 1080;

	};

}


