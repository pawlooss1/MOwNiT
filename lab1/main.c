#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct Point {
    double x;
    double y;
} Point;

Point* generate_from_range(double range) {
    int size = 10000;
    Point* result = malloc(size * sizeof(Point));
    for (int i = 0; i < size; i++) {
        result[i].x = ((float) rand() / (float) RAND_MAX) * 2 * range - range;
        result[i].y = ((float) rand() / (float) RAND_MAX) * 2 * range - range;
    }
    return result;
}

Point* generate_on_line() {
    int size = 1000;
    Point* result = malloc(size * sizeof(Point));
    for (int i = 0; i < size; i++) {
        result[i].x = ((float) rand() / (float) RAND_MAX) * 2000 - 1000;
        result[i].y = 0.05 + 0.05 * result[i].x;
    }
    return result;
}

void write_points_tofile(Point* small, Point* big, Point* line) {
    FILE *f = fopen("points.dat", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < 1000; i++) {
        double x1 = small[i].x;
        double x2 = big[i].x;
        double x3 = line[i].x;
        double y1 = small[i].y;
        double y2 = big[i].y;
        double y3 = line[i].y;
        fprintf(f, "%f %f %f %f %f %f\n", x1, y1, x2, y2, x3, y3);
    }
    for (int i = 1000; i < 10000; i++) {
        double x1 = small[i].x;
        double x2 = big[i].x;
        double y1 = small[i].y;
        double y2 = big[i].y;
        fprintf(f, "%f %f %f %f\n", x1, y1, x2, y2);
    }

    fclose(f);
}

int main() {
    srand(time(NULL));
    Point* small_range_points = generate_from_range(1000.0);
    Point* big_range_points = generate_from_range(1e14);
    Point* points_on_line = generate_on_line();

    write_points_tofile(small_range_points, big_range_points, points_on_line);
    return 0;
}