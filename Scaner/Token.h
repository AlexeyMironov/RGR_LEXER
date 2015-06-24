#pragma once

#include "TokenTypes.h"

class Token
{
public:
	Token(int t, string v, size_t spos, size_t ipos);
	virtual ~Token();
	string ToString(size_t max_value_len) const;
	int type;
	string value;
	size_t str_pos;
	size_t index_pos;
};
