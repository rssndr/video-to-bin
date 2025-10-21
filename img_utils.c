#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int img_to_bin(char* img) {
        FILE*   img_fp;         // img file pointer
        FILE*   bin_fp;         // bin file pointer
        off_t   img_size;       // img size in bytes
        char*   img_buf;        // buffer to store img data

        img_fp = fopen(img, "rb");

        if (img_fp == NULL) {
                perror("[E] Open image");
                return EXIT_FAILURE;
        }

        if (fseek(img_fp, 0, SEEK_END) == -1) {
                perror("[E] Image size");
                return EXIT_FAILURE;
        }
        img_size = ftell(img_fp);
        if (img_size == -1) {
                perror("[E] Image size");
                return EXIT_FAILURE;
        }
        printf("Image size: %ld B\n", img_size);
        rewind(img_fp);

        img_buf = malloc(img_size);
        if (img_buf == NULL) {
                perror("[E] Memory allocation");
                return EXIT_FAILURE;
        }

        if (!fread(img_buf, img_size, 1, img_fp)) {
                perror("[E] Read");
                free(img_buf);
                return EXIT_FAILURE;
        }

        if (fclose(img_fp) != 0) {
                perror("[E] Close image");
                free(img_buf);
                return EXIT_FAILURE;
        }

        bin_fp = fopen("./build/img.bin", "wb");
        if (bin_fp == NULL) {
                perror("[E] Open binary");
                free(img_buf);
                return EXIT_FAILURE;
        }

        if (!fwrite(img_buf, img_size, 1, bin_fp)) {
                perror("[E] Write");
                free(img_buf);
                fclose(bin_fp);
                return EXIT_FAILURE;
        }

        if (fclose(bin_fp) != 0) {
                perror("[E] Close binary");
                free(img_buf);
                return EXIT_FAILURE;
        }

        free(img_buf);

        return EXIT_SUCCESS;
}

