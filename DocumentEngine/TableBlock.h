#pragma once

#include "DocumentBlock.h"

namespace DocEngine::Core
{
	class TableBlock : public DocumentBlock
	{
	public:
		TableBlock()
		{
			BlockType = EBlockType::Table;
		}
	};
}