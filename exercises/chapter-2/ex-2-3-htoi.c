#include <stdio.h>
#include <ctype.h>

int htoi(char hex[]) {
	int decimal = 0;
	int i = 0;
	if (hex[0] == '0' && tolower(hex[1]) == 'x') i = 2; // ignore 0x or 0
	while (hex[i] != '\0') {
		decimal = decimal << 4; // multiply by 16 (shift 4 bits)
		if (isdigit(hex[i])) decimal += hex[i] - '0';
		else if (isalpha(hex[i]) && ('a' <= tolower(hex[i]) <= 'f')) decimal += tolower(hex[i]) - 'a' + 10;
		i++;
	}
	return decimal;
}

int main(int argc, char *argv[]) {
	if (argc > 1) printf("%s : %d\n", argv[1], htoi(argv[1]));
	return 0;
}
