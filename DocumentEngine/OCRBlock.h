#pragma once

#include "DocumentBlock.h"

namespace DocEngine::Core
{
	class OCRBlock : public DocumentBlock
	{
	public:
		OCRBlock()
		{
			BlockType = EBlockType::OCR;
		}

		virtual std::string GetText() const override
		{
			return Text;
		}

		std::string Text;

	};
}