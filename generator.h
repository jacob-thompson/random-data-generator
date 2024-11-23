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
#include <unistd.h>

#define ARGS "c:fmlgep"
#define PROJECT_NAME "random-data-generator"

#define BUF_SIZE 64
#define BYTES_TO_OVERWRITE 3
#define DEFAULT_NUMBER_OF_ENTRIES 500
#define MIN_3DIGIT 100
#define MAX_3DIGIT 999
#define MIN_4DIGIT 1000
#define MAX_4DIGIT 9999
#define POSSIBLE_EMAIL_DOMAINS 6

struct generatedField
{
    FILE* list;
    unsigned short count;
    int flag;
};

void clean(FILE* output);

char* withoutCapsAndSpaces(char* email);

char* getPhone(void);

char* getEmail(char* first, char* last);

char* getName(unsigned short count, FILE* list);

unsigned short countList(FILE* file);

int unexpectedError(void);

int readError(void);

int argumentError(char* command);

int valueError(void);

void projectInfo(void);
