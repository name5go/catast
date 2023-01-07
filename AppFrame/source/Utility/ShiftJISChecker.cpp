#include "ShiftJISChecker.h"

// SHIFT-JIS��1�����ڂ��m�F���A
// 1byte(���p)��2byte(�S�p)�����`�F�b�N
int ShiftJISChecker::Check(unsigned char uc) {
	if (uc < 0x81) { return 1; }
	if (uc < 0xa0) { return 2; }
	if (uc < 0xe0) { return 1; }
	if (uc < 0xff) { return 2; }
	return 1;
}
