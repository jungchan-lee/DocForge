#pragma once

#include <string.h>
#include <fpdfview.h>

#include "DocumentBlock.h"

namespace DocEngine::Core
{
	class ImageBlock : public DocumentBlock
	{
	public:
		ImageBlock()
		{
			BlockType = EBlockType::Image;
		}

	public:
		std::string ImagePath;

		bool bRequiresOCR = true;

		int Width = 0;
		int Height = 0;
		bool bHasTextLikeFeatures;
		float EdgeDensity;
		bool bIsEmbeddedFontLikeImage;

		float Left = 0.0f;
		float Top = 0.0f;
		float Right = 0.0f;
		float Bottom = 0.0f;

	};
}