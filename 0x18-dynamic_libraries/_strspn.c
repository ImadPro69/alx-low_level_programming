unsigned int _strspn(char *s, char *accept)
{
    unsigned int count = 0;
    int isFound;

    while (*s != '\0') {
        isFound = 0;

        while (*accept != '\0') {
            if (*s == *accept) {
                count++;
                isFound = 1;
                break;
            }
            accept++;
        }

        if (isFound == 0)
            break;

        s++;
    }

    return count;
}

