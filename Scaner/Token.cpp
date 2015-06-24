#include "stdafx.h"

#include "Token.h"
#include "Scaner.h"

Token::Token(int t, string v, size_t spos, size_t ipos) : type(t), value(v), str_pos(spos), index_pos(ipos) {}

Token::~Token() {}

string Token::ToString(size_t max_value_len) const
{
	stringstream ss;
	ss << str_pos << " " << Scaner::TokenTs[type] << " " << value;
	return ss.str();
}