#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int **row;
static int **new_row;
static int width_init = 0;
static int height_init = 0;

int load_next_row(FILE* file)
{
	int *old_row1 = row[0];
	row[0] = row[1];
	row[1] = row[2];
	row[2] = old_row1;

	int column = 0;
	int line_found = 0;
	char c;
	while ((c = fgetc(file)) != EOF) {
		line_found = 1;
		if (c == '\n') break;

		if (c == '@') {
			row[2][column] = 1;
		} else {
			row[2][column] = 0;
		}

		column++;
	}

	if (!line_found) {
		printf("END OF FILE\n");
		memset(row[2], 0, sizeof(int) * width_init);
		return 0;
	}

	return 1;
}

void load_array(FILE *file)
{
	int column = 0;
	int row_i = 0;
	char c;
	while ((c = fgetc(file)) != EOF) {
		if (c == '\n') {
			column = 0;
			row_i++;
			continue;
		}
		
		if (c == '@') {
			row[row_i][column] = 1;
			new_row[row_i][column] = 1;
		} else {
			row[row_i][column] = 0;
			new_row[row_i][column] = 0;
		}

		column++;
	}
}

int check_cell(int cel_x, int cel_y)
{
	int surrounding = 0;	
	if (!row[cel_y][cel_x])
		return 0; // No toilet paper

	for (int x = cel_y-1; x < cel_y+2; x++) {
		for (int y = cel_x-1; y < cel_x+2; y++) {
			if (y < 0 || y >= width_init || x < 0 || x >= height_init)
				continue;
			if (row[x][y]) {
				surrounding++;
			}
		}

	}

	if (--surrounding >= 4) {
		return 0;
	}
	new_row[cel_y][cel_x] = 0;	
	return 1;
}

void print_rows()
{
	for (int i = 0; i < height_init; i++) {
		for (int y = 0; y < width_init; y++) {
			printf("%d ", row[i][y]);
		}
		printf("\n");
	}
}

int main() 
{
	FILE *chart = fopen("data_day4.txt", "r");

	char c;
	int stop_width = 0;
	while ((c = fgetc(chart)) != EOF) {
		if (c == '\n') {
			stop_width = 1;
			height_init ++;
		}

		if (!stop_width)
			width_init++;
	}

	rewind(chart);	

	row = malloc(height_init * sizeof(int *));
	new_row = malloc(height_init * sizeof(int *));
	
	for (int i = 0; i < height_init; i++) {
		row[i] = malloc(width_init * sizeof(int));
		new_row[i] = malloc(width_init * sizeof(int));
		memset(row[i], 0, width_init * sizeof(int));
		memset(new_row[i], 0, width_init * sizeof(int));
	}

	// INIT COMPLETED
	
	int grand_total = 0;
	int total = -1;
	load_array(chart);

	while (total) {
		total = 0;
		for (int x = 0; x < width_init; x++) {
			for (int y = 0; y < height_init; y++) {
				total += check_cell(x, y);
			}
		}

		printf ("total: %d\n", total);
		
		for (int x = 0; x < width_init; x++) {
			for (int y = 0; y < height_init; y++) {
				row[y][x] = new_row[y][x];
			}
		}
		grand_total += total;
	}
		
	printf("TOTAL: %d\n", grand_total);
	int test = 1;

	//print_rows();

	fclose(chart);
}
