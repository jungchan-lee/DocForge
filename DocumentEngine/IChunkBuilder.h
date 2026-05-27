#pragma once

namespace DocEngine::Core
{
	class Document;
}

namespace DocEngine::Interface
{
	class IChunkBuilder
	{
	public:
		virtual ~IChunkBuilder() = default;

	public:
		virtual bool BuildChunks(Core::Document& Document) = 0;
	};
}