// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

Train::~Train() {
  if (!first) return;

  Car* cur = first->next;
  while (cur != first) {
    Car* next = cur->next;
    delete cur;
    cur = next;
  }
  delete first;
}

void Train::addCar(bool light) {
  Car* new_car = new Car{light, nullptr, nullptr};
  if (!first) {
    new_car->next = new_car;
    new_car->prev = new_car;
    first = new_car;
  } else {
    Car* tail = first->prev;
    tail->next = new_car;
    new_car->prev = tail;
    new_car->next = first;
    first->prev = new_car;
  }
}

int Train::getLength() {
  if (!first) return 0;

  countOp = 0;
  Car* cur = first;

  cur->light = true;

  for (int k = 1;; ++k) {
    Car* probe = cur;
    for (int i = 0; i < k; ++i) {
      probe = probe->next;
      ++countOp;
    }

    if (probe->light) {
      return k;
    } else {
      probe->light = true;
      for (int i = 0; i < k; ++i) {
        probe = probe->prev;
        ++countOp;
      }
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
