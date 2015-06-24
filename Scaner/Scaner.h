#pragma once
#include "Token.h"
#include "TokenError.h"

class Scaner 
{
public:
	Scaner();
	Scaner(Scaner const& scaner);
	~Scaner();
//interface
	bool SetString(string raw);
	sPtr(Token) PopToken();
	sPtr(Token) NextToken() const;
	void Clear();
	void ResetTokenPos();
	size_t GetTokenCount() const;
	size_t GetMaxTokenLength() const;
	set<string> GetIdList() const;
//errors
	vector<string> GetErrors() const;
	vector<sPtr(TokenError)> GetErrorTokens() const;
//tests
	//void PrivateTests();
//vars
	static map<int, string> TokenEq;
	static map<int, string> TokenTs;
	set<int> Separator;
	set<int> SpecSeparator;
	map<int, string> Error;
//init static vars
	static map<int, string> InitTokenEq(); //equals
	static map<int, string> InitTokenTs(); //to string
private:
	void InitSeparators();
	void InitErrors();
	void PushToken(sPtr(Token) t);
	int CheckToken(const string &token) const;
	bool CheckTokenType(const string &token, const int &type) const;
	bool IsSeparator(const char &ch) const;
	bool IsSpecSeparator(const char &ch) const;
	bool IsDigit(const char &ch);
	bool IsDigits(const string &s);
	bool IsId(const string &s);
//vars
	vector<sPtr(Token)> m_tokens;
	vector<sPtr(Token)>::const_iterator m_curr_pos;
	size_t m_curr_str;
	size_t m_curr_index;
	bool m_state_comment;
};