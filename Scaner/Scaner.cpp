#include "stdafx.h"
#include "assert.h"
#include "ErrorTypes.h"
#include "Scaner.h"

map<int, string> Scaner::TokenEq = Scaner::InitTokenEq();
map<int, string> Scaner::TokenTs = Scaner::InitTokenTs();

Scaner::Scaner() {
	InitTokenEq();
	InitErrors();
	m_curr_str = 0;
	m_curr_index = 0;
	m_state_comment = false;
	ResetTokenPos();
	InitSeparators();
}

Scaner::Scaner(Scaner const& scaner)
{
	ResetTokenPos();
}
Scaner::~Scaner() {}

map<int, string> Scaner::InitTokenEq()
{
	 map<int, string> TokenEq;
//c
	TokenEq[T_ERROR] = "";
	TokenEq[T_EOF] = "\0";
	TokenEq[T_EOFS] = "EOF";
//sep
	TokenEq[T_SEPARATOR_TAB] = "\t";
	TokenEq[T_SEPARATOR_SPACE] = " ";
	TokenEq[T_SEPARATOR_N] = "\n";
//for value
	TokenEq[T_DIGITS] = "";
	TokenEq[T_ID] = "";
	TokenEq[T_STRING] = "";
//keyword
	TokenEq[T_INT] = "int";
	TokenEq[T_DOUBLE] = "double";
	TokenEq[T_FLOAT] = "float";
	TokenEq[T_LONG] = "long";
	TokenEq[T_CHAR] = "char"; 
	TokenEq[T_SHORT] = "short";
	TokenEq[T_WHILE] = "while";
	TokenEq[T_IF] = "if";
	TokenEq[T_ELSE] = "else";
	TokenEq[T_DO] = "do";
	TokenEq[T_AUTO] = "auto";
	TokenEq[T_BREAK] = "break";
	TokenEq[T_CASE] = "case";
	TokenEq[T_CONST] = "const";
	TokenEq[T_CONTINUE] = "continue";
	TokenEq[T_DEFAULT] = "default";
	TokenEq[T_ENUM] = "enum";
	TokenEq[T_EXTERN] = "extern";
	TokenEq[T_FOR] = "for";
	TokenEq[T_GOTO] = "goto";
	TokenEq[T_RETURN] = "return";
	TokenEq[T_REGISTER] = "register";
	TokenEq[T_SIGNED] = "signed";
	TokenEq[T_SIZEOF] = "sizeof";
	TokenEq[T_STATIC] = "static";
	TokenEq[T_STRUCT] = "struct";
	TokenEq[T_SWITCH] = "switch";
	TokenEq[T_TYPEDEF] = "typedef";
	TokenEq[T_UNION] = "union";
	TokenEq[T_UNSIGNED] = "unsigned";
	TokenEq[T_VOID] = "void";
	TokenEq[T_VOLATILE] = "volatile";
//comment
	TokenEq[T_SINGLE_COMMENT] = "//";
	TokenEq[T_L_MULTIPLE_COMMENT] = "/*";
	TokenEq[T_R_MULTIPLE_COMMENT] = "*/";
//spec_separator
	TokenEq[T_L_PARENTHESIS] = "(";
	TokenEq[T_R_PARENTHESIS] = ")";
	TokenEq[T_L_SQUARE_BRACKET] = "[";
	TokenEq[T_R_SQUARE_BRACKET] = "]";
	TokenEq[T_L_BRACES] = "{";
	TokenEq[T_R_BRACES] = "}";
	TokenEq[T_SEMICOLON] = ";";
	TokenEq[T_COLON] = ":";
	TokenEq[T_INC] = "++";
	TokenEq[T_ADD] = "+";
	TokenEq[T_DEC] = "--";
	TokenEq[T_SUBSTRACT] = "-";
	TokenEq[T_MULTIPLY] = "*";
	TokenEq[T_DIVIDE] = "/";
	TokenEq[T_COMPARE_LESS] = "<";
	TokenEq[T_COMPARE_MORE] = ">";
	TokenEq[T_EQUAL] = "=";
	TokenEq[T_NOT] = "!";
	TokenEq[T_NOT_EQUAL] = "!=";
	TokenEq[T_SINGLE_QUOTE] = "'";
	TokenEq[T_DOUBLE_QUOTE] = "\"";
	TokenEq[T_AND] = "&";
	TokenEq[T_OR] = "|";
	TokenEq[T_COMMA] = ",";
	TokenEq[T_POINT] = ".";

	return TokenEq;
}

