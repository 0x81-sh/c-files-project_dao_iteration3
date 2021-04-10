#include "product_dao.h"
#include "backend.h"
#include <stdlib.h>
#include <string.h>

#define STR_SZ 60

struct SProductDAO {
    char filename[STR_SZ];
};

ProductDAO ProductDAO_create(char* filename) {
    ProductDAO new = (ProductDAO) malloc(sizeof (struct SProductDAO));
    strncpy(new->filename, filename, STR_SZ);

    return new;
}

void ProductDAO_write(ProductDAO _this, Product p) {
    FP fp = openWrapper(_this->filename, "ab");
    writeArbitrary(fp, 1, p);

    fclose(fp);
}

Product ProductDAO_read(ProductDAO _this, int position) {
    FP fp = openWrapper(_this->filename, "rb");

    Product *readP = readArbitrary(fp, position, 1);
    Product read = readP[0];
    free(readP);

    fclose(fp);
    return read;
}

void ProductDAO_writeAll(ProductDAO _this, Product* products, int count) {
    FP fp = openWrapper(_this->filename, "wb");
    writeArbitrary(fp, count, products);

    fclose(fp);
}

Product* ProductDAO_readAll(ProductDAO _this, int *count) {
    FP fp = openWrapper(_this->filename, "rb");
    Product *array = readArbitrary(fp, 0, -1, count);

    fclose(fp);
    return array;
}

void ProductDAO_update(ProductDAO _this, Product new, int pos) {
    //Get original data
    int count = 0;
    FP fp = openWrapper(_this->filename, "rb");
    Product *originalData = readArbitrary(fp, 0, -1, &count);
    fclose(fp);

    //Check args
    if (pos >= count || pos < 0) {
        printf("Cannot update outside of array [%d]\n", count);
        return;
    }

    //Replace
    Product_delete(originalData[pos]);
    originalData[pos] = new;

    //Write
    fp = openWrapper(_this->filename, "wb");
    writeArbitrary(fp, count, originalData);
    originalData[pos] = NULL; //prevent passed value from getting freed
    fclose(fp);

    //Free read data
    Product_deleteMultiple(originalData, count, true);
}

void ProductDAO_deleteElement(ProductDAO _this, int pos) {
    //Get original
    int read = 0;
    FP fp = openWrapper(_this->filename, "rb");
    Product *array = readArbitrary(fp, 0, -1, &read);

    //Delete and shift
    Product_delete(array[pos]);
    for (int i = pos; i < read - 1; i++) {
        array[i] = array[i + 1];
    }

    //Close file and open in write mode
    fclose(fp);
    fp = openWrapper(_this->filename, "wb");

    //Write data
    writeArbitrary(fp, read - 1, array);
    Product_deleteMultiple(array, read - 1, true);

    fclose(fp);
}

void ProductDAO_delete(ProductDAO _this) {
    free(_this);
}