#include "PDFParser.h"

#include "Document.h"
#include "DocumentPage.h"

#include "TextBlock.h"

#include "PDFTextExtractor.h"
#include "PDFDocumetLoader.h"
#include "PDFPageParser.h"
#include "PDFPageRenderer.h"
#include "PDFImageExtractor.h"
#include "ImageBlock.h"
#include "OCRBlockBuilder.h"
#include "TesseractOCRProcessor.h"
#include "OCRBlock.h"
#include "OCRUtility.h"
#include "OCRFilter.h"

#include <fpdfview.h>

#include <iostream>


namespace DocEngine::Parser
{
    bool PDFParser::ParseDocument(const std::string& FilePath, Core::Document& OutDocument)
	{
        //페이지 로드
        PDFDocumetLoader Loader;

        if (!Loader.LoadDocument(FilePath))
        {
            return false;
        }

        OutDocument.DocumentType = Core::EDocumentType::PDF;

        //parse page
        PDFPageParser PageParser;

        int PageCount = Loader.GetPageCount();

        //OCR::TesseractOCRProcessor OCRProcessor;

       // OCR::OCRBlockBuilder OCRBuilder(&OCRProcessor);

        OCR::OCRUtility OCRUtil;
        OCR::OCRFilter Filter;

        for (int PageIndex = 0; PageIndex < PageCount; ++PageIndex)
        {
            /*if (PageIndex < 3)
            {
				PDFPageRenderer Renderer;

				Renderer.RenderPageToImage(Loader.GetDocument(), PageIndex, "page_" + std::to_string(PageIndex) + ".png");
            }*/

            //페이지 생성
           FPDF_PAGE PdfPage = Loader.LoadPage(PageIndex);

            if (!PdfPage)
            {
                continue;
            }

            Core::DocumentPage Page = PageParser.ParsePage(PdfPage, PageIndex);

            //이미지인 부분 추출
            PDFImageExtractor ImageExtractor;

            auto ImageBlocks = ImageExtractor.ExtractImages(Loader.GetDocument(), PageIndex);

            for (auto& Block : ImageBlocks)
            {
                // ImageBlock 추가
                Page.ImageBlocks.push_back(Block);

                // OCR 수행
                std::shared_ptr<Core::OCRBlock> OCRBlock;

                if (Filter.ShouldRunOCR(Block))
                {
                    if (OCRUtil.BuildOCRBlockFromImage(Block, OCRBlock))
                    {
                        Page.OCRBlocks.push_back(OCRBlock);
                    }
                }
            }

            OutDocument.Pages.push_back(Page);

            Loader.ClosePage(PdfPage);
        }

        //Loader.UnloadDocument();

		return true;
	}


}