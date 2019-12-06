#pragma once
#include <string>
#include <iostream>
#include <fstream>

class FileWriter
{

public:

	void setContent(std::string_view content)
	{
		m_content = content;
	}

	void writeToFile(std::string_view filePath)
	{
		std::ofstream os;
		os.open(std::string(filePath));

		os << m_content;

		os.close();
	}

private:

	std::string m_content;
};