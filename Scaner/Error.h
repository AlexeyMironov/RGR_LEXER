#pragma once
#include "Scaner.h"

class Error
{
public:
	Error();
	~Error();

	void Accept(sPtr(Scaner) c);
	vector<string> GetErrors() const;
	bool HasErrors() const;
	string GetResult() const;
private:
	vector<sPtr(Scaner)> m_compiler_part;
};

ostream& operator << (ostream &strm, Error const& e);