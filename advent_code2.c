#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

typedef struct id_range {
	char* start;
	char* end;
} id_range;

int count_digits(unsigned long long num)
{
	int count = 0;


	while (num > 0) {
		num = num / (long long) 10;
		count++;
	}

	return count;
}

id_range *get_next_range(char *ranges)
{
	static int next_count = 0;
	int cur_count = 0, index = 0;

	register char *parser = ranges;
	// Parse the commas to find num
	while (cur_count < next_count) {
		while(*(parser++) != ',') {
			if (parser > ranges + strlen(ranges)) {
				printf("None\n");
				return 0;
			}
		}
		cur_count++;
	}

	index = (parser-ranges);
	
	id_range *range = calloc(sizeof(id_range), 0);
	int digits_start = count_digits(atol(parser));
	range->start = calloc(digits_start + 1, 0);
	memcpy(range->start, parser, digits_start);
	range->start[digits_start] = 0;
	while (*(parser++) != '-');
	int digits_end = count_digits(atol(parser));
	range->end = calloc(digits_end + 1, 0);
	memcpy(range->end, parser, digits_end);
	range->end[digits_end] = 0;
		

	printf("START: %s\n", range->start);
	printf("END: %s\n", range->end);
	next_count++;
	return range;	
}

long long check_id(char* number)
{
	int length = strlen(number);
	
	if (length % 2)
		return 0; // Good ID

	char *second_half = number + (length/2);

	if (!strncmp(second_half, number, length/2)) {
		printf("%s\n", number);
		return atol(number);
	}

	return 0;
}

long long check_id2(char *number)
{
	int length = strlen(number);
	int digit_length = 1;
	while (digit_length <= length/2) {
		if (length % digit_length) {
			digit_length++;
			continue;
		}
		int iter = length / digit_length;
		int next = 0;
		for (int i = 1; i < iter; i++) {
			if (strncmp(number, number+(i*digit_length), digit_length)) {
				next = 1;
				break;
			}
		}
		if (!next) {
			return atol(number);
		}

		digit_length++;	
	}

	return 0;
}

int main(int argc, char *argv[])
{
	long long  total = 0;
	id_range *cur_range = 0;
	while (cur_range = get_next_range(argv[1])) {
		printf("ATOL START: %s, %s\n", cur_range->start, cur_range->end);
		for (long long i = atol(cur_range->start); i <= atol(cur_range->end); i++) {
			char str[64];
			sprintf(str, "%llu", i);
			
			total += check_id2(str);
			
		}
	}

	printf("Total: %llu\n", total);
	printf("Fertig\n");
	return 0;
}
