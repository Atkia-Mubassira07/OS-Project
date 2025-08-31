#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <complex.h>

typedef struct {
    int thread_id;
    int width, height, max_iter;
    double xmin, xmax, ymin, ymax;
    int *image;
} ThreadData;

void *compute_mandelbrot(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int id = data->thread_id;

    for (int row = id; row < data->height; row += 8) { // thread processes every 8th row
        for (int col = 0; col < data->width; col++) {
            double x0 = data->xmin + col * (data->xmax - data->xmin) / (data->width - 1);
            double y0 = data->ymin + row * (data->ymax - data->ymin) / (data->height - 1);

            double complex z = 0 + 0*I;
            double complex c = x0 + y0*I;

            int iter = 0;
            while (cabs(z) <= 2.0 && iter < data->max_iter) {
                z = z*z + c;
                iter++;
            }

            // Map to grayscale (0=black, 255=white)
            int color = (iter == data->max_iter) ? 0 : (255 - (255 * iter / data->max_iter));
            data->image[row * data->width + col] = color;
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 9) {
        fprintf(stderr, "Usage: %s <width> <height> <xmin> <xmax> <ymin> <ymax> <max_iter> <output.ppm>\n", argv[0]);
        return 1;
    }

    // Parse arguments safely
    int width = (int)strtol(argv[1], NULL, 10);
    int height = (int)strtol(argv[2], NULL, 10);
    double xmin = strtod(argv[3], NULL);
    double xmax = strtod(argv[4], NULL);
    double ymin = strtod(argv[5], NULL);
    double ymax = strtod(argv[6], NULL);
    int max_iter = (int)strtol(argv[7], NULL, 10);
    char *filename = argv[8];

    // Debug print to confirm args are correct
    printf("Width=%d, Height=%d, xmin=%.2f, xmax=%.2f, ymin=%.2f, ymax=%.2f, max_iter=%d\n",
           width, height, xmin, xmax, ymin, ymax, max_iter);

    // Allocate image buffer
    int *image = malloc(width * height * sizeof(int));
    if (!image) {
        perror("malloc failed");
        return 1;
    }

    // Create threads
    pthread_t threads[8];
    ThreadData thread_data[8];

    for (int i = 0; i < 8; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].width = width;
        thread_data[i].height = height;
        thread_data[i].xmin = xmin;
        thread_data[i].xmax = xmax;
        thread_data[i].ymin = ymin;
        thread_data[i].ymax = ymax;
        thread_data[i].max_iter = max_iter;
        thread_data[i].image = image;

        pthread_create(&threads[i], NULL, compute_mandelbrot, &thread_data[i]);
    }

    for (int i = 0; i < 8; i++) {
        pthread_join(threads[i], NULL);
    }

    // Write image to PPM file
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("fopen failed");
        free(image);
        return 1;
    }
    fprintf(fp, "P3\n%d %d\n255\n", width, height);
    for (int i = 0; i < width * height; i++) {
        int c = image[i];
        fprintf(fp, "%d %d %d ", c, c, c); // grayscale
        if ((i + 1) % width == 0) fprintf(fp, "\n");
    }
    fclose(fp);

    free(image);
    printf("Mandelbrot image saved to %s\n", filename);
    return 0;
}

