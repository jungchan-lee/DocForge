#pragma once

#include <string>


namespace DocEngine::Core
{
	class Document;
}

namespace DocEngine::Parser
{
	class DOCXXMLParser
	{
	public:
		//xml 파일을 파싱하여 Document 객체로 변환
		bool ParseDocumentXML(
			const std::string& XMLPath,
			DocEngine::Core::Document& OutDocument);
	};
}


