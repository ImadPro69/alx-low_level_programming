#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *generate_key(const char *username)
{
    size_t i, username_len = strlen(username);
    char *key = malloc((username_len + 1) * sizeof(char));

    for (i = 0; i < username_len; i++) {
        key[i] = username[i] ^ (char)i;
    }

    key[i] = '\0';

    return key;
}

int main(int argc, char *argv[])
{
    const char *username;
    char *key;

    if (argc != 2) {
        printf("Usage: %s <username>\n", argv[0]);
        return 1;
    }

    username = argv[1];
    key = generate_key(username);

    printf("%s\n", key);

    free(key);

    return 0;
}
