#include <iostream>
#include <stack>
#include <string>

// token types for non one-char tokens
constexpr int ID = 257;
constexpr int NUM = 258;
constexpr int EQ = 259;
constexpr int NE = 260;
constexpr int GE = 261;
constexpr int LE = 262;
constexpr int AND = 263;
constexpr int OR = 264;
constexpr int UMINUS = 265;
constexpr int MAXLEN = 80;
constexpr int ERROR = -1;

struct Expression {
	explicit Expression(const std::string& s) : str(s), pos(0)
	{
		len = str.length();
	}
	std::string str;
	int pos;
	int len;
};
struct Token {
	bool operator==(char);
	bool operator!=(char);
	Token();
	explicit Token(char); // 1-char token: type equals the token itself
	Token(char, char, int); // 2-char token(e.g. <=) & its type(e.g.LE)
	Token(const std::string& str, int, int); //operand with its length & type(defaulted to ID)
	bool IsOperand(); // true if the token type is ID or NUM
	int type; // ascii code for 1-char op; predefined for other tokens
	std::string str; // token value
	int len; // length of str
	int ival = 0; // used to store an integer for type NUM; init to 0 for ID
};
using namespace std;
ostream& operator<<(ostream&, Token t);
Token NextToken(Expression&, bool); // 2nd arg = true for infix expression
enum OperatorPriority {LEFTBRACKET_icp, UMINUS_FACTORIAL, MULTI_DIVIDE, PLUS_MINUS, LE_GE, EQ_NQ, _AND, _OR, EQUAL, LEFTBRACKET_isp,SHARP = 10};

