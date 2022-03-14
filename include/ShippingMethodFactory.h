#ifndef SHIPPINGMETHODFACTORY_H_INCLUDED
#define SHIPPINGMETHODFACTORY_H_INCLUDED

#include "ShippingMethod.h"
#include "Exceptions.h"
/**
* Implementation of a strategy pattern. Determines the appropriate
* shipping method for an orderbased on an input @parameter, in this case
* weight.
*/

class ShippingMethodFactory {
 public:
  /**
  * The weight limits for the vehicle types used for shipping orders.
  * The shipping vehicle limits are:
  *  1. Truck - orders <= 100 kg.
  *  2. Air - orders > 100 and <= 1000 kg.
  *  3. Train - orders > 1000 and <= 10000 kg.
  *  4. Ship - orders > 10000 kg.
  */
  static const int TRUCK = 100;
  static const int AIR = 1000;
  static const int TRAIN = 10000;

  /**
  * Returns a pointer to an appropriate shipping method strategy.
  * @param[in] weight used to determine correct shipping strategy.
  * @return A shipping method based on the weight of the order.
  * @throws invalid_parameter_error if weight is negative.
  */
  ShippingMethod* getShippingMethod(const double weight);
};

#endif // SHIPPINGMETHODFACTORY_H_INCLUDED
