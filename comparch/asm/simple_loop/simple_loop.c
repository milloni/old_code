int f(void) {
	int sum = 0;
	int i = 0xff;
	do {
		sum += i;
		i--;
	} while (i > 0);
	return sum;
}

