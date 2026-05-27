#include "TesseractOCRProcessor.h"

namespace DocEngine::OCR
{
    TesseractOCRProcessor::TesseractOCRProcessor()
    {
        // 언어: 영어 + 한글
        TessAPI.Init(
            "C:\\Program Files\\Tesseract-OCR\\tessdata",
            "eng+kor"
        );

        TessAPI.SetPageSegMode(tesseract::PSM_AUTO);
        TessAPI.SetVariable("preserve_interword_spaces", "1");
    }

    TesseractOCRProcessor::~TesseractOCRProcessor()
    {
        TessAPI.End();
    }

    bool TesseractOCRProcessor::ExtractTextFromImage(const std::string& ImagePath, std::string& OutText)
    {
        Pix* image = pixRead(ImagePath.c_str());

        if (!image)
            return false;

        TessAPI.SetImage(image);

        char* text = TessAPI.GetUTF8Text();

        if (!text)
        {
            pixDestroy(&image);
            return false;
        }

        OutText = text;

        delete[] text;
        pixDestroy(&image);

        return true;
    }
}