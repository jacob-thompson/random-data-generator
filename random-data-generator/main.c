//
//  main.c
//  random-data-generator
//
//  Created by Jacob Thompson on 11/19/24.
//

#include "generator.h"

int main(int argc, const char** argv)
{
    projectInfo();
    srand((int)time(NULL));

    FILE* flist = fopen("data/first.txt", "r");
    FILE* mlist = fopen("data/middle.txt", "r");
    FILE* llist = fopen("data/last.txt", "r");
    FILE* plist = fopen("data/place.txt", "r");

    if (flist == NULL || mlist == NULL || llist == NULL || plist == NULL)
        return readError();

    const unsigned short firstCount = countList(flist);
    const unsigned short middleCount = countList(mlist);
    const unsigned short lastCount = countList(llist);
    const unsigned short placeCount = countList(plist);

    if (firstCount == 0 || middleCount == 0 || lastCount == 0 || placeCount == 0)
        return unexpectedError();

    FILE* out = fopen("output.csv", "w+");
    fprintf(out, "First, Middle, Last, Location, Email, Phone\n");

    for (int id = 0; id < 1000; id++)
    {
        char* first = getName(firstCount, flist);
        char* middle = getName(middleCount, mlist);
        char* last = getName(lastCount, llist);
        char* location = getName(placeCount, plist);
        char* email = getEmail(first, last);
        char* phone = getPhone();

        fprintf(out, "%s, %s, %s, %s, %s, %s\n", first, middle, last, location, email, phone);

        free(first);
        free(middle);
        free(last);
        free(location);
        free(email);
        free(phone);
    }

    return EXIT_SUCCESS;
}
