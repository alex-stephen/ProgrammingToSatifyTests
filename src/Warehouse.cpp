#include "Warehouse.h"
#include <map>
#include <cmath>

Warehouse::Warehouse(Waitlist* w) {
  pending = w;
}

bool Warehouse::changeQuantity(Product* type, int quantity) {
    if (type == nullptr)
        throw invalid_parameter_error("Product is a nullptr.");

    int isNegative = inventory[type] + quantity;
    if (isNegative < 0)
      return false;

    inventory[type] = isNegative;
    if (quantity > 0)
      pending->checkAll();
    return true;
}

int Warehouse::checkQuantity(Product* type) {
  if (type == nullptr)
    throw invalid_parameter_error("Product is a nullptr.");
  return inventory[type];
}
