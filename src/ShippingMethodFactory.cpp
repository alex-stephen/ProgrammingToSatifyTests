#include "ShippingMethodFactory.h"

#include <iostream>

ShippingMethod *ShippingMethodFactory::getShippingMethod(const double weight) {
  if (weight < 0)
      throw invalid_parameter_error("Weight is a negative.");
  if (weight <= TRUCK) {
    return new Truck();
  } else if (weight > TRUCK && weight <= AIR) {
    return new Air();
  } else if (weight > AIR && weight <= TRAIN) {
    return new Train();
  } else {
    return new Ship();
  }
}
