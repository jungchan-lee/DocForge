#include "JSONUtility.h"

namespace DocEngine::Exporter
{
	std::string JSONUtility::EscapeJSONString(const std::string& Input)
	{
		std::string Result;

		for (char Character : Input)
		{
			switch (Character)
			{
			case '\"':
				Result += "\\\"";
				break;

			case '\\':
				Result += "\\\\";
				break;

			case '\n':
				Result += "\\n";
				break;

			case '\r':
				Result += "\\r";
				break;

			case '\t':
				Result += "\\t";
				break;

			default:
				Result += Character;
				break;
			}
		}

		return Result;
	}
	std::string JSONUtility::DocumentTypeToString(Core::EDocumentType Type)
	{
		switch (Type)
		{
		case Core::EDocumentType::PDF:
			return "PDF";

		case Core::EDocumentType::DOCX:
			return "DOCX";

		case Core::EDocumentType::PNG:
			return "PNG";

		case Core::EDocumentType::JPG:
			return "JPG";

		case Core::EDocumentType::JPEG:
			return "JPEG";

		default:
			return "Unknown";
		}
	}
}