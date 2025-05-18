// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

void Train::addCar(bool light) {
  Car* car = new Car{light, nullptr, nullptr};
  if (!first) {
    car->next = car;
    car->prev = car;
    first = car;
  } else {
    Car* tail = first->prev;
    tail->next = car;
    car->prev = tail;
    car->next = first;
    first->prev = car;
  }
}

int Train::getLength() {
  if (!first) return 0;

  countOp = 0;
  Car* ptr = first;
  int len = 1;
  ptr = ptr->next;
  ++countOp;

  while (ptr != first) {
    ++len;
    ptr = ptr->next;
    ++countOp;
  }

  return len;
}

int Train::getOpCount() {
  return countOp;
}
