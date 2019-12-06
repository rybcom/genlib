#include <sstream>
#include <iostream>
#include <string>
#include <fmt/core.h>
#include <fmt/color.h>

struct Printer
{
	static Printer& getPrinter()
	{
		static Printer printer;
		return printer;
	}

	void printLine(std::string_view text)
	{
		m_ss << getLineOffset() << text << "\n";
	}

	void printEmptyLine()
	{
		m_ss << "\n";
	}

	std::string getContent()
	{
		return m_ss.str();
	}

	void clear()
	{
		m_ss.str("");
	}

	void addOffset(std::size_t offset)
	{
		m_offset += offset;
	}
	void removeOffset(std::size_t offset)
	{
		m_offset -= offset;
		if (m_offset < 0)
		{
			m_offset = 0;
		}
	}


private:

	std::string getLineOffset()
	{
		std::string result;
		for (int i = 0; i < m_offset; i++)
		{
			result.append(" ");
		}

		return result;
	}

	std::size_t m_offset = 0;
	std::stringstream m_ss;
};




template<typename Container>
void print_collection(Container & container)
{
	for (auto & item : container)
	{
		item.print();
	}
}

void print_newemptyline()
{
	Printer::getPrinter().printEmptyLine();
}

void print_line(std::string_view text)
{
	Printer::getPrinter().printLine(text);
}

void print_pragma_once()
{
	Printer::getPrinter().printLine("#pragma once");
}

void add_printer_offset(std::size_t offset)
{
	Printer::getPrinter().addOffset(offset);
}


void remove_printer_offset(std::size_t offset)
{
	Printer::getPrinter().removeOffset(offset);
}

static constexpr size_t tab_size = 3;

void add_printer_offset()
{
	add_printer_offset(tab_size);
}

void remove_printer_offset()
{
	remove_printer_offset(tab_size);
}