map<int, string> Scaner::InitTokenTs()
{
	map<int, string> TokenTs;
//c
	TokenTs[T_ERROR] = "ERROR";
//sep
	TokenTs[T_SEPARATOR_TAB] = "SEPARATOR_TAB";
	TokenTs[T_SEPARATOR_SPACE] = "SEPARATOR_SPACE";
	TokenTs[T_SEPARATOR_N] = "SEPARATOR_N";
//for value
	TokenTs[T_DIGITS] = "CONST_INTEGER";
	TokenTs[T_ID] = "IDENTIFIER";
	TokenTs[T_STRING] = "STRING";
//keyword
	TokenTs[T_INT] = "INT";
	TokenTs[T_DOUBLE] = "DOUBLE";
	TokenTs[T_FLOAT] = "FLOAT";
	TokenTs[T_LONG] = "LONG";
	TokenTs[T_CHAR] = "CHAR"; 
	TokenTs[T_SHORT] = "SHORT";
	TokenTs[T_WHILE] = "WHILE";
	TokenTs[T_IF] = "IF";
	TokenTs[T_ELSE] = "ELSE";
	TokenTs[T_DO] = "DO";
	TokenTs[T_AUTO] = "AUTO";
	TokenTs[T_BREAK] = "BREAK";
	TokenTs[T_CASE] = "CASE";
	TokenTs[T_CONST] = "CONST";
	TokenTs[T_CONTINUE] = "CONTINUE";
	TokenTs[T_DEFAULT] = "DEFAULT";
	TokenTs[T_ENUM] = "ENUM";
	TokenTs[T_EXTERN] = "EXTERN";
	TokenTs[T_FOR] = "FOR";
	TokenTs[T_GOTO] = "GOTO";
	TokenTs[T_RETURN] = "RETURN";
	TokenTs[T_REGISTER] = "REGISTER";
	TokenTs[T_SIGNED] = "SIGNED";
	TokenTs[T_SIZEOF] = "SIZEOF";
	TokenTs[T_STATIC] = "STATIC";
	TokenTs[T_STRUCT] = "STRUCT";
	TokenTs[T_SWITCH] = "SWITCH";
	TokenTs[T_TYPEDEF] = "TYPEDEF";
	TokenTs[T_UNION] = "UNION";
	TokenTs[T_UNSIGNED] = "UNSIGNED";
	TokenTs[T_VOID] = "VOID";
	TokenTs[T_VOLATILE] = "VOLATILE";
//spec_separator
	TokenTs[T_L_PARENTHESIS] = "PARENTHESIS_L";
	TokenTs[T_R_PARENTHESIS] = "PARENTHESIS_R";
	TokenTs[T_L_SQUARE_BRACKET] = "SQUARE_BRACKET_L";
	TokenTs[T_R_SQUARE_BRACKET] = "SQUARE_BRACKET_R";
	TokenTs[T_L_BRACES] = "BRACE_L";
	TokenTs[T_R_BRACES] = "BRACE_R";
	TokenTs[T_SEMICOLON] = "SEMICOLON";
	TokenTs[T_COLON] = "COLON";
	TokenTs[T_ADD] = "ADD_OP";
	TokenTs[T_INC] = "INC_OP";
	TokenTs[T_SUBSTRACT] = "SUB_OP";
	TokenTs[T_DEC] = "DEC_OP";
	TokenTs[T_MULTIPLY] = "MUL_OP";
	TokenTs[T_DIVIDE] = "DIV_OP";
	TokenTs[T_COMPARE_LESS] = "COMPARE_LESS";
	TokenTs[T_COMPARE_MORE] = "COMPARE_MORE";
	TokenTs[T_EQUAL] = "COMPARE_EQUAL";
	TokenTs[T_NOT] = "NOT";
	TokenTs[T_NOT_EQUAL] = "COMPARE_NOT_EQUAL";
	TokenTs[T_SINGLE_QUOTE] = "SEPARATOR";
	TokenTs[T_DOUBLE_QUOTE] = "SEPARATOR";
	TokenTs[T_AND] = "AND";
	TokenTs[T_OR] = "OR";
	TokenTs[T_COMMA] = "COMMA";
	TokenTs[T_POINT] = "DOT";

	return TokenTs;
}

