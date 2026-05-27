#pragma once

#include <string.h>
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
	};
}