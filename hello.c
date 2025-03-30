#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void removeDuplicate();
void finalAnalysis();
int isIdentifier(char ch);
int isOperator(char ch);
int isDelimiter(char ch);
int isKeyword(char *str);

char operators[] = {'+', '-', '*', '/', '=', '<', '>', '%'};
char delimiters[] = {'}', '{', ';', '(', ')', '[', ']', ','};
char *keywords[] = {"int", "void", "main", "char", "float"};

int identifierCount = 0, operatorCount = 0, delimiterCount = 0, keywordCount = 0;
int uniqueDelimiterCount = 0, uniqueOperatorCount = 0, uniqueIdentifierCount = 0;
int literalCount = 0, constantCount = 0;

char uniqueDelimiters[20], uniqueIdentifiers[20][20], uniqueOperators[20][20], keywordsList[20][20];
char identifiers[20][20], operatorsList[20][20], delimitersList[20], literals[20][20], constants[20][20];

void lexicalAnalysis(char *str) {
    int i = 0, j = 0, l = 0;

    while (str[i] != '\0') {
        if (isIdentifier(str[i])) {
            while (isIdentifier(str[i])) {
                identifiers[identifierCount][j++] = str[i++];
            }
            identifiers[identifierCount][j] = '\0';
            identifierCount++;
            j = 0;
        } else if (str[i] == '\"') {
            literals[literalCount][l++] = str[i];
            for (j = i + 1; str[j] != '\"'; j++) {
                literals[literalCount][l++] = str[j];
            }
            literals[literalCount][l++] = str[j];
            literals[literalCount][l] = '\0';
            strcpy(literals[literalCount++], literals[literalCount - 1]);
            l = 0;
            i = j + 1;
        } else if (isOperator(str[i])) {
            while (isOperator(str[i])) {
                operatorsList[operatorCount][j++] = str[i++];
            }
            operatorsList[operatorCount][j] = '\0';
            operatorCount++;
            j = 0;
        } else if (isDelimiter(str[i])) {
            while (isDelimiter(str[i])) {
                delimitersList[delimiterCount++] = str[i++];
            }
        } else {
            i++;
        }
    }

    removeDuplicate();
    finalAnalysis();
}

int isIdentifier(char ch) {
    return isalpha(ch) || ch == '_' || isdigit(ch) || ch == '.';
}

int isOperator(char ch) {
    for (int i = 0; i < 8; i++) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}

int isDelimiter(char ch) {
    for (int i = 0; i < 8; i++) {
        if (ch == delimiters[i]) {
            return 1;
        }
    }
    return 0;
}

int isKeyword(char *str) {
    for (int i = 0; i < 5; i++) {
        if (!strcmp(keywords[i], str)) {
            return 1;
        }
    }
    return 0;
}

void removeDuplicate() {
    int i, j;

    int uqDelimiters[20] = {0};
    int uqIdentifiers[20] = {0};
    int uqOperators[20] = {0};

    for (i = 0; i < 20; i++) {
        uniqueDelimiterCount = 0;
        uniqueOperatorCount = 0;
        uniqueIdentifierCount = 0;
    }

    for (i = 1; i < delimiterCount + 1; i++) {
        if (!uqDelimiters[i - 1]) {
            uniqueDelimiters[uniqueDelimiterCount++] = delimitersList[i - 1];
            for (j = i; j < delimiterCount; j++) {
                if (delimitersList[i - 1] == delimitersList[j]) {
                    uqDelimiters[j] = 1;
                }
            }
        }
    }

    for (i = 1; i < identifierCount + 1; i++) {
        if (!uqIdentifiers[i - 1]) {
            strcpy(uniqueIdentifiers[uniqueIdentifierCount++], identifiers[i - 1]);
            for (j = i; j < identifierCount; j++) {
                if (!strcmp(identifiers[i - 1], identifiers[j])) {
                    uqIdentifiers[j] = 1;
                }
            }
        }
    }

    for (i = 1; i < operatorCount + 1; i++) {
        if (!uqOperators[i - 1]) {
            strcpy(uniqueOperators[uniqueOperatorCount++], operatorsList[i - 1]);
            for (j = i; j < operatorCount; j++) {
                if (!strcmp(operatorsList[i - 1], operatorsList[j])) {
                    uqOperators[j] = 1;
                }
            }
        }
    }
}

void finalAnalysis() {
    int i = 0, j;

    identifierCount = 0;

    for (i = 0; i < uniqueIdentifierCount; i++) {
        if (isKeyword(uniqueIdentifiers[i])) {
            strcpy(keywordsList[keywordCount++], uniqueIdentifiers[i]);
        } else if (isdigit(uniqueIdentifiers[i][0])) {
            strcpy(constants[constantCount++], uniqueIdentifiers[i]);
        } else {
            strcpy(identifiers[identifierCount++], uniqueIdentifiers[i]);
        }
    }

    printf("\n\tDelimiters are : \n");
    for (i = 0; i < uniqueDelimiterCount; i++) {
        printf("\t%c\n", uniqueDelimiters[i]);
    }

    printf("\n\tOperators are : \n");
    for (i = 0; i < uniqueOperatorCount; i++) {
        printf("\t%s\n", uniqueOperators[i]);
    }

    printf("\n\tIdentifiers are : \n");
    for (i = 0; i < identifierCount; i++) {
        printf("\t%s\n", identifiers[i]);
    }

    printf("\n\tKeywords are : \n");
    for (i = 0; i < keywordCount; i++) {
        printf("\t%s\n", keywordsList[i]);
    }

    printf("\n\tConstants are :\n");
    for (i = 0; i < constantCount; i++) {
        printf("\t%s\n", constants[i]);
    }

    printf("\n\tLiterals are :\n");
    for (i = 0; i < literalCount; i++) {
        printf("\t%s\n", literals[i]);
    }
}

int main() {
    char str[50];
    printf("\nEnter the string : ");
    scanf("%[^\n]c", str);
    lexicalAnalysis(str);
    return 0;
}
//hhah
