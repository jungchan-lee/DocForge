#include "ExportFormatResolver.h"


namespace DocEngine::Exporter
{
	Core::EExportFormatType ExportFormatResolver::ResolveExportFormat(const std::string& OutputPath)
	{
		if (OutputPath.ends_with(".txt"))
		{
			return Core::EExportFormatType::TXT;
		}

		if (OutputPath.ends_with(".json"))
		{
			return Core::EExportFormatType::JSON;
		}

		if (OutputPath.ends_with(".md"))
		{
			return Core::EExportFormatType::Markdown;
		}

		return Core::EExportFormatType::Unknown;
	}
}