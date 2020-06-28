#include <stdio.h>
#include <stdlib.h>
 
void init(int *a) {
	free(a);
}
 
int main() {
	char *line;
	line = malloc(10);
    int *a = NULL;
    a = (int*) malloc(4 * sizeof(int));
    *a = 1;
    init(a);
    if (a == NULL) {
        printf("ERROR");
    } else {
        printf("OKAY...");
    }
    printf("%d", *a);
	a = (int*) malloc(4 * sizeof(int));
	float i = 0;
	while (i < 1000000)
	{
		i += 0.01f;
	}
}
