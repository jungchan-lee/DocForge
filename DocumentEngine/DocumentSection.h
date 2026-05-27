#pragma once

#include <string>
#include <vector>

namespace DocEngine::Core
{
	class DocumentBlock;
	class DocumentChunk;

	class DocumentSection
	{
	public:
		std::string SectionName;
		std::vector<DocumentBlock*> Blocks;

	public:
		std::string Title;

		int StartPage = 0;
		int EndPage = 0;

		std::vector<DocumentChunk*> Chunks;
	};
}