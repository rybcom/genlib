#include "genlib.h"
#include "filewriter.h"


struct ModelProperty
{
	std::string name;
	std::string type;
};

struct PropertyModelClass
{
	std::string name;
	std::vector<ModelProperty> properties;
};

PropertyModelClass c;
std::vector<PropertyModelClass> modelClasses;



void declare_class_model()
{

#define START_MODEL_CLASS(classname)c ={}; c.name = #classname
#define END_MODEL_CLASS() modelClasses.push_back(c);
#define ADD_PROPERTY(propname,proptype) c.properties.push_back({#propname,#proptype});

#include "ObjectDomainModel.model"
}

#define CONTENT(type,name) type & name = *(new type())

void create_state_header(std::string_view outputFile)
{
	HeaderFile headerFile_state;

	Include includeFile;
	includeFile.file = "PropertyModelDeclaration.h";
	includeFile.useBrackets = false;
	headerFile_state.addContent(includeFile);

	Include includeDescriptors;
	includeDescriptors.file = "ModelDescriptors.h";
	includeDescriptors.useBrackets = false;
	headerFile_state.addContent(includeDescriptors);

	for (auto const & modelclass : modelClasses)
	{

	
		CONTENT(StructType, state);
		state.name = modelclass.name + "State";

		for (auto const & prop : modelclass.properties)
		{
			CONTENT(PropertyType, propType);
			propType.name = prop.name;
			propType.type = prop.type;

			state.addContent(propType);
		}

		CONTENT(Function_UpdateProperty, updateFun);
		updateFun.paramType = modelclass.name + "Descriptor const &";

		for (auto const & prop : modelclass.properties)
		{
			updateFun.props.push_back(prop.name);
		}

		state.addContent(updateFun);

		headerFile_state.addContent(state);
	}

	Printer::getPrinter().clear();
	headerFile_state.process();

	FileWriter fileWriter;
	fileWriter.setContent(Printer::getPrinter().getContent());
	fileWriter.writeToFile(outputFile);
}

void create_desc_header(std::string_view outputFile)
{
	HeaderFile headerFile_desc;

	for (auto const & modelclass : modelClasses)
	{

		CONTENT(StructType, desc);
		desc.name = modelclass.name + "Descriptor";

		CONTENT(FlagStruct, flags);
		flags.name = "Fields";
		flags.type = "short";
		flags.nameOfInstance = "used";

		for (auto const & prop : modelclass.properties)
		{
			CONTENT(MemberType, member);
			member.name = prop.name;
			member.type = prop.type;

			desc.addContent(member);
			flags.addFlag(prop.name);

		}

		desc.addContent(flags);
		headerFile_desc.addContent(desc);
	}

	Printer::getPrinter().clear();
	headerFile_desc.process();

	FileWriter fileWriter;
	fileWriter.setContent(Printer::getPrinter().getContent());
	fileWriter.writeToFile(outputFile);
}


int main()
{
	declare_class_model();

	create_desc_header(R"(..\test\cpp_test_project\include\ModelDescriptors.h)");

	create_state_header(R"(..\test\cpp_test_project\include\ModelStates.h)");
}