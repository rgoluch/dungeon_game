#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>


/* Do not modify write_pgm() or read_pgm() */
int write_pgm(char *file, void *image, uint32_t x, uint32_t y) {
    FILE *o;

    if (!(o = fopen(file, "w"))) {
        perror(file);

        return -1;
    }

    fprintf(o, "P5\n%u %u\n255\n", x, y);

    /* Assume input data is correctly formatted. *
     * There's no way to handle it, otherwise.   */

    if (fwrite(image, 1, x * y, o) != (x * y)) {
        perror("fwrite");
        fclose(o);

        return -1;
    }

    fclose(o);

    return 0;
}

/* A better implementation of this function would read the image dimensions *
 * from the input and allocate the storage, setting x and y so that the     *
 * user can determine the size of the file at runtime.  In order to         *
 * minimize complication, I've written this version to require the user to  *
 * know the size of the image in advance.                                   */
int read_pgm(char *file, void *image, uint32_t x, uint32_t y)
{
    FILE *f;
    char s[80];
    unsigned i, j;

    if (!(f = fopen(file, "r"))) {
        perror(file);

        return -1;
    }

    if (!fgets(s, 80, f) || strncmp(s, "P5", 2)) {
        fprintf(stderr, "Expected P6\n");

        return -1;
    }

    /* Eat comments */
    do {
        fgets(s, 80, f);
    } while (s[0] == '#');

    if (sscanf(s, "%u %u", &i, &j) != 2 || i != x || j != y) {
        fprintf(stderr, "Expected x and y dimensions %u %u\n", x, y);
        fclose(f);

        return -1;
    }

    /* Eat comments */
    do {
        fgets(s, 80, f);
    } while (s[0] == '#');

    if (strncmp(s, "255", 3)) {
        fprintf(stderr, "Expected 255\n");
        fclose(f);

        return -1;
    }

    if (fread(image, 1, x * y, f) != x * y) {
        perror("fread");
        fclose(f);

        return -1;
    }

    fclose(f);

    return 0;
}

int main(int argc, char* argv[]){
    uint8_t image[1024][1024];
    uint8_t output[1024][1024];
    int32_t x[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int32_t y[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

    /* Example usage of PGM functions */
    /* This assumes that motorcycle.pgm is a pgm image of size 1024x1024 */
    read_pgm("motorcycle.pgm", image, 1024, 1024);

    /* After processing the image and storing your output in "out", write *
    * to motorcycle.edge.pgm.                                            */
    
    //Check to make sure that file name was provided
    if(argc == 1){
        printf("Error: No File Name Provided\n");
        return -1;
    }

    //Allocate enough memory for file name and then copy that data 
    char* pFileName = malloc(sizeof(char)* strlen(argv[1]));
    strncpy(pFileName, argv[1], strlen(argv[1]));

    //printf("File Name: %s\n", pFileName);
    //Image pointer, initialized to null to be safe;
    void* pImage = NULL;

    // Sobel Filter code
   for(int r = 0; r < 1024; r++){
       for(int c = 0; c < 1024; c++){
           int16_t accumulator_x = 0;
           int16_t accumulator_y = 0;
           int16_t out = 0;

           for(int i = 0; i < 3; i++){
               for(int j = 0; j < 3; j++){
                   if(r != 0 && c != 0 && r != 1023 && c != 1023){
                    accumulator_x = accumulator_x + (x[i][j]*(int16_t)image[r + (int)(j-ceil(3/2))][c + (int)(i-ceil(3/2))]);
                    accumulator_y = accumulator_y + (y[i][j]*(int16_t)image[r + (int)(j-ceil(3/2))][c + (int)(i-ceil(3/2))]);
                   }
               }
           }
           out = round(sqrt(pow(accumulator_x, 2) + pow(accumulator_y, 2)));
           if (out > 255){
               out = 255;
           }
           output[r][c] = out;
       }
   }

    write_pgm("motorcycle.edge.pgm", output, 1024, 1024);


    free(pFileName);
    return 0;
}