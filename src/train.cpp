// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

void Train::addCar(bool light) {
  Car* node = new Car;
  node->light = light;
  if (!first) {
    node->next = node;
    node->prev = node;
    first = node;
  } else {
    Car* last = first->prev;
    last->next = node;
    node->prev = last;
    node->next = first;
    first->prev = node;
  }
}

int Train::getLength() {
  if (!first) return 0;
  int length = 1;
  countOp = 0;

  Car* cur = first;
  while ((cur = cur->next) != first) {
    ++length;
    ++countOp;
  }
  return length;
}

int Train::getOpCount() {
  return countOp;
}
