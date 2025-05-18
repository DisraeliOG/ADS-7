// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (!first) {
        newCar->next = newCar;
        newCar->prev = newCar;
        first = newCar;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
}

int Train::getLength() {
    if (!first) {
        countOp = 0;
        return 0;
    }

    int length = 1;
    countOp = 0;

    Car* cur = first;
    while (cur->next != first) {
        cur = cur->next;
        ++length;
        ++countOp;
    }

    cur = first;
    while (cur->prev != first) {
        cur = cur->prev;
        ++countOp;
    }

    return length;
}

int Train::getOpCount() {
    return countOp;
}
