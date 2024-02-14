#pragma once

struct Flat {
    int flat_id;
    bool is_empty_flag;
    int initial_bandwidth;
    struct Flat* next;
    struct Flat* prev;
};