void Scaner::InitSeparators()
{
	Separator.insert(T_SEPARATOR_TAB);
	Separator.insert(T_SEPARATOR_SPACE);
	Separator.insert(T_SEPARATOR_N);
	Separator.insert(T_EOF);
	Separator.insert(T_L_MULTIPLE_COMMENT);
	Separator.insert(T_R_MULTIPLE_COMMENT);
	Separator.insert(T_SINGLE_COMMENT);

	SpecSeparator.insert(T_L_PARENTHESIS);
	SpecSeparator.insert(T_R_PARENTHESIS);
	SpecSeparator.insert(T_L_SQUARE_BRACKET);
	SpecSeparator.insert(T_R_SQUARE_BRACKET);
	SpecSeparator.insert(T_L_BRACES);
	SpecSeparator.insert(T_R_BRACES);
	SpecSeparator.insert(T_SEMICOLON);
	SpecSeparator.insert(T_COLON);
	SpecSeparator.insert(T_ADD);
	SpecSeparator.insert(T_SUBSTRACT);
	SpecSeparator.insert(T_MULTIPLY);
	SpecSeparator.insert(T_DIVIDE);
	SpecSeparator.insert(T_COMPARE_LESS);
	SpecSeparator.insert(T_COMPARE_MORE);
	SpecSeparator.insert(T_EQUAL);
	SpecSeparator.insert(T_NOT);
	SpecSeparator.insert(T_NOT_EQUAL);
	SpecSeparator.insert(T_SINGLE_QUOTE);
	SpecSeparator.insert(T_DOUBLE_QUOTE);
	SpecSeparator.insert(T_AND);
	SpecSeparator.insert(T_COMMA);
	SpecSeparator.insert(T_OR);
	SpecSeparator.insert(T_POINT);
}

