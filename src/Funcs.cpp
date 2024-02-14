#include "Funcs.h"


Apartment* get_Apartment(string apartment_name, int max_bandwith) {
    struct Apartment* new_apartment = new Apartment();
    new_apartment->apartment_name = apartment_name;
    new_apartment->max_bandwidth = max_bandwith;
    new_apartment->head_flat = NULL;
    new_apartment->initial_flat_count = 0;
    return new_apartment;
}

Apartment* search_apartment(struct Apartment* head_apartment, char apartment_name) {
    struct Apartment* traverser = head_apartment;
    while (traverser->apartment_name.at(0) != apartment_name && traverser->apartment_name.at(0) != '\0')
    {
        traverser = traverser->next;
    }
    return traverser;
}

Apartment* search_prev_apartment(struct Apartment* head_apartment, char apartment_name) {
    struct Apartment* traverser = head_apartment;
    while (traverser->next->apartment_name.at(0) != apartment_name && traverser->apartment_name.at(0) != '\0')
    {
        traverser = traverser->next;
    }
    return traverser;
}

Apartment* search_apartment_by_flat_id(struct Apartment* head_apartment, int flat_id) {
    struct Apartment* apartmen_traverser = NULL;
    if (head_apartment != NULL)
    {
        apartmen_traverser = head_apartment;
        do
        {
            struct Flat* flat_traverser = apartmen_traverser->head_flat;
            int position = apartmen_traverser->initial_flat_count;
            while (position != 0)
            {
                if (flat_traverser->flat_id == flat_id)
                {
                    return apartmen_traverser;
                }
                else
                {
                    flat_traverser = flat_traverser->next;
                    position--;
                }
            }
            apartmen_traverser = apartmen_traverser->next;
        } while (apartmen_traverser != head_apartment);
    }
    else
    {
        cout << "There is no apartment." << endl;
    }
}

void list_apartments(struct Apartment* head_apartment, ofstream &output) {
    if (head_apartment != NULL)
    {
        struct Apartment* apartmen_traverser = head_apartment;
        do
        {
            output << apartmen_traverser->apartment_name << "(" << apartmen_traverser->max_bandwidth << ")" << "\t";
            struct Flat* flat_traverser = apartmen_traverser->head_flat;
            int position = apartmen_traverser->initial_flat_count;
            while (position != 0)
            {
                output << "Flat " << flat_traverser->flat_id << "(" << flat_traverser->initial_bandwidth << ")" << "\t";
                flat_traverser = flat_traverser->next;
                position--;
            }
            output << endl;
            apartmen_traverser = apartmen_traverser->next;
        } while (apartmen_traverser != head_apartment);
    }
    else
    {
        output << "There is no apartment.";
    }
    output << endl;
}

void free_Apartment(struct Apartment* node) {
    delete node;
}

Flat* get_Flat(int initial_bandwith, int flat_id) {
    struct Flat* new_flat = new Flat();
    new_flat->flat_id = flat_id;
    new_flat->initial_bandwidth = initial_bandwith;
    new_flat->is_empty_flag = false;
    return new_flat;
}

Flat* search_flat(struct Flat* head_flat, int position) {
    struct Flat* traverser = head_flat;
    while (position != 1)
    {
        traverser = traverser->next;
        position--;
    }
    return traverser;
}

Flat* search_flat_by_id(struct Flat* head_flat, int searched_flat_id) {
    struct Flat* traverser = head_flat;
    while (traverser->flat_id != searched_flat_id && traverser->flat_id != '\0')
    {
        traverser = traverser->next;
    }
    return traverser;
}

Flat* search_flat_without_apartment(struct Apartment* head_apartment, int flat_id) {
    struct Apartment* apartmen_traverser = NULL;
    if (head_apartment != NULL)
    {
        apartmen_traverser = head_apartment;
        do
        {
            struct Flat* flat_traverser = apartmen_traverser->head_flat;
            int position = apartmen_traverser->initial_flat_count;
            while (position != 0)
            {
                if (flat_traverser->flat_id == flat_id)
                {
                    return flat_traverser;
                }
                else
                {
                    flat_traverser = flat_traverser->next;
                    position--;
                }
            }
            apartmen_traverser = apartmen_traverser->next;
        } while (apartmen_traverser != head_apartment);
    }
    else
    {
        cout << "There is no apartment." << endl;
    }
}

