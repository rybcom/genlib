#pragma once

#include "printer.h"
#include <vector>

struct Content
{
	void addContent(Content & ref)
	{
		m_items.emplace_back(ref);
	}

	virtual void process()
	{
		for (auto const & item : m_items)
		{
			item.get().process();
		}
	}

protected:

	std::vector<std::reference_wrapper<Content>> m_items;

};

struct Include : public Content
{
	std::string file;
	bool useBrackets = false;

	virtual void process() override
	{
		if (useBrackets)
		{
			print_line(fmt::format("#include <{}>", file));
		}
		else
		{
			print_line(fmt::format("#include \"{}\"", file));
		}
		Content::process();
	}
};


struct HeaderFile : public Content
{
	virtual void process() override
	{
		print_line("#pragma once");
		print_newemptyline();
		Content::process();
	}
};

struct ClassType : public Content
{
	std::string name;
	virtual void process() override
	{
		print_newemptyline();
		print_line(fmt::format("class {}", name));
		print_line("{");
		add_printer_offset();
		Content::process();
		remove_printer_offset();
		print_line("};");
	}
};

struct StructType : public Content
{
	std::string name;
	virtual void process() override
	{
		print_newemptyline();
		print_line(fmt::format("struct {}", name));
		print_line("{");
		add_printer_offset();
		Content::process();
		remove_printer_offset();
		print_line("};");
	}
};

struct MemberType : public Content
{
	std::string name;
	std::string type;

	virtual void process() override
	{
		print_line(fmt::format("{} {};", type, name));
	}

};


struct PropertyType : public Content
{
	std::string name;
	std::string type;

	virtual void process() override
	{
		print_line(fmt::format("define_property({},{});", name, type));
	}

};

struct Function_OneParam : public Content
{
	std::string name;
	std::string returntype = "void";
	std::string paramName;
	std::string paramType;

	virtual void process() override
	{
		print_newemptyline();
		print_line(fmt::format("{} {}({}{})",returntype,name,paramType,paramName));
		print_line("{");
		add_printer_offset();
		Content::process();
		remove_printer_offset();
		print_line("}");
	}
};


struct Function_UpdateProperty: public Content
{
	std::string paramType;
	std::vector<std::string> props;

	virtual void process() override
	{
		print_newemptyline();
		print_line(fmt::format("void update({} desc)", paramType));
		print_line("{");
		add_printer_offset();

		for (auto const & prop : props)
		{
			print_line(fmt::format("update_property({});", prop));
		}

		remove_printer_offset();
		print_line("}");
	}
};


struct FlagStruct : public Content
{
	std::string type;
	std::string name;
	std::string nameOfInstance;
	bool allOption = true;

	void addFlag(std::string const & flag)
	{
		m_flags.emplace_back(flag);
	}

	virtual void process() override
	{
		print_line(fmt::format("struct {}", name));
		print_line("{");
		add_printer_offset();
		print_line(fmt::format("unsigned {} {};", type, getBitFields()));
		printConstructor();
		remove_printer_offset();
		print_line(fmt::format("}} {};",nameOfInstance));
	}
private:

	std::vector<std::string> m_flags;

	std::string getBitFields()
	{
		std::string result;

		bool first = true;
		for (auto & flag : m_flags)
		{
			if (first == false)
			{
				result = result.append(",");
			}
			first = false;
			result = result.append(fmt::format("{}:1", flag));
		}

		return result;
	}


	void printConstructor()
	{
		print_line(fmt::format("{}()", name));
		print_line("{");
		add_printer_offset();
		for (auto & flag : m_flags)
		{
			print_line(fmt::format("{} = true;", flag));
		}
		remove_printer_offset();
		print_line("}");
	}

};


