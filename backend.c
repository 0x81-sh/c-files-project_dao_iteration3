#include "backend.h"
#include <stdlib.h>
#include <stdarg.h>

FP openWrapper (char *filename, char *mode) {
    FP fp = fopen(filename, mode);
    if (!fp) {
        printf("Cannot create or open file.\n");
        exit(1);
    }

    return fp;
}

/*
 * Returns array of products
 * Takes a pointer to an external counter for reporting amount of products when count > 1
 * Count -1 will read all from the provided file (starting from offset pos)
 */
Product* readArbitrary(FP fp, int pos, int count, ...) {
    if (count < 0 && count != -1) {
        printf("Cannot read 0 or less elements");
        return NULL;
    }

    //Obtain count of elements in file and set passed pointer
    if (count == -1) {
        fseek(fp, 0, SEEK_END);
        count = (int) (ftell(fp) / getDataSize());

        va_list args;
        va_start(args, count);
        int *ptr = va_arg(args, int *);
        va_end(args);

        *ptr = count;
    }

    int read = fseek(fp, (long) getDataSize() * pos, SEEK_SET);
    if (read != 0) {
        printf("Could not seek to position.\n");
        return NULL;
    }

    Product *array = (Product *) malloc(sizeof (Product) * count);

    for (int i = 0; i < count; i++) {
        array[i] = Product_create(0, "", 0);
        fread(array[i], getDataSize(), 1, fp);
    }

    return array;
}

/*
 * Takes either a product pointer or a product array as third parameter
 * When count > 1, Product*, else Product
 *
 * Position in file has been omitted, as when using append data is always written to end anyways, and write overwrites the whole file,
 * making the position parameter completely unnecessary
 */
void writeArbitrary(FP fp, int count, ...) {
    va_list args;
    va_start(args, count);

    if (count <= 1) {
        fwrite(va_arg(args, Product), getDataSize(), 1, fp);
        va_end(args);
        return;
    }

    Product *arr = va_arg(args, Product*);
    for (int i = 0; i < count; i++) {
        fwrite(arr[i], getDataSize(), 1, fp);
    }

    va_end(args);
}