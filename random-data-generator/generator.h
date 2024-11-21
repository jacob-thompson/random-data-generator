//
//  generator.h
//  random-data-generator
//
//  Created by Jacob Thompson on 11/20/24.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUF_SIZE 64
#define MIN_3DIGIT 100
#define MAX_3DIGIT 999
#define MIN_4DIGIT 1000
#define MAX_4DIGIT 9999
#define POSSIBLE_EMAIL_DOMAINS 6
#define PROJECT_NAME "random-data-generator"

char* withoutCapsAndSpaces(char* str);

char* getPhone(void);

char* getEmail(char* first, char* last);

char* getName(unsigned short count, FILE* list);

unsigned short countList(FILE* file);

int unexpectedError(void);

int readError(void);

void projectInfo(void);