void Scaner::InitErrors()
{
	Error[E_SCANER_UNRECOGNIZED_IDENTIFIER] = "Unrecognized identifier: ";
	Error[E_SCANER_INCORRECT_IDENTIFIER] = "Incorrect identifier: ";
	Error[E_SCANER_UNKNOWN_SYMBOL] = "Unknown symbol: ";
	Error[E_SCANER_NO_CLOSING_QUOUTE] = "No closing quoute: ";
}
bool Scaner::SetString(string raw)
{
	string curr_token = "";
	int curr_type;
	++m_curr_str;
	raw += '\n';
	for (size_t n = 0; n < raw.length(); ++n)
	{
		if (CheckTokenType(string(&raw[n], 2), T_SINGLE_COMMENT))
		{
			m_state_comment = true;
			while (n < raw.length() && !CheckTokenType(string(&raw[n], 1), T_SEPARATOR_N))
				++n;
			m_state_comment = false;
			continue;
		}
		else if (CheckTokenType(string(&raw[n], 2), T_L_MULTIPLE_COMMENT) || m_state_comment)
		{
			m_state_comment = true;
			while ((n < raw.length()) && !CheckTokenType(string(&raw[n], 2), T_R_MULTIPLE_COMMENT))
				++n;
			if (CheckTokenType(string(&raw[n], 2), T_R_MULTIPLE_COMMENT))
				m_state_comment = false;
			++n;
			continue;
		}
		else if (CheckTokenType(string(&raw[n], 1), T_DOUBLE_QUOTE))
		{
			++n;
			string tmp = "";
			while ((n < (raw.length())) && !CheckTokenType(string(&raw[n], 1), T_DOUBLE_QUOTE))
			{
				tmp += raw[n];
				++n;
			}
			PushToken(sPtr(Token)(new Token(T_DOUBLE_QUOTE, TokenEq[T_DOUBLE_QUOTE], m_curr_str, m_curr_index)));
			PushToken(sPtr(Token)(new Token(T_STRING, tmp, m_curr_str, m_curr_index)));
			if (!CheckTokenType(string(&raw[n], 1), T_DOUBLE_QUOTE))
				PushToken(sPtr(Token)(new TokenError(T_ERROR, curr_token, m_curr_str, m_curr_index, E_SCANER_NO_CLOSING_QUOUTE)));
			else
				PushToken(sPtr(Token)(new Token(T_DOUBLE_QUOTE, TokenEq[T_DOUBLE_QUOTE], m_curr_str, m_curr_index)));
			continue;
		}
		else if (CheckTokenType(string(&raw[n], 1), T_SINGLE_QUOTE))
		{
			++n;
			string tmp = "";
			while ((n < (raw.length())) && !CheckTokenType(string(&raw[n], 1), T_SINGLE_QUOTE))
			{
				tmp += raw[n];
				++n;
			}
			PushToken(sPtr(Token)(new Token(T_SINGLE_QUOTE, TokenEq[T_SINGLE_QUOTE], m_curr_str, m_curr_index)));
			PushToken(sPtr(Token)(new Token(T_STRING, tmp, m_curr_str, m_curr_index)));
			if (!CheckTokenType(string(&raw[n], 1), T_SINGLE_QUOTE))
				PushToken(sPtr(Token)(new TokenError(T_ERROR, curr_token, m_curr_str, m_curr_index, E_SCANER_NO_CLOSING_QUOUTE)));
			else
				PushToken(sPtr(Token)(new Token(T_SINGLE_QUOTE, TokenEq[T_SINGLE_QUOTE], m_curr_str, m_curr_index)));
			continue;
		}
		else if (IsSeparator(raw[n]))
		{
			if (!curr_token.empty())
			{
				if (IsDigits(curr_token))
				{
					PushToken(sPtr(Token)(new Token(T_DIGITS, curr_token, m_curr_str, m_curr_index)));
				}
				else if (IsId(curr_token))
				{
					PushToken(sPtr(Token)(new Token(T_ID, curr_token, m_curr_str, m_curr_index)));
				}
				else
				{
					PushToken(sPtr(Token)(new TokenError(T_ERROR, curr_token, m_curr_str, m_curr_index, E_SCANER_INCORRECT_IDENTIFIER)));
				}
				curr_token.erase();
			}
			if (!IsSpecSeparator(raw[n]) || CheckTokenType(string(&raw[n], 2), T_L_MULTIPLE_COMMENT))
				continue;
		}
		curr_token += raw[n];
		if (((curr_type = CheckToken(curr_token)) != T_ERROR) && (IsSeparator(raw[n + 1]) || IsSpecSeparator(curr_token[0])))
		{
			PushToken(sPtr(Token)(new Token(curr_type, curr_token, m_curr_str, m_curr_index)));
			curr_token.erase();
		}
	}
	return true;
}

sPtr(Token) Scaner::PopToken()
{	
	if (!m_tokens.empty() && (m_curr_pos != m_tokens.cend()))
	{
		return (sPtr(Token)(*m_curr_pos++));
	}
	else
	{
		//trow exeption
		return sPtr(Token)(new Token(T_EOF, TokenEq[T_EOF], m_curr_str, m_curr_index));
	}
}

sPtr(Token) Scaner::NextToken() const
{
	if (!m_tokens.empty() && (m_curr_pos != m_tokens.cend()))
	{
		vector<sPtr(Token)>::const_iterator it = m_curr_pos;
		return (sPtr(Token)(*it++));
	}
	else
	{
		//trow exeption
		return sPtr(Token)(new Token(T_EOF, TokenEq.at(T_EOF), m_curr_str, m_curr_index));
	}
}
void Scaner::PushToken(sPtr(Token) t)
{
	if (!m_tokens.empty())
	{
		Token* lastToken = m_tokens[m_tokens.size() - 1].get();
		string value1 = lastToken->value;
		string value2 = t->value;
		if ((value1 == value2) && (value1 == "+"))
		{
			lastToken->value = "++";
			lastToken->type = T_INC;
			return;
		}

		if ((value1 == value2) && (value1 == "-"))
		{
			lastToken->value = "--";
			lastToken->type = T_DEC;
			return;
		}
	}
	m_tokens.push_back(t);
	++m_curr_index;
	ResetTokenPos(); //because current iterator invalidate afler push_back;
}

