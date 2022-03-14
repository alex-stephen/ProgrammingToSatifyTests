#include <Exceptions.h>
#include "PaperCompany.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

PaperCompany::PaperCompany() {
  wl = new Waitlist();
  wh = new Warehouse(wl);
}

PaperCompany::~PaperCompany() {
  for (auto o : orders) delete o;
  for (auto p : products) delete p.second;
  delete wh;
  delete wl;
}

Order* PaperCompany::createOrder() {
  return new Order(wh, wl);
}

void PaperCompany::addToOrders(Order* input) {
  if (input == nullptr) {
    throw invalid_parameter_error("Order is a nullptr.");
  } else {
    orders.push_back(input);
  }
}

bool PaperCompany::addProduct(string name, double weight) {
    if (products.find(name) != products.end())
        return false;

    Product* p1 = new Product(name, weight);
    products[name] = p1;
    return true;
}

Product* PaperCompany::findProduct(string name) {
  return products[name];
}

void PaperCompany::listInventory() {
  for (auto it = products.begin(); it != products.end(); ++it) {
    std::cout << it->first << " " << it->second << '\n';
  }
}

bool PaperCompany::adjustInventory(string name, int quantity) {
  Product* p = products[name];
  if (quantity < 0) {
    if (wh->checkQuantity(p) < abs(quantity)) {
      return false;
      } else {
          wh->changeQuantity(p, quantity);
        }
    } else {
      wh->changeQuantity(p, quantity);
    return true;
  }
}

void PaperCompany::viewOrders() {
  for (auto order : orders) {
    order->view();
  }
}
