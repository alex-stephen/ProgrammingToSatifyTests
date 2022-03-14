#include "Order.h"
#include "OrderState.h"
#include "Warehouse.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

InCartState::InCartState() : OrderState("In Cart") {}

void InCartState::view(Order *in) {
  std::cout << "Order is in InCart State" << '\n';
  in->displayContent();
}

bool InCartState::submit(Order *in) {
    for (auto it : in->getContents()) {
        if (it.second > in->getWarehouse()->checkQuantity(it.first)) {
            std::cout << "One or more of the products are not in stock and the "
            << "order was added to the waitlist" << '\n';

            in->getWaitlist()->addOrder(in);
            return false;
        }
    }

    std::cout << "Order from InCart has been completed" << '\n';

    for (auto it : in->getContents()) {
        in->getWarehouse()->changeQuantity(it.first, ((it.second)*-1));
    }

    return true;
}

void InCartState::cancel(Order *in) {
  in->getContents().clear();
}

PendingState::PendingState() : OrderState("Pending") {}

void PendingState::view(Order *in) {
  std::cout << "Order is in Pending State" << '\n';
  in->displayContent();
}

bool PendingState::submit(Order *in) {
    for (auto it : in->getContents()) {
        if (it.second > in->getWarehouse()->checkQuantity(it.first)) {
            std::cout << "One or more of the products are not in stock and the "
            << "order was added to the waitlist" << '\n';

            return false;
        }
    }

    std::cout << "Order from Pending has been completed" << '\n';

    for (auto it : in->getContents()) {
        in->getWarehouse()->changeQuantity(it.first, ((it.second)*-1));
    }

    return true;
}

void PendingState::cancel(Order *in) {
  in->getContents().clear();
  in->getWaitlist()->removeOrder(in);
}

CompleteState::CompleteState() : OrderState("Complete") {}

void CompleteState::view(Order *in) {
  std::cout << "Order has been successfully shipped : "
            << in->getShipping()->name()
            << '\n';
  in->displayContent();
}

bool CompleteState::submit(Order *in) {
  std::cout << "Error, this order has already been submitted" << '\n';
  return true;
}
void CompleteState::cancel(Order *in) {
  std::cout << "Error, this order has already been submitted" << '\n';
}
