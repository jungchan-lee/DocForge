#include "FileTypeResolver.h"

#include <filesystem>
#include <algorithm>
#include <cctype>

namespace DocEngine::Parser
{
	Core::EDocumentType FileTypeResolver::ResolveFileType(const std::string& FilePath)
	{
        /*if (FilePath.ends_with(".pdf"))
        {
            return Core::EDocumentType::PDF;
        }

        if (FilePath.ends_with(".docx"))
        {
            return Core::EDocumentType::DOCX;
        }

        if(FilePath.ends_with(".png"))
        {
            return Core::EDocumentType::PNG;
		}
        
        if (FilePath.ends_with(".jpg"))
        {
			return Core::EDocumentType::JPG;
        }

        if (FilePath.ends_with(".jpeg"))
        {
            return Core::EDocumentType::JPEG;
        }


        return Core::EDocumentType::Unknown;*/
	    
        std::filesystem::path Path(FilePath);

        std::string Extension =
            Path.extension().string();

        std::transform(
            Extension.begin(),
            Extension.end(),
            Extension.begin(),
            [](unsigned char c)
            {
                return std::tolower(c);
            });

        if (Extension == ".pdf")
        {
            return Core::EDocumentType::PDF;
        }

        if (Extension == ".docx")
        {
            return Core::EDocumentType::DOCX;
        }

        if (Extension == ".png")
        {
            return Core::EDocumentType::PNG;
        }

        if (Extension == ".jpg")
        {
            return Core::EDocumentType::JPG;
        }

        if (Extension == ".jpeg")
        {
            return Core::EDocumentType::JPEG;
        }

        return Core::EDocumentType::Unknown;
    
    }
}