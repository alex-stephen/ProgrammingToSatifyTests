#include "Order.h"
#include "Waitlist.h"
#include <iostream>
#include <vector>
#include <map>

void Waitlist::checkAll() {
  std::vector<Order*> o;
  for (Order* order : pendingOrders) {
    bool temp = order->submit();
    if (temp)
      o.push_back(order);
  }
  for (auto order : o) {
        removeOrder(order);
  }
}

void Waitlist::addOrder(Order* order) {
  if (order == nullptr)
    throw invalid_parameter_error("Order is a nullptr.");
  pendingOrders.push_back(order);
}

void Waitlist::removeOrder(Order* order) {
  if (order == nullptr)
    throw invalid_parameter_error("Order is a nullptr.");
  pendingOrders.remove(order);
}

int Waitlist::size() {
  return pendingOrders.size();
}
