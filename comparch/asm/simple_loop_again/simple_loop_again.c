int simple_loop_again(void) {
	int sum = 0;
	char *str = "Fear of the duck";
	int i = 0;
	while (str[i] != '\0') {
		sum += str[i];
		i++;
	}
	return sum;
}

