#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "remake.h"
#include "hexfind.h"
#include "errorfile.h"
#define MAX_LEN 81
void StringCopy(char* str, char* copy);
void labelcopy(char* copy, char* label, char* OPeratoroperand, char* senevcolumn);
void divideOPcode(char* trimOPeratoroperand, char* operator, char* operand);
void simcount(char* trimoperand, FILE* fp);
void errorlabel(char* trimlabel, FILE* fp);
	int main(void) {
		FILE* fs;
		FILE* fp;
		char str[MAX_LEN] = " ";
		char delimit[] = "\n";
		char delimitt[] = " \n";
		char columndelit[] = "\n";
		char* token = "";
		char* tokenn = "";
		char* columntokenn = " ";
		fs = fopen("test.asm", "r");
		fp = fopen("test.txt", "w");
		while (fgets(str, sizeof(str), fs) != NULL) {
			char copy[MAX_LEN] = " ";
			char copylabel[7] = " ";
			char trimlabel[7] = " ";
			char label[7] = "";
			char senevcolumn[2] = "";
			char OPeratoroperand[74] = "";
			char trimOPeratoroperand[75] = "";
			char operator[37] = "";
			char operand[38] = "";
			char trimoperator[37] = "";
			char trimoperand[38] = "";
			int error = 0;

				StringCopy(str, copy);
				labelcopy(copy, label, OPeratoroperand, senevcolumn);

				strcpy(trimlabel, trim(label));
				errorlabel(trimlabel, fp);
				token = strtok(trimlabel, delimit);
				while (token != NULL) {
					printf("%s\n", token);
					fprintf(fp, "%s\n", token);
					token = strtok(NULL, delimit);
				}

				columntokenn = strtok(senevcolumn, columndelit);
				while (columntokenn != NULL) {
					printf("%s\n", columntokenn);
					fprintf(fp, "%s\n", columntokenn);
					columntokenn = strtok(NULL, columndelit);
				}
				strcpy(trimOPeratoroperand, trim(OPeratoroperand));
				divideOPcode(trimOPeratoroperand, operator, operand);


				strcpy(trimoperator, trim(operator));
				tokenn = strtok(trimoperator, delimitt);
				while (tokenn != NULL) {
					printf("%s\n", tokenn);
					fprintf(fp, "%s\n", tokenn);
					tokenn = strtok(NULL, delimitt);
				}

				strcpy(trimoperand, trim(operand));
				simcount(trimoperand, fp);	
		}
		fclose(fs);
		printf("--->File creation complete\n");
		printf("--->The existing file has been modified.\n");
		printf("-->Execution complete");
		return 0;
	}
	void errorlabel(char* trimlabel,FILE* fp) {
		for (int i = 0; i < strlen(trimlabel); i++) {
			if (*(trimlabel + i - 1) == ' ') {
				printf("Syntaxerror-----> %s\n", trimlabel);
				errorfile(fp);
			}
		}
	}
	void StringCopy(char* str, char* copy) {
		while (*str != 0) {
			if (*(str - 1) == '.') {
				break;
			}
			else {
				*(copy) = *(str);
				str++;
				copy++;
			}
		}
		*copy = '\0';
	}
	void labelcopy(char* copy, char* label, char* OPeratoroperand, char* senevcolumn) {
		for (int i = 0; i < strlen(copy); i++) {
			if (i < 6) {
				*(label + i) = *(copy + i);
			}
			else if (i == 6) {
				if (*(copy + i) == '.') {
					*(senevcolumn + (i-6)) = *(copy + i);
				}
			}
			else if (i  >=7) {
				*(OPeratoroperand + (i - 7)) = *(copy + i);
			}
		}
	}
	void divideOPcode(char* trimOPeratoroperand, char* operator, char* operand) {
		int count = 0;
		int i = 0;
			while (trimOPeratoroperand[i] != 0) {
                    if (trimOPeratoroperand[i - 1] == ' ') {
					count++;
					break;
				 }
				else {
					*(operator + i) = *(trimOPeratoroperand + i);
					i++;
				}
			}
		
			if (count == 1) {
				for (int k = i; k <= strlen(trimOPeratoroperand); k++) {
					*(operand + k - i) = trimOPeratoroperand[k];

				}
			}
	}
	void simcount(char* trimoperand, FILE* fp) {
		char delimittt[] = "\n,";
		char* tokennn = "";
		int size = strlen(trimoperand) - 3;
		char ohex[size];
		if (*trimoperand == 'C' && *(trimoperand + 1) == '\'' && *(trimoperand + strlen(trimoperand) - 1) == '\'') {
			printf("%c\n", 'C');
			fprintf(fp, "%c\n", 'C');
			for (int i = 2; i < strlen(trimoperand) - 1; i++) {
				printf("%c", *(trimoperand + i));
				fprintf(fp, "%c", *(trimoperand + i));
			}
			printf("\n");
			fprintf(fp, "\n", ' ');
		}
		else if (*trimoperand == 'X' && *(trimoperand + 1) == '\'' && *(trimoperand + strlen(trimoperand) - 1) == '\'') {
			if (findhex(trimoperand) =='o') {
				printf("%c\n", 'X');
				fprintf(fp, "%c\n", 'X');
				unsigned int result = 0;
				for (int i = 2; i < strlen(trimoperand) - 1; i++) {
					ohex[i - 2] = trimoperand[i];
				}
				result = strtol(ohex, NULL, 16);
				printf("%d\n", result);
				fprintf(fp, "%d\n", result);
			}
			else if (findhex(trimoperand) =='x') {
				printf("No change-----> %s\n", trimoperand);
				errorfile(fp);
			}
		}
		else {
			tokennn = strtok(trimoperand, delimittt);
			while (tokennn != NULL) {
				printf("%s\n", tokennn);
				fprintf(fp, "%s\n", tokennn);
				tokennn = strtok(NULL, delimittt);
			}
		}
	}