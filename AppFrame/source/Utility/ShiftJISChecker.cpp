#include "ShiftJISChecker.h"

// SHIFT-JISの1文字目を確認し、
// 1byte(半角)か2byte(全角)かをチェック
int ShiftJISChecker::Check(unsigned char uc) {
	if (uc < 0x81) { return 1; }
	if (uc < 0xa0) { return 2; }
	if (uc < 0xe0) { return 1; }
	if (uc < 0xff) { return 2; }
	return 1;
}
