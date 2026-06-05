#include "TesseractOCRProcessor.h"

#include <cstring>

namespace DocEngine::OCR
{
    TesseractOCRProcessor::TesseractOCRProcessor()
    {
        // 언어: 영어 + 한글
        TessAPI.Init(
            "C:\\Program Files\\Tesseract-OCR\\tessdata",
            "eng+kor"
        );

        TessAPI.SetPageSegMode(tesseract::PSM_AUTO_OSD);
        TessAPI.SetVariable("preserve_interword_spaces", "1");
    }

    TesseractOCRProcessor::~TesseractOCRProcessor()
    {
        TessAPI.End();
    }

    bool TesseractOCRProcessor::ExtractTextFromBitmap(FPDF_BITMAP Image, std::string& OutText)
    {
        if (!Image)
        {
            return false;
        }

        // PDFium bitmap 정보
        const int Width = FPDFBitmap_GetWidth(Image);
        const int Height = FPDFBitmap_GetHeight(Image);
        const int Stride = FPDFBitmap_GetStride(Image);

        unsigned char* Buffer = static_cast<unsigned char*>(FPDFBitmap_GetBuffer(Image));

        if (!Buffer)
        {
            return false;
        }

        // PDFium bitmap 직접 OCR 입력
        TessAPI.SetImage(
            Buffer,
            Width,
            Height,
            4,          // bytes per pixel
            Stride);

        char* Text = TessAPI.GetUTF8Text();

        if (!Text)
        {
            return false;
        }

        OutText = Text;

        //delete[] Text;

        return true;
    }
    bool TesseractOCRProcessor::ExtractTextFromImage(const std::string& ImagePath, std::string& OutText)
    {
        Pix* Image = pixRead(ImagePath.c_str());

        if (!Image)
        {
            return false;
        }

        TessAPI.SetImage(Image);

        char* Text = TessAPI.GetUTF8Text();

        if (!Text)
        {
            pixDestroy(&Image);
            return false;
        }

        OutText = Text;

        //delete[] Text;

        pixDestroy(&Image);

        return true;
    }
}