BEGIN {
	lines = 0;
}
	{ lines++; }
END {
	printf("The file %s has %d lines.\n", FILENAME, lines);
}
