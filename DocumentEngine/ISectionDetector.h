#pragma once

namespace DocEngine::Core
{
	class Document;
}

namespace DocEngine::Interface
{
	class ISectionDetector
	{
	public:
		virtual ~ISectionDetector() = default;
	public:
		virtual bool DetectSections(Core::Document& Document) = 0;
	};
}