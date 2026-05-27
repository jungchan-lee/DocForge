#pragma once

#include <memory>

namespace DocEngine::Core
{
	class ImageBlock;
}

namespace DocEngine::OCR
{
	class OCRFilter
	{
	public:
		bool ShouldRunOCR(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const;

	private:
		bool IsTooSmall(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const;
		bool IsLikelyTextImage(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const;

		float CalculateScore(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const;

		float EdgeScore(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const;
		float SizeScore(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const;
		float ShapeScore(const std::shared_ptr<Core::ImageBlock>& ImageBlock) const;
	};
}



