#pragma once

#include <string>

#include "BlockType.h"
#include "Rect.h"
#include "MetadataTypes.h"

namespace DocEngine::Core
{
	class DocumentBlock
	{
	public:
		virtual ~DocumentBlock() = default;

		virtual std::string GetText() const { return ""; }

	public:
		EBlockType BlockType = EBlockType::Text;
		Rect Bounds;
		Metadata BlockMetadata;

		int PageIndex = 0;
	};
}
