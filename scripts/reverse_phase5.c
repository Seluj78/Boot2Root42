#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include  <string.h>

int get_index(char* string, char c) {
    char *e = strchr(string, c);
    if (e == NULL) {
        return -1;
    }
    return (int)(e - string);
}

int main(int ac, char **av)
{
    char *charset = "isrveawhobpnutfg";
    char *giants = "giants";
    for (int giants_idx = 0; giants_idx < 6; giants_idx++)
    {
        int charindex = get_index(charset, giants[giants_idx]);
        printf("%c Matches: ", giants[giants_idx]);
        for (int i = 97; i < 123; i++)
        {
            if ((i & 15) == charindex)
            {
                printf("%c ", (char)i);
            }
        }
        printf("\n");
    }
    return (0);
}
