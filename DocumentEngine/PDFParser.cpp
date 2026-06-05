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
        // PDF 로드
        PDFDocumetLoader Loader;

        if (!Loader.LoadDocument(FilePath))
        {
            return false;
        }

        OutDocument.DocumentType = Core::EDocumentType::PDF;
        PDFPageRenderer Renderer;

        PDFPageParser PageParser;

        const int PageCount = Loader.GetPageCount();

        // OCR 시스템
        OCR::OCRUtility OCRUtil;
        OCR::OCRFilter OCRFilter;

        for (int PageIndex = 0; PageIndex < PageCount; ++PageIndex)
        {
            // PDF 페이지 로드
            FPDF_PAGE PdfPage = Loader.LoadPage(PageIndex);

            if (!PdfPage)
            {
                continue;
            }

            // =========================
            // 1. TEXT BLOCK 추출
            // =========================
            Core::DocumentPage Page = PageParser.ParsePage(PdfPage, PageIndex);

            // =========================
            // 2. IMAGE BLOCK 추출
            // =========================
            PDFImageExtractor ImageExtractor;
            // =====================
            // IMAGE 탐지
            // =====================

            auto ImageBlocks =
                ImageExtractor.ExtractImages(
                    PdfPage,
                    PageIndex);

            for (auto& ImageBlock : ImageBlocks)
            {
                if (!ImageBlock)
                {
                    continue;
                }

                Page.ImageBlocks.push_back(
                    ImageBlock);

                // =====================
                // OCR 필터
                // =====================

                if (!OCRFilter.ShouldRunOCR(
                    ImageBlock))
                {
                    continue;
                }

                // =====================
                // OCR용 bitmap 렌더
                // =====================

                FPDF_BITMAP OCRBitmap =
                    Renderer.RenderRegionToBitmap(
                        PdfPage,
                        ImageBlock->Left,
                        ImageBlock->Top,
                        ImageBlock->Right,
                        ImageBlock->Bottom);

                if (!OCRBitmap)
                {
                    continue;
                }

                // =====================
                // OCR 수행
                // =====================

                std::shared_ptr<Core::OCRBlock>
                    OCRBlock;

                bool bSuccess =
                    OCRUtil.BuildOCRBlockFromBitmap(
                        OCRBitmap,
                        ImageBlock,
                        OCRBlock);

                // bitmap 메모리 해제
                FPDFBitmap_Destroy(OCRBitmap);

                if (!bSuccess)
                {
                    continue;
                }

                if (!OCRBlock)
                {
                    continue;
                }

                Page.OCRBlocks.push_back(
                    OCRBlock);
            }
            //auto ExtractedImages = ImageExtractor.ExtractImages(PdfPage, PageIndex);

            //for (auto& Extracted : ExtractedImages)
            //{
            //    auto ImageBlock = Extracted.ImageBlock;

            //    FPDF_BITMAP Bitmap = Extracted.Bitmap;

            //    if (!ImageBlock || !Bitmap)
            //    {
            //        continue;
            //    }

            //    // ImageBlock 저장
            //    Page.ImageBlocks.push_back(ImageBlock);

            //    // OCR 필터
            //    if (!OCRFilter.ShouldRunOCR(ImageBlock))
            //    {
            //        FPDFBitmap_Destroy(Bitmap);
            //        continue;
            //    }

            //    // OCR 수행
            //    std::shared_ptr<Core::OCRBlock>
            //        OCRBlock;

            //    bool bOCRSuccess = OCRUtil.BuildOCRBlockFromImage( Bitmap,ImageBlock,OCRBlock);

            //    // Bitmap 메모리 해제
            //    FPDFBitmap_Destroy(Bitmap);

            //    if (!bOCRSuccess)
            //    {
            //        continue;
            //    }

            //    if (!OCRBlock)
            //    {
            //        continue;
            //    }

            //    // OCR 결과 저장
            //    Page.OCRBlocks.push_back(OCRBlock);
            //}

            // 페이지 저장
            OutDocument.Pages.push_back(Page);

            // 페이지 해제
            Loader.ClosePage(PdfPage);
        }

        return true;
	}


}