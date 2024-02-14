#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "Apartment.h"
#include "Flat.h"
#include <fstream>
#include <vector>
#include <string.h>

// it creates apartment
Apartment* get_Apartment(string apartment_name, int max_bandwith);
// it searchs apartment by name
Apartment* search_apartment(struct Apartment* head_apartment, char apartment_name);
// it searches before of apartment
Apartment* search_prev_apartment(struct Apartment* head_apartment, char apartment_name);
// it searches apartmen by flat id
Apartment* search_apartment_by_flat_id(struct Apartment* head_apartment, int flat_id);
void list_apartments(struct Apartment* head_apartment, ofstream& output);
// it deletes apartment
void free_Apartment(struct Apartment* node);
// it creates apartment
Flat* get_Flat(int initial_bandwith, int flat_id);
// it searches flat by positon
Flat* search_flat(struct Flat* head_flat, int position);
// it searches flat by id
Flat* search_flat_by_id(struct Flat* head_flat, int searched_flat_id);
Flat* search_flat_without_apartment(struct Apartment* head_apartment, int flat_id);
//it deletes flat
void free_Flat(struct Flat* node);
void add_apartment(string apartment_name, string position, int max_bandwith, struct Apartment*& head_apartment, struct Apartment*& tail_apartment);
void add_flat(string apartment_name, int index, int initial_bandwith, int flat_id, struct Apartment* head_apartment);
void delete_flat_list(struct Apartment*& apartment_of_flats);
void remove_apartment(string apartment_name, struct Apartment*& head_apartment, struct Apartment*& tail_apartment);
void make_flat_empty(string apartment_name, int flat_id, struct Apartment* head_apartment);
void find_sum_of_max_bandwidth(struct Apartment* head_apartment, ofstream& output);
void merge_two_apartments(string apartment_name_1, string apartment_name_2, struct Apartment*& head_apartment, struct Apartment*& tail_apartment);
void relocate_flats_to_same_apartments(string new_apartment_name, int flat_id_to_shift, vector<int> flat_id_list, struct Apartment* head_apartment);
void del_everything(struct Apartment*& head_apartment, struct Apartment*& tail_apartment);