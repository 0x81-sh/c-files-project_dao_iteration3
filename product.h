#pragma once
#include <stdbool.h>

typedef struct SProduct *Product;

Product Product_create(int id, char *name, double price);
void Product_print(Product _this);
int Product_delete(Product _this);
void Product_deleteMultiple(Product *products, int count, bool deleteSelf);
int Product_getId(Product _this);
double Product_getPrice(Product _this);
void Product_setPrice(Product _this, double newPrice);
char *Product_getName(Product _this);
void Product_setName(Product _this, char *newName);
int getDataSize();
bool Product_compare(Product a, Product b);
char *Product_toString(Product _this);