void free_Flat(struct Flat* node) {
    delete node;
}

void add_apartment(string apartment_name, string position, int max_bandwith, struct Apartment *&head_apartment, struct Apartment *&tail_apartment) {
    struct Apartment* new_apartment = new Apartment();
    new_apartment->apartment_name = apartment_name;
    new_apartment->max_bandwidth = max_bandwith;
    new_apartment->head_flat = NULL;
    new_apartment->initial_bandwidth_sum = 0;
    new_apartment->head_flat = NULL;
    new_apartment->initial_flat_count = 0;
    char first_letter_of_pos = position.at(0); // after or before
    char last_letter_of_pos = position[position.length() - 1]; // hangi apartmana göre

    if (first_letter_of_pos == 'a')
    {
        if (last_letter_of_pos == tail_apartment->apartment_name.at(0))
        {
            new_apartment->next = tail_apartment->next;
            tail_apartment->next = new_apartment;
            tail_apartment = new_apartment;
        }
        else
        {
            Apartment* after_which = search_apartment(head_apartment, last_letter_of_pos);
            if (after_which != NULL)
            {
                new_apartment->next = after_which->next;
                after_which->next = new_apartment;
            }
        }
    }
    else if (first_letter_of_pos == 'b')
    {
        if (last_letter_of_pos == head_apartment->apartment_name.at(0))
        {
            new_apartment->next = head_apartment;
            tail_apartment->next = new_apartment;
            head_apartment = new_apartment;
        }
        else
        {
            Apartment* after_which = search_prev_apartment(head_apartment, last_letter_of_pos);
            if (after_which != NULL)
            {
                new_apartment->next = after_which->next;
                after_which->next = new_apartment;
            }
        }
    }
    else
    {
        head_apartment = new_apartment;
        tail_apartment = new_apartment;
        head_apartment->next = tail_apartment;
        tail_apartment->next = head_apartment;
    }
}

void add_flat(string apartment_name, int index, int initial_bandwith, int flat_id, struct Apartment* head_apartment) {
    Apartment* apartment_of_flat = search_apartment(head_apartment, apartment_name.at(0));
    int avalaible_bandwith = apartment_of_flat->max_bandwidth - apartment_of_flat->initial_bandwidth_sum;
    int calculated_bandwith;
    struct Flat* new_flat = new Flat();
    if (avalaible_bandwith >= initial_bandwith)
    {
        calculated_bandwith = initial_bandwith;
        new_flat->flat_id = flat_id;
        new_flat->initial_bandwidth = calculated_bandwith;
        new_flat->is_empty_flag = false; 
        new_flat->next = NULL;
        new_flat->prev = NULL;
    }
    else if (avalaible_bandwith == 0)
    {
        calculated_bandwith = 0;
        new_flat->flat_id = flat_id;
        new_flat->initial_bandwidth = calculated_bandwith;
        new_flat->is_empty_flag = true;
        new_flat->next = NULL;
        new_flat->prev = NULL;
    }
    else
    {
        calculated_bandwith = avalaible_bandwith;
        new_flat->flat_id = flat_id;
        new_flat->initial_bandwidth = calculated_bandwith;
        new_flat->is_empty_flag = false;
        new_flat->next = NULL;
        new_flat->prev = NULL;
    }

    if (index == 0)
    {
        if (apartment_of_flat->head_flat == NULL)
        {
            apartment_of_flat->head_flat = new_flat;
            new_flat->next = NULL;
            new_flat->prev = NULL;
        }
        else
        {
            new_flat->next = apartment_of_flat->head_flat;
            apartment_of_flat->head_flat->prev = new_flat;
            apartment_of_flat->head_flat = new_flat;
        }

    }
    else
    {
        struct Flat* after_which = search_flat(apartment_of_flat->head_flat, index);

        if (after_which->next == NULL)
        {
            after_which->next = new_flat;
            new_flat->prev = after_which;
        }
        else
        {
            struct Flat* before_which = after_which->next;
            after_which->next = new_flat;
            before_which->prev = new_flat;
            new_flat->next = before_which;
            new_flat->prev = after_which;
        }
    }

    apartment_of_flat->initial_flat_count += 1;
    apartment_of_flat->initial_bandwidth_sum += new_flat->initial_bandwidth;
   
}

