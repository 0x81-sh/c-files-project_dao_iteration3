#include <stdio.h>
#include <string.h>
#include "product.h"
#include "product_dao.h"

bool compareArray(Product *arr1, Product *arr2, int size);
void testSingle(ProductDAO productDao);
void testArray(ProductDAO productDao);
void testUpdate(ProductDAO productDao);
void testDelete(ProductDAO productDao);
void testToString();

int main() {
    ProductDAO file = ProductDAO_create("test.dat");
    remove("test.dat"); //make sure file is clean

    testSingle(file);
    testArray(file);
    testUpdate(file);
    testDelete(file);
    testToString();

    printf("All tests ran.\n");
    ProductDAO_delete(file);
    return 0;
}

bool compareArray(Product *arr1, Product *arr2, int size) {
    for (int i = 0; i < size; i++) {
        if (!Product_compare(arr1[i], arr2[i])) {
            printf("\tCompare trace:\n");

            printf("\t\tProduct %da: ", i);
            Product_print(arr1[i]);
            printf("\n\t\tProduct %db: ", i);
            Product_print(arr2[i]);
            printf("\n\t\t> Diff: %d\n", Product_compare(arr1[i], arr2[i]));

            return false;
        }
    }

    return true;
}

//only works on empty file as reads index 0
void testSingle(ProductDAO productDao) {
    Product testData = Product_create(1, "testProductX", 420.69);
    ProductDAO_write(productDao, testData);

    Product testData2 = ProductDAO_read(productDao, 0);

    if (!Product_compare(testData, testData2)) printf("Single add/read failed.\n");
    Product_delete(testData);
    Product_delete(testData2);
}

void testArray(ProductDAO productDao) {
    Product testArr[3] = {Product_create(1, "test", 2.0),
                          Product_create(2, "test2", 4.0),
                          Product_create(3, "test3", 6.0)};
    ProductDAO_writeAll(productDao, testArr, 3);

    int size = 0;
    Product *array = ProductDAO_readAll(productDao, &size);

    if (!compareArray(testArr, array, size) || size != 3) printf("Array write/read failed.\n");
    Product_deleteMultiple(array, size, true);
    Product_deleteMultiple(testArr, size, false);
}

void testUpdate(ProductDAO productDao) {
    Product testArr[3] = {Product_create(1, "test", 2.0),
                          Product_create(2, "test2", 4.0),
                          Product_create(3, "test3", 6.0)};
    ProductDAO_writeAll(productDao, testArr, 3);

    //modify all to test that modifications work on all ends of the array
    Product newData[3] = {Product_create(7, "test7", 7.0),
                          Product_create(8, "test8", 8.0),
                          Product_create(9, "test9", 9.0)};
    ProductDAO_update(productDao, newData[0], 0);
    ProductDAO_update(productDao, newData[1], 1);
    ProductDAO_update(productDao, newData[2], 2);

    int size = 0;
    Product *array = ProductDAO_readAll(productDao, &size);

    if (!compareArray(newData, array, size) || size != 3) printf("Product update failed.\n");
    Product_deleteMultiple(array, size, true);
    Product_deleteMultiple(testArr, size, false);
    Product_deleteMultiple(newData, size, false);
}

void testDelete(ProductDAO productDao) {
    Product testArr[3] = {Product_create(1, "test", 2.0),
                          Product_create(2, "test2", 4.0),
                          Product_create(3, "test3", 6.0)};
    ProductDAO_writeAll(productDao, testArr, 3);

    ProductDAO_deleteElement(productDao, 1);
    Product testArr2[2] = {Product_create(1, "test", 2.0),
                           Product_create(3, "test3", 6.0)};

    int size = 0;
    Product *array = ProductDAO_readAll(productDao, &size);

    if (!compareArray(array, testArr2, size) || size != 2) printf("Product delete failed.\n");
    Product_deleteMultiple(array, size, true);
    Product_deleteMultiple(testArr2, size, false);
    Product_deleteMultiple(testArr, 3, false);
}

void testToString() {
    Product testData = Product_create(5, "test", 45);
    char *shouldBe = "[5] test : 45.000000";
    char *is = Product_toString(testData);

    if (strcmp(shouldBe, is) != 0) printf("To string failed.\n");
    Product_delete(testData);
}