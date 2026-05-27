#pragma once

#include <vector>
#include "DocumentPage.h"
#include "DocumentSection.h"
#include "DocumentChunk.h"
#include "DocumentType.h"

namespace DocEngine::Core
{
	class Document
	{
	public:
		std::vector<DocumentPage> Pages;
		std::vector<DocumentSection> Sections;
		std::vector<DocumentChunk> Chunks;
		EDocumentType DocumentType = EDocumentType::Unknown;
	};
}