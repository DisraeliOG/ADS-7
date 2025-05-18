// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

#include <cstddef>

class Train {
 private:
  struct Car {
    bool light;
    Car* next;
    Car* prev;
    explicit Car(bool l) : light(l), next(this), prev(this) {}
  };

  Car* first;
  std::size_t countOp;

 public:
  Train();
  ~Train();

  void addCar(bool light);

  std::size_t getLength();

  std::size_t getOpCount() const;
};

#endif  // INCLUDE_TRAIN_H_
