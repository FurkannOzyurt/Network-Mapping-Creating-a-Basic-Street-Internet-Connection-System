#include "Funcs.h"
#include <sstream>

int main(int argc, char* argv[])
{
    ifstream input_reader(argv[1]);
    ofstream output(argv[2]);
    struct Apartment* head_apartment = NULL;
    struct Apartment* tail_apartment = NULL;
    string line;
    while (getline(input_reader,line))
    {
        if (line[line.length()-1] == '\r')
        {
            line.erase(line.length() - 1);
        }
        vector<string> command_elements;
        stringstream ss(line);
        string element;
        int i = 0;
        while (!ss.eof()) {
            getline(ss, element, '\t');
            command_elements.push_back(element);
            i++;
        }
        if (command_elements[0] == "add_apartment")
        {
            add_apartment(command_elements[1], command_elements[2], atoi(command_elements[3].c_str()) , head_apartment, tail_apartment);
        }
        else if (command_elements[0] == "add_flat")
        {
            add_flat(command_elements[1], atoi(command_elements[2].c_str()), atoi(command_elements[3].c_str()), atoi(command_elements[4].c_str()), head_apartment);
        }
        else if (command_elements[0] == "remove_apartment")
        {
            remove_apartment(command_elements[1],head_apartment,tail_apartment);
            
        }
        else if (command_elements[0] == "make_flat_empty")
        {
            make_flat_empty(command_elements[1], atoi(command_elements[2].c_str()), head_apartment);
        }
        else if (command_elements[0] == "find_sum_of_max_bandwidths")
        {
            
            find_sum_of_max_bandwidth(head_apartment,output);
            
        }
        else if (command_elements[0] == "merge_two_apartments")
        {
            merge_two_apartments(command_elements[1], command_elements[2], head_apartment, tail_apartment);
            
        }
        else if (command_elements[0] == "list_apartments")
        {
            
            list_apartments(head_apartment, output);
        }
        else
        {
            vector<int> relocate_elements;
            stringstream ss2(command_elements[3].substr(1, command_elements[3].length() - 2));
            string element;
            int i = 0;
            while (!ss2.eof()) {
                getline(ss2, element, ',');
                relocate_elements.push_back(atoi(element.c_str()));
                i++;
            }
            relocate_flats_to_same_apartments(command_elements[1], atoi(command_elements[2].c_str()), relocate_elements, head_apartment);
            
        }

    }

    input_reader.close();
    output.close();
    del_everything(head_apartment, tail_apartment);

    return 0;
}
