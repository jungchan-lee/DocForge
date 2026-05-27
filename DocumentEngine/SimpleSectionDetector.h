#pragma once

#include <string>

#include "ISectionDetector.h"
namespace DocEngine::Section
{
	class SimpleSectionDetector : public Interface::ISectionDetector
	{
	public: 
		virtual bool DetectSections(Core::Document& Document) override;

	private:
		bool IsSectionTitle(const std::string& Text) const;
	};
}