void delete_flat_list(struct Apartment *&apartment_of_flats) {
    struct Flat* traverser = apartment_of_flats->head_flat;
    if (traverser == NULL)
    {
        ;
    }
    else
    {
        apartment_of_flats->head_flat = traverser->next;
        free_Flat(traverser);
        delete_flat_list(apartment_of_flats);
    }
}

void remove_apartment(string apartment_name, struct Apartment *&head_apartment, struct Apartment *&tail_apartment) {
    struct Apartment* removed_apartment = search_apartment(head_apartment, apartment_name.at(0));
    struct Apartment* removed_apartment_prev = search_prev_apartment(head_apartment, apartment_name.at(0));;
    if (removed_apartment->apartment_name == head_apartment->apartment_name && removed_apartment->apartment_name == tail_apartment->apartment_name)
    {
        delete_flat_list(removed_apartment);
        free_Apartment(head_apartment);
        head_apartment = NULL;
        tail_apartment = NULL;
    }
    else if (removed_apartment->apartment_name == head_apartment->apartment_name)
    {
        delete_flat_list(removed_apartment);
        tail_apartment->next = removed_apartment->next;
        head_apartment = removed_apartment->next;
        free_Apartment(removed_apartment);
    }
    else if (removed_apartment->apartment_name == tail_apartment->apartment_name)
    {
        delete_flat_list(removed_apartment);
        removed_apartment_prev->next = tail_apartment->next;
        free_Apartment(tail_apartment);
        tail_apartment = removed_apartment_prev;
    }
    else
    {
        delete_flat_list(removed_apartment);
        removed_apartment_prev->next = removed_apartment->next;
        free_Apartment(removed_apartment);
    }
}

void make_flat_empty(string apartment_name, int flat_id, struct Apartment* head_apartment) {
    struct Apartment* apartment_of_flat = search_apartment(head_apartment, apartment_name.at(0));
    struct Flat* emptied_flat = search_flat_by_id(apartment_of_flat->head_flat, flat_id);
    apartment_of_flat->initial_bandwidth_sum -= emptied_flat->initial_bandwidth;
    emptied_flat->initial_bandwidth = 0;
    emptied_flat->is_empty_flag = true;
}

void find_sum_of_max_bandwidth(struct Apartment* head_apartment, ofstream &output) {
    int sum_of_max_bandwidth = 0;
    struct Apartment* traverser = head_apartment;
    do
    {
        if (traverser != NULL)
        {
            sum_of_max_bandwidth += traverser->max_bandwidth;
            traverser = traverser->next;
        }
    } while (traverser != head_apartment);
    output << "sum of bandwidth: " << sum_of_max_bandwidth << endl;
    output << endl;
}

void del_everything(struct Apartment*& head_apartment, struct Apartment*& tail_apartment) {
    struct Apartment* traverser = head_apartment;
    if (traverser == tail_apartment)
    {
        remove_apartment(tail_apartment->apartment_name, head_apartment, tail_apartment);
    }
    else
    {
        head_apartment = traverser->next;
        remove_apartment(traverser->apartment_name,traverser,tail_apartment);
        del_everything(head_apartment,tail_apartment);
    }
    
}

