#include "product.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define SZ_STRING 30

struct SProduct {
    int id;
    char name[SZ_STRING];
    double price;
    char *strBuffer;
};

Product Product_create(int id, char *name, double price) {
    Product created = (Product) calloc(sizeof(struct SProduct), 1);

    created->id = id;
    created->price = price;
    created->strBuffer = NULL;
    strcpy(created->name, name);

    return created;
}

void Product_print(Product _this) {
    printf("%s", Product_toString(_this));
}

int Product_delete(Product _this) {
    if (_this && _this->strBuffer) free(_this->strBuffer);
    free(_this);

    if (!_this) {
        return 1;
    }
    return 0;
}

void Product_deleteMultiple(Product *products, int count, bool deleteSelf) {
    int failed = 0;
    for (int i = 0; i < count; i++) {
        failed += Product_delete(products[i]);
    }

    if (deleteSelf) free(products);
}

int Product_getId(Product _this) {
    return _this->id;
}

double Product_getPrice(Product _this) {
    return _this->price;
}

void Product_setPrice(Product _this, double newPrice) {
    _this->price = newPrice;
}

char *Product_getName(Product _this) {
    return _this->name;
}

void Product_setName(Product _this, char *newName) {
    strcpy(_this->name, newName);
}

int getDataSize () {
    return sizeof (struct SProduct);
}

bool Product_compare(Product a, Product b) {
    if (a->id != b->id) return false;
    if (strcmp(a->name, b->name) != 0) return false;
    if (a->price != b->price) return false;

    return true;
}

char *Product_toString(Product _this) {
    char *str = (char *) malloc(sizeof (char) * (SZ_STRING + 30));
    sprintf(str, "[%d] %s : %lf", _this->id, _this->name, _this->price);

    str = (char *) realloc(str, sizeof (char) * (strlen(str) + 1));
    _this->strBuffer = str;

    return str;
}