#pragma once
class ShiftJISChecker
{
public:
	static	int Check(unsigned char uc);
	static	int Check(char c) { return Check((unsigned char)c); }
};

