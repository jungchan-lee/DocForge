#include "DOCXArchive.h"

#include <iostream>
#include <filesystem>

#include <miniz.h>

namespace FileSystem = std::filesystem;

namespace DocEngine::Parser
{
	bool DOCXArchive::ExtractArchive(const std::string& FilePath, const std::string& OutputDirectory)
	{
        mz_zip_archive ZipArchive{};

        if (!mz_zip_reader_init_file(&ZipArchive, FilePath.c_str(), 0))
        {
            std::cout << "Failed to open DOCX archive\n";

            return false;
        }

        FileSystem::create_directories(OutputDirectory);

        int FileCount = (int)mz_zip_reader_get_num_files(&ZipArchive);

        for (int i = 0; i < FileCount; ++i)
        {
            mz_zip_archive_file_stat FileStat{};

            if (!mz_zip_reader_file_stat(&ZipArchive, i, &FileStat))
            {
                continue;
            }

            std::string FileName = FileStat.m_filename;

            std::string OutputPath = OutputDirectory + "/" + FileName;

            if (mz_zip_reader_is_file_a_directory(&ZipArchive, i))
            {
                FileSystem::create_directories(OutputPath);

                continue;
            }

            FileSystem::create_directories(FileSystem::path(OutputPath).parent_path());

            if (!mz_zip_reader_extract_to_file(&ZipArchive, i, OutputPath.c_str(), 0))
            {
                std::cout << "Failed to extract: " << FileName << "\n";
            }
        }

        mz_zip_reader_end(&ZipArchive);

        return true;
	}
}