#include <stdio.h>
#include <string.h>

void squeeze(char s1[], char s2[]) {
	int i, j; // old index, new index
	int match = 0;
	for (i = j = 0; s1[i] != '\0'; i++) {
		for (int k = 0; !(match = (s1[i] == s2[k])) && s2[k] != '\0'; k++); // check for matches
		if (!match) s1[j++] = s1[i]; // set current char (s1[j] = s1[i]) and increment new index (j++)
	}
	s1[j] = '\0';
}

int main(int argc, char *argv[]) {
	if (argc >= 3) {
		char old[256];
		strcpy(old, argv[1]);
		squeeze(argv[1], argv[2]);
		printf("%s - %s => %s \n", old, argv[2], argv[1]);
	}
	return 0;
}
