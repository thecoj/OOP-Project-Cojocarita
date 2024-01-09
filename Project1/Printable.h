#pragma once

#include <iostream>

class Printable {
public:
    virtual void print() const = 0;  // Pure virtual function
    virtual ~Printable() {}          // Virtual destructor
};
