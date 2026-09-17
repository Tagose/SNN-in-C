#include "mnist_loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_mnist_image(const char* filepath, int target_line, float* pixel_intensities, int* out_label) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("Error: Could not open %s\n", filepath);
        return -1;
    }

    char line_buffer[10000]; // Big enough to hold 785 comma-separated numbers
    int current_line = 0;

    // Skip lines until we hit the one we want
    while (fgets(line_buffer, sizeof(line_buffer), file)) {
        if (current_line == target_line) {
            
            // The very first number in the CSV row is the label (e.g., "7")
            char* token = strtok(line_buffer, ",");
            *out_label = atoi(token);

            // The next 784 numbers are the pixels (0 to 255)
            for (int i = 0; i < 784; i++) {
                token = strtok(NULL, ",");
                if (token) {
                    // Convert to float and normalize to 0.0 - 1.0 for the Poisson encoder
                    pixel_intensities[i] = atof(token) / 255.0;
                } else {
                    pixel_intensities[i] = 0.0; // Safety fallback
                }
            }
            fclose(file);
            return 0; // Success
        }
        current_line++;
    }

    fclose(file);
    return -1; // Line not found
}