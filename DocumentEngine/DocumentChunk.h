#pragma once

#include <string>
#include <vector>

namespace DocEngine::Core
{
	class DocumentBlock;

	class DocumentChunk
	{
	public:
		int ChunkIndex = 0;

		std::string ChunkId;
		std::string Text;
		std::string SectionName;

		int StartPage = 0;
		int EndPage = 0;

		size_t TokenCount = 0;
		size_t CharacterCount = 0;

		std::vector<DocumentBlock*> SourceBlocks;
	};
}