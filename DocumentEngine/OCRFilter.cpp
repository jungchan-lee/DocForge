#include "OCRFilter.h"

#include "ImageBlock.h"

namespace DocEngine::OCR
{
    bool OCRFilter::ShouldRunOCR(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const
    {
        if (!ImageBlock)
            return false;

        if (IsTooSmall(ImageBlock))
            return false;

        if (IsLikelyTextImage(ImageBlock))
            return true;

        return false;


        float Score = CalculateScore(ImageBlock);

        return Score > 60.0f; // threshold
    }

    bool OCRFilter::IsTooSmall(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const
    {
        // 너무 작은 이미지 (아이콘/로고) 제외
        return ImageBlock->Width < 50 || ImageBlock->Height < 50;
    }

    bool OCRFilter::IsLikelyTextImage(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const
    {
        // 1차 heuristic (나중에 개선 가능)
        return ImageBlock->Width > 200 && ImageBlock->Height > 80;
    }
    float OCRFilter::CalculateScore(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const
    {
        float Score = 0.0f;

        //Score += EdgeScore(ImageBlock);
        Score += SizeScore(ImageBlock);
        Score += ShapeScore(ImageBlock);

        return Score;
    }
    float OCRFilter::EdgeScore(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const
    {
        float density = ImageBlock->EdgeDensity; // 나중에 추가

        if (density > 0.6f) return 50.0f;
        if (density > 0.3f) return 30.0f;

        return 5.0f;
    }
    float OCRFilter::SizeScore(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const
    {
        int w = ImageBlock->Width;
        int h = ImageBlock->Height;

        if (w < 50 || h < 50)
            return 0.0f;

        if (w > 300 && h > 80)
            return 20.0f;

        return 10.0f;
    }
    float OCRFilter::ShapeScore(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const
    {
        float ratio = (float)ImageBlock->Width / (float)ImageBlock->Height;

        // 문서 형태 (가로로 긴 박스)
        if (ratio > 2.0f && ratio < 6.0f)
            return 20.0f;

        return 5.0f;
    }
}
