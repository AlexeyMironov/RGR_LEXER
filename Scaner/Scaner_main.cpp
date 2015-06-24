// Scaner.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include "Scaner.h"
#include "Parser.h"
#include "Error.h"


string Tooem(const char* str) //нужно дл€ распознавани€ русского названи€ файлов из консоли
{
	vector<char> buffer(strlen(str) + 1);
	CharToOemA(str, &buffer[0]); //конвертаци€ char в string 
	return string(&buffer[0], buffer.size()-1);
}

int main(int argc, char* argv[])
{
	string temp;
	string fin_file_name, fout_file_name;

	if (!(argc == 2 || argc == 3))
	{
		cout << "Need command line arguments: <input file> [<output file>]." << endl;
		return 1;
	}
	//открытие файлов
	if (argc > 1)
	{
		fin_file_name = Tooem(argv[1]);
	}
	ifstream fin(fin_file_name, ios::in);
	if (!fin)  
	{
		cout << "Error opening file: " << fin_file_name << "!" << endl;
		return 1;
	}
	if (argc > 2)
	{
		fout_file_name = Tooem(argv[2]);
	}
	if (fin_file_name == fout_file_name)
	{
		cout << "Command line arguments is same: <input file> <output file>." << endl;
		return 1;
	}

	ofstream f;
	if (!fout_file_name.empty())
	{
		f.open(fout_file_name, ios::out);
		if (!f)  
		{
			cout << "Error opening file: " << fout_file_name << "!" << endl;
			return 1;
		}
	}
	Error e;
	sPtr(Scaner) scaner(new Scaner);// динамич. указатель на сканер
	e.Accept(dynamic_pointer_cast<Scaner>(scaner));

	while (!fin.eof())
	{
		getline(fin, temp);
		scaner->SetString(temp);
	}
	if (e.HasErrors())
	{
		f << e;
	}
	else
	{
		sPtr(Token) t;
		size_t max_value_len = scaner->GetMaxTokenLength(); // дл€ выравнивани€
		f << "<Token List: >" << endl;;
		while (true)
		{
			t = scaner->PopToken();
			if (t->type != T_EOF)
			{
				f << t->ToString(max_value_len) << endl;
			}
			else
			{
				break;
			}
		}
		scaner->ResetTokenPos();
		f << endl << "<ID List: >" << endl;
		set<string> IdList = scaner->GetIdList();
		for (set<string>::const_iterator it = IdList.cbegin(); it != IdList.cend(); ++it)
		{
			f << *it << endl;
		}
	}
	return 0;
}

