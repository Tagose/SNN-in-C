#pragma once

// Reads a specific line from the MNIST CSV.
// Fills your 784-element array with 0.0-1.0 intensities and returns the actual digit label.
int load_mnist_image(const char* filepath, int target_line, float* pixel_intensities, int* out_label);