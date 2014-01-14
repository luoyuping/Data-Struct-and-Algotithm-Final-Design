#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	FILE* fp;
	int m;
	fp=fopen("test.txt","wt");
    scanf("%d",&m);
    fprintf(fp, "%d\n", &m);
    fprintf(fp, "%d\n", m);
    fclose(fp);
	return 0;
}