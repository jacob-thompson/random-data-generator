//
//  main.c
//  random-data-generator
//
//  Created by Jacob Thompson on 11/19/24.
//

#include "generator.h"

int main(int argc, char** argv)
{
    projectInfo();
    srand((int)time(NULL));

    struct generatedField first, middle, last, geo;

    first.flag = middle.flag = last.flag = geo.flag = 0;
    int customData, showEmail, showPhone;
    customData = showEmail = showPhone = 0;

    int opt;
    int entries = DEFAULT_NUMBER_OF_ENTRIES;
    while((opt = getopt(argc, argv, ARGS)) != -1)
    {
        switch (opt) {
            case 'c':
                sscanf(optarg, "%d", &entries);
                break;
            case 'f':
                customData++;
                first.flag = customData;
                break;
            case 'm':
                customData++;
                middle.flag = customData;
                break;
            case 'l':
                customData++;
                last.flag = customData;
                break;
            case 'g':
                customData++;
                geo.flag = customData;
                break;
            case 'e':
                customData++;
                showEmail = customData;
                break;
            case 'p':
                customData++;
                showPhone = customData;
                break;
            default:
                return argumentError(argv[0]);
        }
    }

    if (entries < 0)
        return valueError();

    char* header = malloc(sizeof(BUF_SIZE));
    if (customData)
    {
        if (first.flag)
            strcat(header, "First, ");
        if (middle.flag)
            strcat(header, "Middle, ");
        if (last.flag)
            strcat(header, "Last, ");
        if (geo.flag)
            strcat(header, "Geolocation, ");
        if (showEmail)
            strcat(header, "Email, ");
        if (showPhone)
            strcat(header, "Phone");
    } else
        strcat(header, "First, Middle, Last, Geolocation, Email, Phone");


    first.list = fopen(".data/first.txt", "r");
    middle.list = fopen(".data/middle.txt", "r");
    last.list = fopen(".data/last.txt", "r");
    geo.list = fopen(".data/geo.txt", "r");

    if (!first.list || !middle.list || !last.list || !geo.list)
        return readError();

    first.count = countList(first.list);
    middle.count = countList(middle.list);
    last.count = countList(last.list);
    geo.count = countList(geo.list);

    if (!first.count || !middle.count || !last.count || !geo.count)
        return unexpectedError();

    FILE* out = fopen("output.csv", "w+");
    fprintf(out, "%s\n", header);
    free(header);

    for (int id = 0; id < entries; id++)
    {
        char* firstEntry = getName(first.count, first.list);
        char* middleEntry = getName(middle.count, middle.list);
        char* lastEntry = getName(last.count, last.list);
        char* geoEntry = getName(geo.count, geo.list);
        char* emailEntry = getEmail(firstEntry, lastEntry);
        char* phoneEntry = getPhone();

        if (customData)
        {
            if (first.flag)
                fprintf(out, "%s, ", firstEntry);
            if (middle.flag)
                fprintf(out, "%s, ", middleEntry);
            if (last.flag)
                fprintf(out, "%s, ", lastEntry);
            if (geo.flag)
                fprintf(out, "%s, ", geoEntry);
            if (showEmail)
                fprintf(out, "%s, ", emailEntry);
            if (showPhone)
                fprintf(out, "%s", phoneEntry);

            fprintf(out, "\n");
        } else
            fprintf(out, "%s, %s, %s, %s, %s, %s\n", firstEntry, middleEntry, lastEntry, geoEntry, emailEntry, phoneEntry);

        free(firstEntry);
        free(middleEntry);
        free(lastEntry);
        free(geoEntry);
        free(emailEntry);
        free(phoneEntry);
    }

    fclose(out);

    if (customData && !showPhone)
        clean(out);

    return EXIT_SUCCESS;
}
