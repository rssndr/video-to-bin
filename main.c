#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
        FILE*   img_fp;         // img file pointer
        FILE*   bin_fp;         // bin file pointer
        off_t   img_size;       // img size in bytes
        char*   img_buf;        // buffer to store img data

        img_fp = fopen("./img/pfp.jpg", "rb");

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
                return EXIT_FAILURE;
        }

        if (fclose(img_fp) != 0) {
                perror("[E] Close image");
                return EXIT_FAILURE;
        }

        bin_fp = fopen("./img.bin", "wb");
        if (bin_fp == NULL) {
                perror("[E] Open binary");
                return EXIT_FAILURE;
        }

        if (!fwrite(img_buf, img_size, 1, bin_fp)) {
                perror("[E] Write");
                return EXIT_FAILURE;
        }

        if (fclose(bin_fp) != 0) {
                perror("[E] Close binary");
                return EXIT_FAILURE;
        }

        free(img_buf);

        return 0;
}

