#include "stdafx.h"

#include "Error.h"

Error::Error() {}

Error::~Error() {}

void Error::Accept(sPtr(Scaner) c)
{
	m_compiler_part.push_back(c);
}
vector<string> Error::GetErrors() const
{
	vector<string> s; 
	for (vector<sPtr(Scaner)>::const_iterator it = m_compiler_part.cbegin(); it != m_compiler_part.cend(); ++it)
	{
		vector<string> errs = it->get()->GetErrors();
		s.insert(s.end(), errs.begin(), errs.end());
	}
	return s;
}

bool Error::HasErrors() const
{
	return (GetErrors().size() > 0);
}

ostream& operator << (ostream &strm, Error const& e)
{
	vector<string> errs = e.GetErrors();
	for (size_t i = 0; i < errs.size(); ++i)
	{
		strm << (i + 1) << ". " << errs[i] << endl;
	}
	return strm;
}