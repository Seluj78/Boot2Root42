#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int32_t func4(int32_t arg_8h)
{
    int32_t iVar1;
    int32_t iVar2;
    int32_t var_18h;

    if (arg_8h < 2) {
        iVar2 = 1;
    }
    else
    {
        iVar1 = func4(arg_8h + -1);
        iVar2 = func4(arg_8h + -2);
        iVar2 = iVar2 + iVar1;
    }
    return iVar2;
}

int main(int ac, char **av)
{
    int i = atoi(av[1]);
    printf("Passed: %d | Res: %d\n", i, func4(i));
}
