#include "Product.h"
#include <string>

Product::Product(string name, double pWeight) : id(name), weight(pWeight) {}

double Product::getWeight() {
  return weight;
}

string Product::getName() {
  return id;
}
