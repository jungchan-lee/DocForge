#pragma once

#include <string>

namespace DocEngine::Interface
{
	class IOCRProcessor
	{
	public:
		virtual ~IOCRProcessor() = default;

	public:
		virtual bool ExtractTextFromImage(const std::string& ImagePath, std::string& OutText) = 0;
	};
}