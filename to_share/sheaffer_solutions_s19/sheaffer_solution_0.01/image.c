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

int main(int argc, char* argv[]){

    uint32_t x[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    uint32_t y[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};

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
    write_pgm(pFileName,pImage,x,y);

    free(pFileName);
    return 0;
}