#include "Order.h"
#include <iostream>
#include <map>
#include <utility>

Order::Order(Warehouse *w, Waitlist *wl) {
  if (w == nullptr || wl == nullptr)
    throw invalid_parameter_error("Paramters are Null.");
  from = w;
  in = wl;
  status = new InCartState();
  shipType = nullptr;
}

Order::~Order() {
  if (status) delete status;
  if (shipType) delete shipType;
}

bool Order::editContents(Product *item, int quantity) {
  if (item == nullptr || quantity == 0)
    throw invalid_parameter_error("Paramters are Null.");

    if (contents.find(item) != contents.end()) {
      contents[item] += quantity;
      return true;
    } else if (quantity > 0) {
      contents[item] += quantity;
      return true;
    } else {
      return false;
    }
}

bool Order::submit() {
  bool test = status->submit(this);
  delete status;
    if (!test) {
      status = new PendingState();
      return false;
    }
        double o_weight = 0.0;
        for (auto it : getContents()) {
          o_weight += it.first->getWeight() * it.second;
        }

        if (shipType) {
          delete shipType;
        }
        setShipping(o_weight);
        status = new CompleteState();
        return true;
    }

bool Order::isEmpty() {
  return contents.empty();
}

map<Product *, int> &Order::getContents() {
  return contents;
}

Warehouse *Order::getWarehouse() {
  return from;
}

void Order::cancel() {
  status->cancel(this);
}

void Order::view() {
  status->view(this);
}

void Order::displayContent() {
  for (auto it : contents) {
    std:: cout << it.first->getName() << " " << it.second << '\n';
  }
}

Waitlist *Order::getWaitlist() {
  return in;
}

OrderState *Order::getStatus() {
  return status;
}

void Order::setShipping(double weight) {
  ShippingMethodFactory* f = new ShippingMethodFactory();
  shipType = f->getShippingMethod(weight);
  delete f;
}

ShippingMethod *Order::getShipping() {
  return shipType;
}
