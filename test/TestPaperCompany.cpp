#include "Order.h"
#include <Exceptions.h>
#include "PaperCompany.h"
#include "gtest/gtest.h"

TEST(TestPaperCompany, defaultConstructorTest) {
  PaperCompany* p1 = new PaperCompany();

  delete p1;
}

TEST(TestPaperCompany, testAddProduct) {
  PaperCompany* p1 = new PaperCompany();

  EXPECT_TRUE(p1->addProduct("Paper", 30));
  EXPECT_TRUE(p1->addProduct("Pens", 30));
  EXPECT_FALSE(p1->addProduct("Paper", 40));

  delete p1;
}
TEST(TestPaperCompany, testFindProduct) {
  PaperCompany* p1 = new PaperCompany();
  Product* p = new Product("Pens", 10);
  p1->addProduct("Paper", 30);
  p1->addProduct("Pens", 50);

  EXPECT_FALSE(p1->findProduct("Paper") == p1->findProduct("Pens"));
  EXPECT_TRUE(p1->findProduct("Paper") == p1->findProduct("Paper"));
  EXPECT_EQ(p1->findProduct("Card Stock"), nullptr);
  EXPECT_EQ(p1->findProduct("Pens")->getName(),
  p->getName());

  delete p1;
  delete p;
}

TEST(TestPaperCompany, testAdjustInventoryAdd) {
  PaperCompany* p1 = new PaperCompany();
  p1->addProduct("Paper", 20);
  PaperCompany* p2 = new PaperCompany();
  p2->addProduct("Card Stock", 50);
  PaperCompany* p3 = new PaperCompany();
  p3->addProduct("Envelopes", 30);

  EXPECT_TRUE(p1->adjustInventory("Paper", 100));
  EXPECT_TRUE(p2->adjustInventory("Card Stock", 50));
  EXPECT_TRUE(p3->adjustInventory("Envelopes", 10000));
  EXPECT_THROW(p3->adjustInventory("IamMichaelScarn", 10),
  invalid_parameter_error);

  delete p1;
  delete p2;
  delete p3;
}
TEST(TestPaperCompany, testAdjustInventoryRemove) {
  PaperCompany* p1 = new PaperCompany();
  p1->addProduct("Paper", 100);
  PaperCompany* p2 = new PaperCompany();
  p2->addProduct("Card Stock", 100);
  PaperCompany* p3 = new PaperCompany();
  p3->addProduct("Black Paper", 50);

  EXPECT_TRUE(p1->adjustInventory("Paper", 15));
  EXPECT_TRUE(p1->adjustInventory("Paper", -10));
  EXPECT_TRUE(p2->adjustInventory("Card Stock", 10));
  EXPECT_TRUE(p2->adjustInventory("Card Stock", -5));
  EXPECT_TRUE(p3->adjustInventory("Black Paper", 20));
  EXPECT_TRUE(p3->adjustInventory("Black Paper", -20));

  delete p1;
  delete p2;
  delete p3;
}


TEST(TestPaperCompany, testAdjustInventoryInvalid) {
  PaperCompany* p1 = new PaperCompany();
  p1->addProduct("Paper", 10);
  PaperCompany* p2 = new PaperCompany();
  p2->addProduct("White Out", 20);

  EXPECT_FALSE(p1->adjustInventory("Paper", -20));
  EXPECT_FALSE(p2->adjustInventory("White Out", -10));
  EXPECT_THROW(p2->adjustInventory("Poster", 10), invalid_parameter_error);

  delete p1;
  delete p2;
}

TEST(TestPaperCompany, testListInvetory) {
  PaperCompany* p1 = new PaperCompany();
  p1->addProduct("Paper", 1);
  p1->addProduct("Pens", 2);

  EXPECT_NO_THROW(p1->listInventory());
  delete p1;
}

TEST(TestPaperCompany, testAddToOrders) {
  PaperCompany* pc = new PaperCompany();
  Order* o = nullptr;

  EXPECT_THROW(pc->addToOrders(o), invalid_parameter_error);

  delete pc;
  delete o;
}
TEST(TestPaperCompany, viewOrderTest) {
  PaperCompany * pc1 = new PaperCompany();
  pc1-> addProduct("Paper", 15);

  Order * o = pc1->createOrder();

  pc1->addToOrders(o);
  EXPECT_NO_THROW(pc1->viewOrders());

  delete pc1;
}
