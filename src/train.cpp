// Copyright 2021 NNTU-CS
#include "train.h"

#include <stdexcept>

Train::Train() : entry_(nullptr), count_op_(0) {}

Train::~Train() {
  if (!entry_) return;

  Car* cur = entry_->next;
  while (cur != entry_) {
    Car* next = cur->next;
    delete cur;
    cur = next;
  }
  delete entry_;
}

void Train::AddCar(bool light) {
  Car* node = new Car(light);
  if (!entry_) {
    entry_ = node;
  } else {
    Car* tail = entry_->prev;
    tail->next = node;
    node->prev = tail;
    node->next = entry_;
    entry_->prev = node;
  }
}

int Train::GetLength() {
  if (!entry_) throw std::runtime_error("Train is empty");

  Car* cur = entry_;
  int len = 1;
  cur = cur->next;
  count_op_ = 0;
  while (cur != entry_) {
    cur = cur->next;
    ++len;
    ++count_op_;
  }
  return len;
}

long long Train::GetOpCount() const {
  return count_op_;
}
