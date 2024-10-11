#pragma warning(disable : 4996)
#include "remake.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include<stdlib.h>
// 함수 원형 선언
char* trim_left(char* sr);
char* trim_right(char* sr);
char* trim(char* sr);
// trim_left 함수: 문자열의 왼쪽 공백을 제거
char* trim_left(char* sr){
    while (*sr) {
        if (isspace(*sr)) {
            sr++;
        }
        else {
            break;
        }
    }
    return sr;
}
// trim_right 함수: 문자열의 오른쪽 공백을 제거
char* trim_right(char* sr) {
    int len = (int)strlen(sr) - 1;
    while (len >= 0) {
        if (isspace(*(sr + len))) {
            len--;
        }
        else {
            break;
        }
    }
    *(sr + ++len) = '\0';
    return sr;
}
// trim 함수: 문자열의 양쪽 공백을 제거
char* trim(char* sr) {
    return trim_left(trim_right(sr));
}