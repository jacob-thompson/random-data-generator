//
//  generator.c
//  random-data-generator
//
//  Created by Jacob Thompson on 11/20/24.
//

#include "generator.h"

void clean(FILE* output)
{
    output = fopen("output.csv", "r");
    FILE *temp = fopen("temp", "w+");

    char* line = malloc(BUF_SIZE * sizeof(char));
    while (fgets(line, BUF_SIZE, output) != NULL)
    {
        if (strstr(line, ", \n"))
        {
            unsigned long len = strlen(line);
            line[len - BYTES_TO_OVERWRITE] = '\0';
            fprintf(temp, "%s\n", line);
        }
    }

    fclose(output);
    fclose(temp);
    free(line);

    rename("temp", "output.csv");
}

char* withoutCapsAndSpaces(char* email)
{
    int count = 0;
    for (int i = 0; email[i]; i++)
    {
        email[i] = tolower(email[i]);
        if (email[i] != ' ')
            email[count++] = email[i];
    }

    email[count] = '\0';

    return email;
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
            break;
        case 2:
            strcat(email, last);
            strcat(email, "@yahoo.com");
            break;
        case 3:
            strcat(email, last);
            strcat(email, "@outlook.com");
            break;
        case 4:
            strcat(email, last);
            strcat(email, "@hotmail.com");
            break;
        case 5:
            strcat(email, last);
            strcat(email, "@aol.com");
            break;
        default:
            strcat(email, "@");
            strcat(email, last);
            strcat(email, ".com");
            break;
    }

    return withoutCapsAndSpaces(email);
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

int argumentError(char* command)
{
    fprintf(stderr, "Usage: %s [-%s]\n", command, ARGS);

    fprintf(stderr, "\t-c <INT>\n");
    fprintf(stderr, "\t\t Configures the number of entries to generate.\n");

    fprintf(stderr, "\t-f\n");
    fprintf(stderr, "\t\t Toggles the first name field.\n");

    fprintf(stderr, "\t-m\n");
    fprintf(stderr, "\t\t Toggles the middle name field.\n");

    fprintf(stderr, "\t-l\n");
    fprintf(stderr, "\t\t Toggles the last name field.\n");

    fprintf(stderr, "\t-g\n");
    fprintf(stderr, "\t\t Toggles the geolocation field.\n");

    fprintf(stderr, "\t-e\n");
    fprintf(stderr, "\t\t Toggles the email field.\n");

    fprintf(stderr, "\t-p\n");
    fprintf(stderr, "\t\t Toggles the phone number field.\n");

    return EXIT_FAILURE;
}

int valueError(void)
{
    fprintf(stderr, "INVALID VALUE PASSED TO ARG\n");

    return EXIT_FAILURE;
}

void projectInfo(void)
{
    fprintf(stdout, "%s ", PROJECT_NAME);
    fprintf(stdout, "https://github.com/jacob-thompson/%s/\n", PROJECT_NAME);
}
