#pragma once

#include "DocumentBlock.h"

#include <string>

namespace DocEngine::Core
{
	class TextBlock : public DocumentBlock
	{
	public:
		TextBlock()
		{
			BlockType = EBlockType::Text;
		}

		virtual std::string GetText() const override
		{
			return Text;
		}

	public:
		std::string Text;

	};
}