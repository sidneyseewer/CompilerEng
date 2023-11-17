#include "Stdio.h"

//#include "SymbolTable.h"

#include "Parser.h"
#include "Scanner.h"
#include <sys/timeb.h>
#include <wchar.h>

int main(int argc, char* argv[])
{
	if (argc >= 5) {
		wchar_t* inputFile = coco_string_create(argv[2]);
		wchar_t* outputFile = coco_string_create(argv[4]);
		printf("Inputfile: %ls\n", inputFile);
		printf("Outputfile: %ls\n", outputFile);
		MIEC::Scanner* scanner = new MIEC::Scanner(inputFile);
		MIEC::Parser* parser = new MIEC::Parser(scanner);
		//		parser->tab = new MIEC::SymbolTable(parser);
		//		parser->gen = new MIEC::CodeGenerator();
		parser->Parse();
		if (parser->errors->count == 0) {
			printf("No errors detected!");
		}
		else {
			printf("%d errors detected", parser->errors->count);
		}

		coco_string_delete(inputFile);
		//		delete parser->gen;
		//		delete parser->tab;
		delete parser;
		delete scanner;

	}
	else {
		printf("File could not be read \n");
	}
	return 0;
}


//int main(int argc, wchar_t* wargv[])
//{
//	if (argc >= 5) {
//		for (int i = 1; i < argc; i++) {
//			printf("Arg 1: ", argc[i])
//		}
//	}
//	if (argc >= 5) {
//		wchar_t* inputFileName;
//		wchar_t* outputFileName;
//		// Loop through command-line arguments
//		for (int i = 1; i < argc; i++) {
//			if (wcscmp(wargv[i], L"-in") == 0 && i + 1 < argc) {
//				// Extract input file information
//				inputFileName = wargv[i + 1];
//				printf("Input file: %ls\n", inputFileName);
//				//std::wcout << L"Input file: " << inputFileName << std::endl;
//			}
//			if (wcscmp(wargv[i], L"-out") == 0 && i + 1 < argc) {
//				// Extract output file information
//				outputFileName = wargv[i + 1];
//				printf("Output file: %ls\n", outputFileName);
//				//std::wcout << L"Output file: " << outputFileName << std::endl;
//			}
//		}
//		printf("Input file: %ls\n", inputFileName);
//		printf("Output file: %ls\n", outputFileName);
//		MIEC::Scanner* scanner = new MIEC::Scanner((wchar_t*)inputFileName);
//		MIEC::Parser* parser = new MIEC::Parser(scanner);
//		//		parser->tab = new MIEC::SymbolTable(parser);
//		//		parser->gen = new MIEC::CodeGenerator();
//		parser->Parse();
//		if (parser->errors->count == 0) {
//			printf("No errors detected!");
//		}
//		else {
//			printf("%d errors detected", parser->errors->count);
//		}
//
//		coco_string_delete(inputFileName);
//		//		delete parser->gen;
//		//		delete parser->tab;
//		delete parser;
//		delete scanner;
//	}
//	else {
//		printf("-- No source file specified\n");
//	}
////	if (argc == 2) {
////		wchar_t* fileName = coco_string_create(argv[1]);
////		MIEC::Scanner* scanner = new MIEC::Scanner(fileName);
////		MIEC::Parser* parser = new MIEC::Parser(scanner);
//////		parser->tab = new MIEC::SymbolTable(parser);
//////		parser->gen = new MIEC::CodeGenerator();
////		parser->Parse();
////		if (parser->errors->count == 0) {
////			printf("No errors detected!");
////		}
////		else {
////			printf("%d errors detected", parser->errors->count);
////		}
////
////		coco_string_delete(fileName);
//////		delete parser->gen;
//////		delete parser->tab;
////		delete parser;
////		delete scanner;
////	}
////	else
////		printf("-- No source file specified\n");
//
//   return 0;
//}