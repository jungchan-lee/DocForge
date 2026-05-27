#pragma once

#include <string>

#include "BlockType.h"

namespace DocEngine::Core
{
	class BlockTypeUtility
	{
	public:
		static std::string ToString(EBlockType Type);
	};
}


