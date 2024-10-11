#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hexfind.h"
char findhex(char* str);
char findhex(char* str) {
	char hexlist[17] = { '1','2','3','4','5','6','7','8','9','0','A','B','C','D','E','F' };
	int ok = 0;
	for (int i = 2; i < strlen(str) - 1; i++) {
		for (int k = 0; k < strlen(hexlist); k++) {
			if (*(str + i) == *(hexlist + k)) {
				ok++;
			}
		}
	}
	if (ok == strlen(str) - 3) {
		return 'o';
	}
	else if (ok < strlen(str) - 3) {
		return 'x';
	}
}