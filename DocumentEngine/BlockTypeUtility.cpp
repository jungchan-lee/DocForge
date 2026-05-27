#include "BlockTypeUtility.h"


namespace DocEngine::Core
{
	std::string BlockTypeUtility::ToString(EBlockType Type)
	{
        switch (Type)
        {
        case EBlockType::Text:
            return "Text";

        case EBlockType::Image:
            return "Image";

        case EBlockType::OCR:
            return "OCR";

        case EBlockType::Table:
            return "Table";

        default:
            return "Unknown";
        }
	}
}