void merge_two_apartments(string apartment_name_1, string apartment_name_2, struct Apartment *&head_apartment, struct Apartment *&tail_apartment) {
    struct Apartment* added_apartment = search_apartment(head_apartment, apartment_name_1.at(0));
    struct Apartment* deleted_apartment = search_apartment(head_apartment, apartment_name_2.at(0));
    added_apartment->max_bandwidth += deleted_apartment->max_bandwidth;
    if (deleted_apartment->head_flat == NULL || (deleted_apartment->head_flat == NULL && added_apartment->head_flat == NULL))
    {
        remove_apartment(deleted_apartment->apartment_name, head_apartment, tail_apartment);
    }
    else if (added_apartment->head_flat == NULL)
    {
        added_apartment->head_flat = deleted_apartment->head_flat;
        added_apartment->initial_flat_count += deleted_apartment->initial_flat_count;
        added_apartment->initial_bandwidth_sum += deleted_apartment->initial_bandwidth_sum;
        deleted_apartment->head_flat = NULL;
        remove_apartment(deleted_apartment->apartment_name, head_apartment, tail_apartment);
    }
    else
    {
        search_flat(added_apartment->head_flat, added_apartment->initial_flat_count)->next = deleted_apartment->head_flat;
        deleted_apartment->head_flat->prev = search_flat(added_apartment->head_flat, added_apartment->initial_flat_count);
        added_apartment->initial_flat_count += deleted_apartment->initial_flat_count;
        added_apartment->initial_bandwidth_sum += deleted_apartment->initial_bandwidth_sum;
        deleted_apartment->head_flat = NULL;
        remove_apartment(deleted_apartment->apartment_name, head_apartment, tail_apartment);
    }
}

void relocate_flats_to_same_apartments(string new_apartment_name, int flat_id_to_shift, vector<int> flat_id_list, struct Apartment* head_apartment) {
    struct Apartment* new_apartment = search_apartment(head_apartment, new_apartment_name.at(0));
    struct Flat* flat_to_shift = search_flat_by_id(new_apartment->head_flat, flat_id_to_shift);
    struct Flat* flat_to_relocate = NULL;
    struct Apartment* apartment_of_flat_to_relocate = NULL;

    for (int i = 0; i < flat_id_list.size(); i++)
    {
        flat_to_relocate = search_flat_without_apartment(head_apartment, flat_id_list[i]);
        apartment_of_flat_to_relocate = search_apartment_by_flat_id(head_apartment, flat_to_relocate->flat_id);
        if (flat_to_relocate == apartment_of_flat_to_relocate->head_flat)
        {
            apartment_of_flat_to_relocate->head_flat = flat_to_relocate->next;
            apartment_of_flat_to_relocate->head_flat->prev = NULL;
        }
        else if (flat_to_relocate == search_flat(apartment_of_flat_to_relocate->head_flat, apartment_of_flat_to_relocate->initial_flat_count))
        {
            flat_to_relocate->prev->next = NULL;
            flat_to_relocate->prev = NULL;
        }
        else
        {
            flat_to_relocate->prev->next = flat_to_relocate->next;
            flat_to_relocate->next->prev = flat_to_relocate->prev;
        }

        if (flat_to_shift == new_apartment->head_flat)
        {
            flat_to_relocate->next = new_apartment->head_flat;
            new_apartment->head_flat->prev = flat_to_relocate;
            new_apartment->head_flat = flat_to_relocate;
        }
        else
        {
            flat_to_relocate->next = flat_to_shift;
            flat_to_relocate->prev = flat_to_shift->prev;
            flat_to_relocate->prev->next = flat_to_relocate;
            flat_to_relocate->next->prev = flat_to_relocate;
        }
        new_apartment->initial_bandwidth_sum += flat_to_relocate->initial_bandwidth;
        new_apartment->initial_flat_count += 1;
        new_apartment->max_bandwidth += flat_to_relocate->initial_bandwidth;
        apartment_of_flat_to_relocate->initial_flat_count -= 1;
        apartment_of_flat_to_relocate->initial_bandwidth_sum -= flat_to_relocate->initial_bandwidth;
        apartment_of_flat_to_relocate->max_bandwidth -= flat_to_relocate->initial_bandwidth;
    }
}