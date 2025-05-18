// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

void Train::addCar(bool light) {
    Car* newCar = new Car;
    newCar->light = light;

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

    int length = 0;
    countOp = 0;
    Car* cur = first;

    do {
        if (cur->light) {
            cur->light = false;
            countOp += 2;
        }
        ++length;
        cur = cur->next;
        countOp++;
    } while (cur != first);

    return length;
}

int Train::getOpCount() {
    return countOp;
}
