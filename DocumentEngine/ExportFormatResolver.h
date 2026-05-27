#pragma once

#include <string>

#include "ExportFormatType.h"

namespace DocEngine::Exporter
{
	class ExportFormatResolver
	{
	public:
		static Core::EExportFormatType ResolveExportFormat(const std::string& OutputPath);
	};
}



