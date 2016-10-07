#pragma once

class string
{
private:
	char m_str[256];
public:
	string() {};
	string(char[]);
	int strcnt(); //Returns the length of the string
	char strret(int); //Returns character at index
	void strapp(string);
	void strpre(string);
	void strlow();
	void strcap();
	bool strsub(char[]);
	bool strsub(char[], int);
	bool strcomp(string);
	const char * cstyle();
	bool strrep(char[], char[]);
};

