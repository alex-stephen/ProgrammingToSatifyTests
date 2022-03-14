#include "ShippingMethod.h"
#include <string>

string ShippingMethod::name() {
  return shipName;
}

Air::Air() {
  shipName = "Air";
}

Truck::Truck() {
  shipName = "Truck";
}

Train::Train() {
  shipName = "Train";
}

Ship::Ship() {
  shipName = "Ship";
}