int Scaner::CheckToken(const string &token) const
{
	if (token.empty())
		return T_EOF;
	for (map<int, string>::const_iterator it = TokenEq.begin(); it != TokenEq.end(); ++it)
	{
		if (!it->second.empty() && it->second == token)
			return it->first;
	}
	return T_ERROR;
}

bool Scaner::CheckTokenType(const string &token, const int &type) const
{
	try
	{
		string TokenDefVal = TokenEq.at(type);
		if (!TokenDefVal.empty() && TokenDefVal == token && !token.empty())
			return true;
	}
	catch(std::out_of_range const& e)
	{
		e.what();
	}
	return false;
}

bool Scaner::IsSeparator(const char &ch) const
{
	int token_type = CheckToken(string(&ch, 1));
	return (Separator.find(token_type) != Separator.end() || IsSpecSeparator(ch));
}

bool Scaner::IsSpecSeparator(const char &ch) const
{
	int token_type = CheckToken(string(&ch, 1));
	return (SpecSeparator.find(token_type) != SpecSeparator.end());
}

bool Scaner::IsDigit(const char &ch)
{
	return (ch >= '0' && ch <= '9');
}

bool Scaner::IsDigits(const string &s)
{
	for (size_t i = 0; i < s.length(); ++i)
	{
		if (!IsDigit(s[i]))
			return false;
	}
	return (s.empty()) ? false : true;
}

bool Scaner::IsId(const string &s)
{
	return !IsDigit(s[0]);
}

void Scaner::ResetTokenPos()
{
	this->m_curr_pos = this->m_tokens.cbegin();
}

void Scaner::Clear()
{
	this->m_tokens.clear();
	m_curr_str = 0;
	m_curr_index = 0;
	m_state_comment = false;
	ResetTokenPos();
}

vector<sPtr(TokenError)> Scaner::GetErrorTokens() const
{
	vector<sPtr(TokenError)> v;
	for (vector<sPtr(Token)>::const_iterator it = m_tokens.cbegin(); it != m_tokens.cend(); ++it)
	{
		if (it->get()->type == T_ERROR)
			v.push_back(dynamic_pointer_cast<TokenError>(*it));
	}
	return v;
}

vector<string> Scaner::GetErrors() const
{
	vector<sPtr(TokenError)> e_tokens = Scaner::GetErrorTokens();
	vector<string> e_strings;
	for (vector<sPtr(TokenError)>::const_iterator it = e_tokens.cbegin(); it != e_tokens.cend(); ++it)
	{ 
		stringstream ss;
		ss << "ERROR (Scaner): "
			<< "<String: " << (it->get()->str_pos) << ">[" << it->get()->index_pos << "]: "
			<< Error.at(it->get()->error_code) << "`" << it->get()->value << "`";
		e_strings.push_back(ss.str());
		ss.clear(); ss.flush();
	}
	return e_strings;
}
set<string> Scaner::GetIdList() const
{
	set<string> id_list;
	for(vector<sPtr(Token)>::const_iterator it = m_tokens.cbegin(); it != m_tokens.cend(); ++it)
	{
		if (it->get()->type == T_ID)
			id_list.insert(it->get()->value);
	}
	return id_list;
}

size_t Scaner::GetTokenCount() const
{
	return m_tokens.size();
}

size_t Scaner::GetMaxTokenLength() const
{
	size_t size = 0;
	for(vector<sPtr(Token)>::const_iterator it = m_tokens.cbegin(); it != m_tokens.cend(); ++it)
	{
		//if (it->get()->type != T_STRING)
		if (it->get()->value.length() > size)
			size = it->get()->value.length();
	}
	return size;
}
