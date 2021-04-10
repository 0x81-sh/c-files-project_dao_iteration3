#pragma once
#include "product.h"

typedef struct SProductDAO *ProductDAO;

ProductDAO ProductDAO_create(char* filename);
void ProductDAO_write(ProductDAO _this, Product p);
Product ProductDAO_read(ProductDAO _this, int position);
void ProductDAO_writeAll(ProductDAO _this, Product* products, int count);
Product* ProductDAO_readAll(ProductDAO _this, int *count);
void ProductDAO_update(ProductDAO _this, Product new, int pos);
void ProductDAO_deleteElement(ProductDAO _this, int pos);
void ProductDAO_delete(ProductDAO _this);