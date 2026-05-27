#include "PDFPageRenderer.h"

#define _CRT_SECURE_NO_WARNINGS // 프로젝트 속성에 C++ 전처리기에 예외
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


#include <iostream>

namespace DocEngine::Parser
{
	bool PDFPageRenderer::RenderPageToImage(FPDF_DOCUMENT Document, int PageIndex, const std::string& OutputPath, RenderResult& OutResult)
	{
		FPDF_PAGE Page = FPDF_LoadPage(Document, PageIndex);

		if (!Page)
		{
			return false;
		}

		const float Scale = 3.0f;

		const int Width = static_cast<int>(FPDF_GetPageWidth(Page) * Scale);

		const int Height = static_cast<int>(FPDF_GetPageHeight(Page) * Scale);

		FPDF_BITMAP Bitmap = FPDFBitmap_Create(Width, Height, 1);

		if (!Bitmap)
		{
			FPDF_ClosePage(Page);
			return false;
		}

		FPDFBitmap_FillRect(
			Bitmap,
			0,
			0,
			Width,
			Height,
			0xFFFFFFFF);

		FPDF_RenderPageBitmap(
			Bitmap,
			Page,
			0,
			0,
			Width,
			Height,
			0,
			FPDF_ANNOT);

		// TODO:
		// Bitmap -> PNG 저장

		unsigned char* Buffer = static_cast<unsigned char*>(FPDFBitmap_GetBuffer(Bitmap));

		const int Stride = FPDFBitmap_GetStride(Bitmap);

		const int Result =
			stbi_write_png(
				OutputPath.c_str(),
				Width,
				Height,
				4,
				Buffer,
				Stride);

		if (Result == 0)
		{
			FPDFBitmap_Destroy(Bitmap);
			FPDF_ClosePage(Page);

			return false;
		}

		OutResult.Width = Width;
		OutResult.Height = Height;

		FPDFBitmap_Destroy(Bitmap);

		FPDF_ClosePage(Page);

		return true;
	}
}