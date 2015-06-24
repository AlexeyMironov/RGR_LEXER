#include "stdafx.h"
#include "TokenError.h"


TokenError::TokenError(int t, string v, size_t spos, size_t ipos, int e) : Token(t, v, spos, ipos), error_code(e) {}

TokenError::~TokenError() {}
