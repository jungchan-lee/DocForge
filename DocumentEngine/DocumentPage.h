#pragma once

#include <memory>
#include <vector>

#include "DocumentBlock.h"

namespace DocEngine::Core
{
	class DocumentPage
	{
	public:
		int PageIndex = 0;
		std::vector<std::shared_ptr<DocumentBlock>> TextBlocks;
		std::vector<std::shared_ptr<DocumentBlock>> ImageBlocks;
		std::vector<std::shared_ptr<DocumentBlock>> OCRBlocks;
		std::vector<std::shared_ptr<Core::DocumentBlock>> GetAllTextLikeBlocks() const
		{
			std::vector<std::shared_ptr<Core::DocumentBlock>> Result;

			Result.insert(Result.end(), TextBlocks.begin(), TextBlocks.end());
			Result.insert(Result.end(), OCRBlocks.begin(), OCRBlocks.end());

			return Result;
		};
	};
}