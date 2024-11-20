//
//  main.c
//  random-data-generator
//
//  Created by Jacob Thompson on 11/19/24.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PROJECT_NAME "random-data-generator"
#define BUF_SIZE 64

char* withoutCaps(char* str)
{
    for (int i = 0; i < strlen(str); i++)
        str[i] = tolower(str[i]);

    return str;
}

char* getPhone(void)
{
    char* phoneNumber = malloc(BUF_SIZE * sizeof(char));

    unsigned short area, exchange, line;
    area = rand() % 999 + 100;
    exchange = rand() % 999 + 100;
    line = rand() % 9999 + 1000;

    sprintf(phoneNumber, "(%d) %d - %d", area, exchange, line);

    return phoneNumber;
}

char* getEmail(char* first, char* last)
{
    char* email = malloc(BUF_SIZE * sizeof(char));
    strcat(email, first);
    strcat(email, last);

    char* gmail = "@gmail.com";
    char* yahoo = "@yahoo.com";
    char* outlook = "@outlook.com";
    char* hotmail = "@hotmail.com";
    char* aol = "@aol.com";
    unsigned short domain = rand() % 7 + 1;

    switch (domain)
    {
        case 1:
            strcat(email, gmail);
            return withoutCaps(email);
            break;
        case 2:
            strcat(email, yahoo);
            return withoutCaps(email);
            break;
        case 3:
            strcat(email, outlook);
            return withoutCaps(email);
            break;
        case 4:
            strcat(email, hotmail);
            return withoutCaps(email);
            break;
        case 5:
            strcat(email, aol);
            return withoutCaps(email);
            break;
        default:
            strcat(email, "@");
            strcat(email, last);
            strcat(email, ".com");
            return withoutCaps(email);
            break;
    }
}

char* getName(unsigned short count, FILE* list)
{
    char* line = malloc(BUF_SIZE * sizeof(char));

    unsigned short increment = 1;
    unsigned short random = rand() % count + 1;

    while (fgets(line, BUF_SIZE, list) != NULL)
    {
        if (increment == random)
        {
            unsigned long len = strlen(line);
            line[len - 1] = '\0';

            fseek(list, 0, SEEK_SET);

            return line;
        } else
            increment++;
    }

    return "N/A";
}

unsigned short countList(FILE* file)
{
    char buffer[BUF_SIZE];
    unsigned short counter = 0;

    for (;;)
    {
        size_t res = fread(buffer, 1, BUF_SIZE, file);
        if (ferror(file))
            return 0;

        for (int i = 0; i < res; i++)
            if (buffer[i] == '\n')
                counter++;

        if (feof(file))
            break;
    }

    fseek(file, 0, SEEK_SET);

    return counter;
}

int unexpectedError(void)
{
    fprintf(stderr, "AN UNEXPECTED ERROR HAS OCCURRED. ");
    fprintf(stderr, "PLEASE SUBMIT AN ISSUE REPORT HERE:\n");
    fprintf(stderr, "\thttps://github.com/jacob-thompson/%s/issues\n", PROJECT_NAME);

    return EXIT_FAILURE;
}

int readError(void)
{
    fprintf(stderr, "FAILED TO OPEN ONE OR MORE LIST FILES\n");

    return EXIT_FAILURE;
}

void projectInfo(void)
{
    fprintf(stdout, "%s ", PROJECT_NAME);
    fprintf(stdout, "https://github.com/jacob-thompson/%s/\n", PROJECT_NAME);
}

int main(int argc, const char** argv)
{
    projectInfo();
    srand((int)time(NULL));

    FILE* flist = fopen("first.txt", "r");
    FILE* mlist = fopen("middle.txt", "r");
    FILE* llist = fopen("last.txt", "r");
    FILE* plist = fopen("place.txt", "r");
    unsigned short firstCount, middleCount, lastCount, placeCount;

    if (flist == NULL || mlist == NULL || llist == NULL || plist == NULL)
        return readError();
    else
    {
        firstCount = countList(flist);
        middleCount = countList(mlist);
        lastCount = countList(llist);
        placeCount = countList(plist);
    }

    if (firstCount == 0 || middleCount == 0 || lastCount == 0 || placeCount == 0)
        return unexpectedError();

    FILE* out = fopen("output.csv", "w+");
    fprintf(out, "ID, First, Middle, Last, Location, Email, Phone\n");

    for (int id = 0; id < 100; id++)
    {
        char* first = getName(firstCount, flist);
        char* middle = getName(middleCount, mlist);
        char* last = getName(lastCount, llist);
        char* location = getName(placeCount, plist);
        char* email = getEmail(first, last);
        char* phone = getPhone();

        fprintf(out, "%d, %s, %s, %s, %s, %s, %s\n", id, first, middle, last, location, email, phone);

        free(first);
        free(middle);
        free(last);
        free(location);
        free(email);
        free(phone);
    }

    return EXIT_SUCCESS;
}
