

#if !defined(COCO_PARSER_H__)
#define COCO_PARSER_H__



#include "Scanner.h"

namespace MIEC {


class Errors {
public:
	int count;			// number of errors detected

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_LPAREN=1,
		_RPAREN=2,
		_SEMICOLON=3,
		_COLON=4,
		_EQUALS=5,
		_PLUS=6,
		_MINUS=7,
		_TIMES=8,
		_DIVIDE=9,
		_RELOP=10,
		_IDENT=11,
		_PRINT=12,
		_IF_STMNT=13,
		_THEN=14,
		_ELSE=15,
		_WHILE=16,
		_DO=17,
		_BEGIN=18,
		_END_STMNT=19,
		_BEGIN_VAR=20,
		_END_VAR=21,
		_NUMBER=22,
		_TYPES=23,
		_PROGRAM=24
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token

void Err(wchar_t* msg) {
		errors->Error(la->line, la->col, msg);
	}

  


	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void EXPR();
	void TERM();
	void FACT();
	void CONDITION();
	void STMNT();
	void PRINT_STMNT();
	void VARDECL();
	void MIEC();

	void Parse();

}; // end Parser

} // namespace


#endif // !defined(COCO_PARSER_H__)

