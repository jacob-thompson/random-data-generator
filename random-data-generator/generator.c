//
//  generator.c
//  random-data-generator
//
//  Created by Jacob Thompson on 11/20/24.
//

#include "generator.h"

char* withoutCapsAndSpaces(char* str)
{
    int count = 0;
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
        if (str[i] != ' ')
            str[count++] = str[i];
    }

    str[count] = '\0';

    return str;
}

char* getPhone(void)
{
    char* phoneNumber = malloc(BUF_SIZE * sizeof(char));

    unsigned short area, exchange, line;
    area = rand() % (MAX_3DIGIT + 1 - MIN_3DIGIT) + MIN_3DIGIT;
    exchange = rand() % (MAX_3DIGIT + 1 - MIN_3DIGIT) + MIN_3DIGIT;
    line = rand() % (MAX_4DIGIT + 1 - MIN_4DIGIT) + MIN_4DIGIT;

    sprintf(phoneNumber, "(%d) %d - %d", area, exchange, line);

    return phoneNumber;
}

char* getEmail(char* first, char* last)
{
    char* email = malloc(BUF_SIZE * sizeof(char));
    strcat(email, first);

    unsigned short domain = rand() % POSSIBLE_EMAIL_DOMAINS + 1;

    switch (domain)
    {
        case 1:
            strcat(email, last);
            strcat(email, "@gmail.com");
            return withoutCapsAndSpaces(email);
            break;
        case 2:
            strcat(email, last);
            strcat(email, "@yahoo.com");
            return withoutCapsAndSpaces(email);
            break;
        case 3:
            strcat(email, last);
            strcat(email, "@outlook.com");
            return withoutCapsAndSpaces(email);
            break;
        case 4:
            strcat(email, last);
            strcat(email, "@hotmail.com");
            return withoutCapsAndSpaces(email);
            break;
        case 5:
            strcat(email, last);
            strcat(email, "@aol.com");
            return withoutCapsAndSpaces(email);
            break;
        default:
            strcat(email, "@");
            strcat(email, last);
            strcat(email, ".com");
            return withoutCapsAndSpaces(email);
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
    char* buffer = malloc(BUF_SIZE * sizeof(char));
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

    free(buffer);
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
