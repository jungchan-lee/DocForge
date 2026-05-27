#pragma once

#include "IChunkBuilder.h"

namespace DocEngine::Chunk
{
	class FixedSizeChunkBuilder : public Interface::IChunkBuilder
	{
	public:
		FixedSizeChunkBuilder(size_t InChunkSize = 1000, size_t InOverlapSize = 200);

		virtual bool BuildChunks(Core::Document& Document) override;

	private:
		size_t ChunkSize;
		size_t OverlapSize;
	};
}


