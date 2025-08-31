# Task D: Mandelbrot Fractal (Multithreading)

## Build
gcc -O2 -pthread mandelbrot.c -o mandelbrot -lm

## Run
./mandelbrot <width> <height> <xmin> <xmax> <ymin> <ymax> <max_iter> <output.ppm>

### Example
./mandelbrot 800 600 -2.0 0.47 -1.12 1.12 1000 mandelbrot.ppm
