

#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"


namespace MIEC {


void Parser::SynErr(int n) {
	if (errDist >= minErrDist) errors->SynErr(la->line, la->col, n);
	errDist = 0;
}

void Parser::SemErr(const wchar_t* msg) {
	if (errDist >= minErrDist) errors->Error(t->line, t->col, msg);
	errDist = 0;
}

void Parser::Get() {
	for (;;) {
		t = la;
		la = scanner->Scan();
		if (la->kind <= maxT) { ++errDist; break; }

		if (dummyToken != t) {
			dummyToken->kind = t->kind;
			dummyToken->pos = t->pos;
			dummyToken->col = t->col;
			dummyToken->line = t->line;
			dummyToken->next = NULL;
			coco_string_delete(dummyToken->val);
			dummyToken->val = coco_string_create(t->val);
			t = dummyToken;
		}
		la = t;
	}
}

void Parser::Expect(int n) {
	if (la->kind==n) Get(); else { SynErr(n); }
}

void Parser::ExpectWeak(int n, int follow) {
	if (la->kind == n) Get();
	else {
		SynErr(n);
		while (!StartOf(follow)) Get();
	}
}

bool Parser::WeakSeparator(int n, int syFol, int repFol) {
	if (la->kind == n) {Get(); return true;}
	else if (StartOf(repFol)) {return false;}
	else {
		SynErr(n);
		while (!(StartOf(syFol) || StartOf(repFol) || StartOf(0))) {
			Get();
		}
		return StartOf(syFol);
	}
}

void Parser::EXPR() {
		TERM();
		while (la->kind == 6 || la->kind == 7) {
			if (la->kind == 6) {
				Get();
			} else {
				Get();
			}
			TERM();
		}
}

void Parser::TERM() {
		FACT();
		while (la->kind == 8 || la->kind == 9) {
			if (la->kind == 8) {
				Get();
			} else {
				Get();
			}
			FACT();
		}
}

void Parser::FACT() {
		if (la->kind == 11) {
			Get();
		} else if (la->kind == 22) {
			Get();
		} else if (la->kind == 1) {
			Get();
			EXPR();
			Expect(2);
		} else SynErr(26);
}

void Parser::CONDITION() {
		EXPR();
		Expect(10);
		EXPR();
}

void Parser::STMNT() {
		if (la->kind == 11 || la->kind == 12) {
			if (la->kind == 11) {
				Get();
				Expect(5);
				EXPR();
			} else {
				PRINT_STMNT();
			}
			Expect(3);
		} else if (la->kind == 16) {
			Get();
			CONDITION();
			Expect(17);
			STMNT();
			Expect(19);
		} else if (la->kind == 13) {
			Get();
			CONDITION();
			Expect(14);
			if (StartOf(1)) {
				STMNT();
				Expect(15);
			}
			STMNT();
			Expect(19);
		} else SynErr(27);
}

void Parser::PRINT_STMNT() {
		Expect(12);
		Expect(1);
		EXPR();
		Expect(2);
}

void Parser::VARDECL() {
		Expect(20);
		while (la->kind == 11) {
			Get();
			Expect(4);
			Expect(23);
			Expect(3);
		}
		Expect(21);
}

void Parser::MIEC() {
		Expect(24);
		Expect(11);
		if (la->kind == 20) {
			VARDECL();
		}
		Expect(18);
		while (StartOf(1)) {
			STMNT();
		}
		Expect(19);
}



void Parser::Parse() {
	t = NULL;
	la = dummyToken = new Token();
	la->val = coco_string_create(L"Dummy Token");
	Get();
	MIEC();

	Expect(0);
}

Parser::Parser(Scanner *scanner) {
	maxT = 25;

	dummyToken = NULL;
	t = la = NULL;
	minErrDist = 2;
	errDist = minErrDist;
	this->scanner = scanner;
	errors = new Errors();
}

bool Parser::StartOf(int s) {
	const bool T = true;
	const bool x = false;

	static bool set[2][27] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,T, T,T,x,x, T,x,x,x, x,x,x,x, x,x,x}
	};



	return set[s][la->kind];
}

Parser::~Parser() {
	delete errors;
	delete dummyToken;
}

Errors::Errors() {
	count = 0;
}

void Errors::SynErr(int line, int col, int n) {
	wchar_t* s;
	switch (n) {
			case 0: s = coco_string_create(L"EOF expected"); break;
			case 1: s = coco_string_create(L"LPAREN expected"); break;
			case 2: s = coco_string_create(L"RPAREN expected"); break;
			case 3: s = coco_string_create(L"SEMICOLON expected"); break;
			case 4: s = coco_string_create(L"COLON expected"); break;
			case 5: s = coco_string_create(L"EQUALS expected"); break;
			case 6: s = coco_string_create(L"PLUS expected"); break;
			case 7: s = coco_string_create(L"MINUS expected"); break;
			case 8: s = coco_string_create(L"TIMES expected"); break;
			case 9: s = coco_string_create(L"DIVIDE expected"); break;
			case 10: s = coco_string_create(L"RELOP expected"); break;
			case 11: s = coco_string_create(L"IDENT expected"); break;
			case 12: s = coco_string_create(L"PRINT expected"); break;
			case 13: s = coco_string_create(L"IF_STMNT expected"); break;
			case 14: s = coco_string_create(L"THEN expected"); break;
			case 15: s = coco_string_create(L"ELSE expected"); break;
			case 16: s = coco_string_create(L"WHILE expected"); break;
			case 17: s = coco_string_create(L"DO expected"); break;
			case 18: s = coco_string_create(L"BEGIN expected"); break;
			case 19: s = coco_string_create(L"END_STMNT expected"); break;
			case 20: s = coco_string_create(L"BEGIN_VAR expected"); break;
			case 21: s = coco_string_create(L"END_VAR expected"); break;
			case 22: s = coco_string_create(L"NUMBER expected"); break;
			case 23: s = coco_string_create(L"TYPES expected"); break;
			case 24: s = coco_string_create(L"PROGRAM expected"); break;
			case 25: s = coco_string_create(L"??? expected"); break;
			case 26: s = coco_string_create(L"invalid FACT"); break;
			case 27: s = coco_string_create(L"invalid STMNT"); break;

		default:
		{
			wchar_t format[20];
			coco_swprintf(format, 20, L"error %d", n);
			s = coco_string_create(format);
		}
		break;
	}
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	coco_string_delete(s);
	count++;
}

void Errors::Error(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	count++;
}

void Errors::Warning(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
}

void Errors::Warning(const wchar_t *s) {
	wprintf(L"%ls\n", s);
}

void Errors::Exception(const wchar_t* s) {
	wprintf(L"%ls", s); 
	exit(1);
}

} // namespace


