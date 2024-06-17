#include<stdio.h>
#include<ctype.h>

int main() {
	
	int freq[26];
	for (int i=0; i<26; i++) freq[i]=0;

	int c;
	while ((c = getchar()) != EOF) {
		c = tolower(c);
		if (('a' <= c && c <='z')) ++freq[c-'a'];
	}

	for (int i=0; i<26; i++) {
		printf("%c (%2d) : ", i+'a', freq[i]);
		for (int j=0; j<freq[i]; j++) printf("#");
		printf("\n");
	}
}
