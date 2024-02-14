#pragma once
#include <iostream>
using namespace std;

struct Apartment {
    int max_bandwidth;
    int initial_bandwidth_sum;
    int initial_flat_count;
    string apartment_name;
    struct Apartment* next;
    struct Flat* head_flat;
};
