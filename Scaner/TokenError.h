#pragma once
#include "Token.h"

class TokenError : public Token
{
public:
	TokenError(int t, string v, size_t spos, size_t ipos, int e_code);
	virtual ~TokenError();

	int error_code;
};

