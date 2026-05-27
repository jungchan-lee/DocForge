#include "FixedSizeChunkBuilder.h"

#include "Document.h"
#include "DocumentPage.h"
#include "DocumentBlock.h"
#include "DocumentChunk.h"

namespace DocEngine::Chunk
{
	FixedSizeChunkBuilder::FixedSizeChunkBuilder(size_t InChunkSize, size_t InOverlapSize) 
        : ChunkSize(InChunkSize)
        , OverlapSize(InOverlapSize)
    {
    }

    bool FixedSizeChunkBuilder::BuildChunks(Core::Document& Document)
	{
        Document.Chunks.clear();

        std::string CurrentText;

        Core::DocumentChunk CurrentChunk;

        int ChunkIndex = 0;

        for (const auto& Page : Document.Pages)
        {
            for (const auto& Block : Page.GetAllTextLikeBlocks())
            {
                if (!Block)
                {
                    continue;
                }

                CurrentText += Block->GetText();
                CurrentText += "\n";

                CurrentChunk.SourceBlocks.push_back(Block.get());

                if (CurrentChunk.SourceBlocks.size() == 1)
                {
                    CurrentChunk.StartPage = Page.PageIndex;
                }

                CurrentChunk.EndPage = Page.PageIndex;

                if (CurrentText.size() >= ChunkSize)
                {
                    CurrentChunk.ChunkIndex = ChunkIndex++;

                    CurrentChunk.Text = CurrentText;

                    CurrentChunk.ChunkId = "chunk_" + std::to_string(CurrentChunk.ChunkIndex);

                    // Metadata
                    CurrentChunk.CharacterCount = CurrentChunk.Text.size();

                    CurrentChunk.TokenCount = CurrentChunk.CharacterCount / 4;

                    Document.Chunks.push_back(CurrentChunk);

                    std::string OverlapText;

                    if (CurrentText.size() > OverlapSize)
                    {
                        OverlapText =
                            CurrentText.substr(CurrentText.size() - OverlapSize);
                    }

                    // 다음 Chunk 준비
                    CurrentChunk = Core::DocumentChunk{};

                    CurrentChunk.StartPage = Page.PageIndex;
                    CurrentChunk.EndPage = Page.PageIndex;

                    CurrentText = OverlapText;
                }
            }
        }

        // 마지막 남은 텍스트 처리
        if (!CurrentText.empty())
        {
            CurrentChunk.ChunkIndex = ChunkIndex++;

            CurrentChunk.Text = CurrentText;

            CurrentChunk.ChunkId = "chunk_" + std::to_string(CurrentChunk.ChunkIndex);

            // Metadata
            CurrentChunk.CharacterCount = CurrentChunk.Text.size();

            CurrentChunk.TokenCount = CurrentChunk.CharacterCount / 4;

            Document.Chunks.push_back(CurrentChunk);
        }

        return true;
	}
}