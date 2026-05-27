#include "PDFDocumetLoader.h"

namespace DocEngine::Parser
{
	PDFDocumetLoader::PDFDocumetLoader()
	{
		//PDF 라이브러리 초기화, 안하면 PDFIUM 관련 함수 호출 시 크래시
		FPDF_InitLibrary();
	}

	PDFDocumetLoader::~PDFDocumetLoader()
	{
		if (Document)
		{
			FPDF_CloseDocument(Document);
			Document = nullptr;
		}

		FPDF_DestroyLibrary();
	}

	bool PDFDocumetLoader::LoadDocument(const std::string& FilePath)
	{
		Document = FPDF_LoadDocument(FilePath.c_str(), nullptr);
		return Document != nullptr;
	}

	/*void PDFDocumetLoader::UnloadDocument()
	{
		if (Document)
		{
			FPDF_CloseDocument(Document);
			Document = nullptr;
		}
	}*/

	int PDFDocumetLoader::GetPageCount() const
	{
		if (!Document)
		{
			return 0;
		}
		return FPDF_GetPageCount(Document);
	}

	FPDF_PAGE PDFDocumetLoader::LoadPage(int PageIndex)
	{
		if (!Document)
		{
			return nullptr;
		}

		return FPDF_LoadPage(Document, PageIndex);
	}

	void PDFDocumetLoader::ClosePage(FPDF_PAGE Page)
	{
		if (Page)
		{
			FPDF_ClosePage(Page);
		}
	}
}