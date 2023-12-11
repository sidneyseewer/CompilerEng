#include "SymbolTable.h"
#include "Types/BaseType.h"
#include "Types/StringType.h"
#include "Types/Type.h"
#include "Types/TypeKind.h"
#include "lib/Singelton.h"
#include "stdio.h"

#include "SymbolTable.h"

#include "Parser.h"
#include "Scanner.h"
#include "SymbolFactory.h"
#include <limits>
#include <memory>
#include <string>
#include <sys/timeb.h>
#include <utility>
#include <vector>
#include <wchar.h>
#include <iostream>

#include <format>

class ParamFactory : public Singelton<ParamFactory> {
public:
void PrintThis() { std::cout << "this:" << this << std::endl; }
private:
friend class Singelton<ParamFactory> ; //necessary for SingletonBase to construct a ParamF
ParamFactory(int const x) { std::cout << this << std::endl << x << std::endl; };
ParamFactory(int const x, int const y) { std::cout << this << std::endl << x << "," << y << std::endl; };
};

int main(int argc, char *argv[]) {
  if (argc >= 5) {
    wchar_t *inputFile = coco_string_create(argv[2]);
    wchar_t *outputFile = coco_string_create(argv[4]);
    printf("Inputfile: %ls\n", inputFile);
    printf("Outputfile: %ls\n", outputFile);
    MIEC::Scanner *scanner = new MIEC::Scanner(inputFile);
    MIEC::Parser *parser = new MIEC::Parser(scanner);
    //		parser->tab = new MIEC::SymbolTable(parser);
    //		parser->gen = new MIEC::CodeGenerator();
    parser->Parse();
    if (parser->errors->count == 0) {
      printf("No errors detected!");
    } else {
      printf("%d errors detected", parser->errors->count);
    }

    coco_string_delete(inputFile);
    //		delete parser->gen;
    //		delete parser->tab;
    delete parser;
    delete scanner;

  } else {
    printf("File could not be read \n");
  }
  enum Ts{Type,Var,Const};
  std::vector<std::pair<std::string,Ts >> input{
    {"integer",Type},
    {"x",Var},
    {"y",Var},
    {"z",Var},
    {"4711",Const},
    {"11.0",Const}
  };
// 	auto s1=sf.CreateType("integer");
// 	auto s2=sf.CreateVar("x", TypeKind::INT);
// 	auto s3=sf.CreateVar("y", TypeKind::INT);
// 	auto s4=sf.CreateVar("z", TypeKind::INT);
// 	auto s5=sf.CreateConst("4711");
// 	auto s6=sf.CreateConst("11.0");


std::unordered_map<std::string, int> symbols;

symbols.contains("as");
symbols["as"]=12;
symbols.contains("as");
symbols["as"];

  SymbolFactory &sf = SymbolFactory::GetInstance();
  SymbolTable &st = SymbolTable::GetInstance();

for(auto itr=input.cbegin();itr!=input.cend();itr++)
{
	auto name=itr->first;
	switch (itr->second) {
	case Type:
	if(st.Find(name)!=nullptr)
	{
		st.Add(sf.CreateType(name));
	}
	break;
	case Var:
	if(st.Find(name)!=nullptr)
	{
		st.Add(sf.CreateVar(name,FLOAT));
	}
	break;
	case Const:
	if(st.Find(name)!=nullptr)
	{
		st.Add(sf.CreateConst(name));
	}
	break;
	}
}
std::string s=std::format("{}",std::numeric_limits<float>::max()+2);

	
  return 0;
}

// int main(int argc, char** argv)
// {
// 	if (argc >= 5) {
// 		for (int i = 1; i < argc; i++) {
// 			printf("Arg 1: ", argc[i])
// 		}
// 	}
// 	if (argc >= 5) {
// 		wchar_t* inputFileName;
// 		wchar_t* outputFileName;
// 		// Loop through command-line arguments
// 		for (int i = 1; i < argc; i++) {
// 			if (wcscmp(wargv[i], L"-in") == 0 && i + 1 < argc) {
// 				// Extract input file information
// 				inputFileName = wargv[i + 1];
// 				printf("Input file: %ls\n", inputFileName);
// 				//std::wcout << L"Input file: " << inputFileName <<
// std::endl;
// 			}
// 			if (wcscmp(wargv[i], L"-out") == 0 && i + 1 < argc) {
// 				// Extract output file information
// 				outputFileName = wargv[i + 1];
// 				printf("Output file: %ls\n", outputFileName);
// 				//std::wcout << L"Output file: " << outputFileName <<
// std::endl;
// 			}
// 		}
// 		printf("Input file: %ls\n", inputFileName);
// 		printf("Output file: %ls\n", outputFileName);
// 		MIEC::Scanner* scanner = new
// MIEC::Scanner((wchar_t*)inputFileName); 		MIEC::Parser* parser = new
// MIEC::Parser(scanner);
// 		//		parser->tab = new MIEC::SymbolTable(parser);
// 		//		parser->gen = new MIEC::CodeGenerator();
// 		parser->Parse();
// 		if (parser->errors->count == 0) {
// 			printf("No errors detected!");
// 		}
// 		else {
// 			printf("%d errors detected", parser->errors->count);
// 		}

// 		coco_string_delete(inputFileName);
// 		//		delete parser->gen;
// 		//		delete parser->tab;
// 		delete parser;
// 		delete scanner;
// 	}
// 	else {
// 		printf("-- No source file specified\n");
// 	}
// 	if (argc == 2) {
// 		wchar_t* fileName = coco_string_create(argv[1]);
// 		MIEC::Scanner* scanner = new MIEC::Scanner(fileName);
// 		MIEC::Parser* parser = new MIEC::Parser(scanner);
// //		parser->tab = new MIEC::SymbolTable(parser);
// //		parser->gen = new MIEC::CodeGenerator();
// 		parser->Parse();
// 		if (parser->errors->count == 0) {
// 			printf("No errors detected!");
// 		}
// 		else {
// 			printf("%d errors detected", parser->errors->count);
// 		}

// 		coco_string_delete(fileName);
// //		delete parser->gen;
// //		delete parser->tab;
// 		delete parser;
// 		delete scanner;
// 	}
// 	else
// 		printf("-- No source file specified\n");

//   return 0;
// }