bool Token::operator==(char b) { return len == 1 && str[0] == b; }
bool Token::operator!=(char b) { return len != 1 || str[0] != b; }
Token::Token() {}
Token::Token(const char c) : type(c), len(1)
{
	str.append(1, c);
} // default type = c itself
Token::Token(const char c, const char c2, const int ty) : type(ty), len(2)
{
	str.append(1, c);
    str.append(1, c2);
}
Token::Token(const std::string& arr, int l, int ty = ID) : type(ty) , len(l)
{
	for (int i = 0; i < len; i++) {
        str.append(1, arr[i]);
    }
	str.append(1, '\0');
	if (type == NUM) {
		ival = arr[0] - '0';
		for (int i = 1; i < len; i++) ival = ival * 10 + arr[i] - '0';
	}
	else if (type == ID) ival = 0;
	else throw "must be ID or NUM";
}
bool Token::IsOperand() { return type == ID || type == NUM; }
ostream& operator<<(ostream& os, Token t) {
	if (t.type == UMINUS) os << "-u";
	else if (t.type == NUM) os << t.ival;
	else for (int i = 0; i < t.len; i++) os << t.str[i];
	return os;
}
bool GetID(Expression& e, Token& tok) {
	char arr[MAXLEN]; int idlen = 0;
	char c = e.str[e.pos];
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) 
		return false;	// c가 알파벳이 아니면 false
	arr[idlen++] = c;	// arr[0]에다가 c 저장
	e.pos++;			// c 다음부터
	// c가 알파벳이거나 숫자면 arr에 저장, 연산자면 나가기
	while (((c = e.str[e.pos]) >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')) {
		arr[idlen++] = c; e.pos++;
	}
	arr[idlen] = '\0'; // 마지막은 개행 문자로
	tok = Token(arr, idlen, ID); // return an ID
	return true;
}
bool GetInt(Expression& e, Token& tok)
{
	char arr[MAXLEN]; int intLen = 0;
	char c = e.str[e.pos];
	if (c < '0' || c > '9') return false; // c가 integer가 아니면 false
	arr[intLen++] = c; // arr[0] 에다가 c 저장 후 intLen 1더하고
	e.pos++;
	for (c = e.str[e.pos]; '0' <= c && c <= '9'; c = e.str[++e.pos]) {
		arr[intLen++] = c;
	}
	arr[intLen] = '\0'; // 마지막은 개행 문자로
	tok = Token(arr, intLen, NUM);
	return true;
}
/*********
* function : SkipBlanks
* purpose : 수식 e의 pos 부분을 blank나 '\t'(tab) 부분이 있으면 넘겨버린다.
********/
void SkipBlanks(Expression& e) {
	char c;
	while (e.pos < e.len && ((c = e.str[e.pos]) == ' ' || c == '\t')) {
		e.pos++;
	}
}
bool TwoCharOp(Expression& e, Token& tok) {
	// 7가지 두글자 토큰들 <= >= == != && || -u을 처리
	char c = e.str[e.pos]; char c2 = e.str[e.pos + 1];
	int op; // LE GE EQ NE AND OR UMINUS
	if (c == '<' && c2 == '=') op = LE;			// <=
	else if (c == '>' && c2 == '=') op = GE;	// >=
	else if (c == '=' && c2 == '=') op = EQ;	// ==
	else if (c == '!' && c2 == '=') op = NE;	// !=
	else if (c == '&' && c2 == '&') op = AND;	// &&
	else if (c == '|' && c2 == '|') op = OR;	// ||
	else if (c == '-' && c2 == 'u') op = UMINUS;
	else { return false; } // 맞는 두 글자 토큰이 아니면 false를 return
	tok = Token(c, c2, op); e.pos += 2;
	return true;
}
bool OneCharOp(Expression& e, Token& tok) {
	char c = e.str[e.pos];
	if (c == '-' || c == '!' || c == '*' || c == '/' || c == '%' ||
		c == '+' || c == '<' || c == '>' || c == '(' || c == ')' || c == '=') {
		tok = Token(c); e.pos++; return true;
	}
	return false;
}
Token NextToken(Expression& e, bool INFIX = true) {
	static bool oprrFound = true; // 종전에 연산자 발견되었다고 가정.
	static bool previousIsBracket = false; // 이전 연산자가 여는 소괄호인지 아닌 지
	Token tok;
	SkipBlanks(e); // skip blanks if any
	if (e.pos == e.len) { // No more token left in this expression
		if (INFIX) oprrFound = true; return Token('#');
	}
	if (GetID(e, tok) || GetInt(e, tok)) {
		if (INFIX) oprrFound = false; return tok;
	}
	if(TwoCharOp(e, tok) || OneCharOp(e, tok)) {
		// operator 후 -발견
		if (tok.type == '-' && INFIX && oprrFound && !previousIsBracket) {
			tok = Token('-', 'u', UMINUS); // unary minus(-u)로 바꾸시오
		}
		if (INFIX) oprrFound = true;
		if (tok.type == '(' && INFIX) {
			previousIsBracket = true;
		}
		return tok;
	}
	throw "Illegal Character Found";
}
int icp(const Token& t) { // in-coming priority
	int ty = t.type;
	// 이 부분 작성
	// ty가 '('면 0,
	//UMINUS나 '!'면 1,
	//'*'나 '/'나 '%'면 2,
	//‘+’나 '-'면 3,
	//'<'나 '>'나 LE나 GE면 4,
	//EQ나 NE면 5,
	//AND면 6,
	//OR이면 7,
	//'='이면 8,
	//'#'면 10 를 return한다.
	if (ty == '(') return LEFTBRACKET_icp;
	else if (ty == UMINUS || ty == '!') return UMINUS_FACTORIAL;
	else if (ty == '*' || ty == '/' || ty == '%') return MULTI_DIVIDE;
	else if (ty == '+' || ty == '-') return PLUS_MINUS;
	else if (ty == '<' || ty == '>' || ty == LE || ty == GE) return LE_GE;
	else if (ty == AND) return _AND;
	else if (ty == OR) return _OR;
	else if (ty == '=') return EQUAL;
	else if (ty == '#') return SHARP;
	else return ERROR;
}
int isp(const Token& t) // in-stack priority
{
	int ty = t.type; //stack 에서의 우선순위 결정
	// stack 안에서는 여는 개괄호 (의 우선순위가 달라지는데, icp에서는 0이었다면 isp에서는 가장 낮은 값인 9를 리턴한다.
	// #(SHARP)보다는 우선순위가 높아야 하기에 #은 10으로 설정하였다
	if (ty == '(') return LEFTBRACKET_isp;
	else if (ty == UMINUS || ty == '!') return UMINUS_FACTORIAL;
	else if (ty == '*' || ty == '/' || ty == '%') return MULTI_DIVIDE;
	else if (ty == '+' || ty == '-') return PLUS_MINUS;
	else if (ty == '<' || ty == '>' || ty == LE || ty == GE) return LE_GE;
	else if (ty == AND) return _AND;
	else if (ty == OR) return _OR;
	else if (ty == '=') return EQUAL;
	else if (ty == '#') return SHARP;
	else return ERROR;
}
void Postfix(Expression e)
{
	stack<Token> Stack_Expression; // 수식 e를 담을 스택 생성
	Stack_Expression.emplace('#');
	for (Token x = NextToken(e); x != '#'; x = NextToken(e)) {
		if (x.IsOperand()) cout << x; // x가 피연산자 operand면 x 그대로 출력
		else if (x == ')') { // x가 닫는 괄호면 '('이 나올 때까지 unstack
			for (; Stack_Expression.top() != '('; Stack_Expression.pop()) {
				cout << Stack_Expression.top();
			}
			Stack_Expression.pop(); // unstack '('
		}
		else { // x is an operator
			for (; isp(Stack_Expression.top()) <= icp(x); Stack_Expression.pop()) {
				cout << Stack_Expression.top();
			}
			Stack_Expression.emplace(x);
		}
	}

	// end of expression; empty the stack
	while (Stack_Expression.top() != '#') {
		cout << Stack_Expression.top(); Stack_Expression.pop();
	}
	cout << endl; 
	Stack_Expression.pop();
}

int main()
{
    std::string str;
    std::cin >> str;

    Expression e(str);
    Postfix(e);

    return 0;
}