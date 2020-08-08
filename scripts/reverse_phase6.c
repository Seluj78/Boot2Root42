#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void read_six_numbers(char *string, int loaded[6])
{
	int readed;

	readed = sscanf(string, "%d %d %d %d %d %d", &loaded[0], &loaded[1],
					&loaded[2], &loaded[3], &loaded[4], &loaded[5]);

	if (readed < 6)
	{
		printf("Fail on sscanf\n");
		exit(0);
	}
}

void func6(char *str)
{
	int readed[6];
	int result[6];
	int iVar4 = 0;
	int iVar2 = 0;

	printf("String: %s\n", str);
	read_six_numbers(str, readed);
	for (int index = 0; index < 6; index++)
	{
		printf("Readed[%d]: %d, ", index, readed[index]);
	}
	printf("\n");
	do
	{
		if (5 < readed[iVar4] - 1U)
		{
			printf("Fail: Number cannot be superior to 6\n");
			exit(0);
		}
		iVar2 = iVar4 + 1;
		if (iVar2 <= 5)
		{
			do
			{
				if (readed[iVar4] == readed[iVar2])
				{
					printf("Fail: Cannot have two times the same number (readed[%d]: %d| readed[%d]: %d)\n", iVar4, readed[iVar4], iVar2, readed[iVar2]);
					exit(0);
				}
				iVar2 += 1;

			} while (iVar2 <= 5);
		}
		iVar4 += 1;
	} while (iVar4 <= 5);
	printf("Passed this test\n");
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		printf("Arguments missing\n");
		return (0);
	}
	func6(argv[1]);
	return 0;
}
