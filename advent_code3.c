#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct num_array {
	int size;
	char *nums;
} num_array;

num_array *create_array(char *seq)
{
	volatile int length = strlen(seq);

	num_array *array = malloc(sizeof(num_array));
	array->size = length;
	array->nums = malloc(length);

	for (int i = 0; i < length; i++) {
		array->nums[i] = seq[i] - '0';
	}

	return array;
}

long long scan_array(num_array *array)
{
	int count_index = 12;
	int indicies[count_index];

	memset(indicies, -1, count_index * sizeof(int));
	
	int current_index = 0;
	for (int cur = 0; cur <= count_index - 1; cur++) {
		for (int i = current_index; i < array->size - (count_index - cur - 1); i++) {
			if (indicies[cur] == -1 || array->nums[indicies[cur]] < array->nums[i]) {
				current_index = i;
				indicies[cur] = i;
			}
		}

		current_index++;
	}
	long long total = 0;
	for (int i = 0; i < count_index; i++) {
		total += array->nums[indicies[i]] * pow(10, (count_index - i - 1));
	}



	return total;
}

void print_num_array(num_array *nums)
{
	for (int i = 0; i < nums->size; i++) {
		printf("%d, ", nums->nums[i]);
	}

	printf("\n");
}

int main(int nargs, char *argv[])
{
	FILE *file = fopen("data_day3.txt", "r");

	char buf[64];
	char c;
	int iter = 0;
	long long total = 0;
	num_array *array;
	while ((c = fgetc(file)) != EOF) {
		if (c == '\n') {
			buf[iter] = 0;
			iter = 0;
			array = create_array(buf);
			total += scan_array(array);
			print_num_array(array);
			free(array->nums);
			free(array);
			continue;
		}

		if (c < '0' || c > '9')
			continue;
		buf[iter] = c;
		iter++;
	}

	printf("Total: %llu\n", total);

	return 0;
}
