#include <iostream>
#include <string>
#include <algorithm>
#include<fcntl.h>
#include <fstream>

using namespace std;

struct Phone /// струткура за телефон
{
    string brand, model, color;
    float price, memory, display_diagonal;
    bool is_working_with_2_sim_cards;
    unsigned same_phone_count;
};

struct Phone_System /// структура за система от телфени
{
    int n;
    struct Phone phones[100];
};

struct Phone init_phone(Phone_System *system)  /// функцията създава телефон и връща променлива от тип телефон
{
    string brand, model, color;
    float price, memory, display_diagonal;
    bool is_working_with_2_sim_cards;
    cout << "Enter: brand, model, color, price, memory, screen size, is working with 2 sim cards(0 or 1)" << endl;
    cin >> brand >> model >> color >> price >> memory >> display_diagonal >> is_working_with_2_sim_cards;


    unsigned same_phone_count = 1;
    for(int i = 0;i < system->n;i++)
    {
        if(system->phones[i].model == model)
        {
            system->phones[i].same_phone_count ++;
            same_phone_count ++;
        }
    }

    return (Phone) {brand, model, color, price, memory, display_diagonal, is_working_with_2_sim_cards, same_phone_count};
}

void add_phone(Phone_System *system) /// функцията
{
    Phone phone = init_phone(system);

    if(system->n == 100)
    {
        cout << "Phone system limit had been reached no more space!!!" << endl;
        return;
    }

    system->phones[system->n++] = phone;
}

void add_phones(Phone_System *system, int n)
{
    for (int i = 0; i < n; i++)
        add_phone(system);
}

void print_phone(Phone phone)
{
    cout << "brand: " << phone.brand << endl;
    cout << "model: " << phone.model << endl;
    cout << "color: " << phone.color << endl;
    cout << "price: " << phone.price << endl;
    cout << "memory: " << phone.memory << endl;
    cout << "display_diagonal: " << phone.display_diagonal << endl;
    cout << "is_working_with_2_sim_cards: " << phone.is_working_with_2_sim_cards << endl;
    cout << "same_phone_count: " << phone.same_phone_count << endl;
}

void print_phones(Phone_System *system)
{
    for(int i = 0;i < system->n;i++)
        print_phone(system->phones[i]);
}

void print_phones_less_memory(Phone_System *system)
{
    float least_memory = system->phones[0].memory;
    for(int i = 1;i < system->n;i++)
        if(least_memory > system->phones[i].memory)
            least_memory = system->phones[i].memory;

    for(int i = 0;i < system->n;i++)
        if(least_memory == system->phones[i].memory)
            print_phone(system->phones[i]);
}

void print_phones_2_sim(Phone_System *system)
{
    for(int i = 0;i < system->n;i++)
        if(system->phones[i].is_working_with_2_sim_cards)
            print_phone(system->phones[i]);
}

bool cmp(Phone p, Phone q)
{
    return p.price < q.price;
}

void sort_phones_least_expensive(Phone_System *system)
{
    sort(system->phones, system->phones + system->n, cmp);
}


void write_to_file_save(Phone_System *system, const char *file_path)
{
   int fd = open(file_path, O_WRONLY | O_TRUNC);

   if(fd == -1)
   {
       cout << "File can't be open!!!\n" << endl;
       return;
   }

   for(int i = 0;i < system->n;i++)
   {
       if(write(fd, system->phones + i, sizeof (Phone)) == -1)
       {
           cout << "Error while writing!!!" << endl;
           return;
       }
   }
}

void read_from_file_save(Phone_System *system, const char *file_path)
{
    int fd = open(file_path, O_RDONLY);

    if(fd == -1)
    {
        cout << "File can't be open!!!\n" << endl;
        return;
    }

    Phone p;
    while(1)
    {
        int read_status = read(fd, &p, sizeof(Phone));

        if(read_status == -1)
        {
            cout << "Error while reading!!!" << endl;
            return;
        }

        if(!read_status)
            return;

        if(system->n == 100)
        {
            cout << "Phone system limit had been reached no more space!!!" << endl;
            return;
        }

        system->phones[system->n++] = p;
    }
}

void phones_least_expensive(Phone_System *system, string model)
{
    Phone arr[100];
    int index = 0;
    for (int i = 0; i < system->n; i++)
    {
        if (system->phones[i].model == model)
            arr[index++] = system->phones[i];
    }

    sort(arr, arr + index, cmp);
}

void phones_least_expensive(Phone_System *system, float screen_size)
{
    Phone arr[100];
    int index = 0;
    for (int i = 0; i < system->n; i++)
    {
        if (system->phones[i].display_diagonal == screen_size)
            arr[index++] = system->phones[i];
    }

    sort(arr, arr + index, cmp);
}

void correct(Phone_System *system, string brand, string model)
{
    for(int i = 0;i < system->n;i++)
    {
        if(system->phones[i].brand == brand && system->phones[i].model == model)
        {
            string brand, model, color;
            float price, memory, display_diagonal;
            bool is_working_with_2_sim_cards;
            unsigned t = system->phones[i].same_phone_count;
            cin >> brand >> model >> color >> price >> memory >> display_diagonal >> is_working_with_2_sim_cards;
            system->phones[i] = (Phone) {brand, model, color, price, memory, display_diagonal, is_working_with_2_sim_cards, t};
        }
    }
}

void sell(Phone_System *system, string model, string brand)
{
    for(int i = 0;i < system->n;i++)
    {
        if(system->phones[i].brand == brand && system->phones[i].model == model)
        {
            if(system->phones[i].same_phone_count == 0)
            {
                cout << "All units of this phone had been sold!" << endl;
            }

            system->phones[i].same_phone_count--;
        }
    }
}

void write_in_txt_file(Phone_System *system, string path)
{
    ofstream file;
    file.open(path);

    for(int i = 0;i < system->n;i++)
    {
        file << system->phones[i].brand << endl;
        file << system->phones[i].model << endl;
        file << system->phones[i].color << endl;
        file << system->phones[i].price << endl;
        file << system->phones[i].memory << endl;
        file << system->phones[i].display_diagonal << endl;
        file <<  system->phones[i].is_working_with_2_sim_cards << endl;
        file << system->phones[i].same_phone_count << endl;
    }

    file.close();
}

int main()
{
    Phone_System system;
    while(1)
    {
        cout << "Commands" << endl;
        cout << "a ----> add one phone" << endl;
        cout << "b ----> add multiple phones" << endl;
        cout << "c ----> print all phones" << endl;
        cout << "d ----> print phones sorted by memory" << endl;
        cout << "e ----> print phones can work with 2 sim cards" << endl;
        cout << "f ----> sort phones by price" << endl;
        cout << "g ----> correct phone" << endl;
        cout << "h ----> sell phone" << endl;
        cout << "i ----> save in binary file" << endl;
        cout << "j ----> load from binary file" << endl;
        cout << "k ----> sort phones by price and model" << endl;
        cout << "l ----> sort phones by price and screen size" << endl;
        cout << "m ----> write to txt file" << endl;
        cout << "q ----> for quiting" << endl;

        char command;
        cin >> command;

        if(command == 'q')
            break;

        if(command == 'a')
            add_phone(&system);

        if(command == 'b')
        {
            cout << "Enter number of phones" << endl;
            int n;
            cin >> n;
            add_phones(&system, n);
        }

        if(command == 'c')
            print_phones(&system);

        if(command == 'd')
            print_phones_less_memory(&system);

        if(command == 'e')
            print_phones_2_sim(&system);

        if(command == 'f')
            sort_phones_least_expensive(&system);


        if(command == 'g')
        {
            string brand, model;
            cout << "Enter brand and model" << endl;
            cin >> brand >> model;
            correct(&system, brand, model);
        }

        if(command == 'h')
        {
            string brand, model;
            cout << "Enter brand and model" << endl;
            cin >> brand >> model;
            sell(&system, brand, model);
        }

        if(command == 'i')
        {
            cout << "Enter path: ";
            string path;
            cin >> path;

            char *path_ = (char *) malloc(path.size() + 1);
            if(!path_)
            {
                cout << "Can' t allocate memory!!!" << endl;
                continue;
            }

            int i = 0;
            for(;i < path.size();i++)
                path_[i] = path[i];
            path_[i] = 0;

            write_to_file_save(&system, path_);

            free(path_);
        }

        if(command == 'j')
        {
            cout << "Enter path: ";
            string path;
            cin >> path;

            char *path_ = (char *) malloc(path.size() + 1);
            if(!path_)
            {
                cout << "Can' t allocate memory!!!" << endl;
                continue;
            }

            int i = 0;
            for(;i < path.size();i++)
                path_[i] = path[i];
            path_[i] = 0;

            read_from_file_save(&system, path_);
            free(path_);
        }

        if(command == 'k')
        {
            string brand;
            cout << "Enter brand " << endl;
            cin >> brand;
            phones_least_expensive(&system, brand);
        }

        if(command == 'k')
        {
            float screen_size;
            cout << "Enter screen size" << endl;
            cin >> screen_size;
            phones_least_expensive(&system, screen_size);
        }

        if(command == 'm')
        {
            cout << "Enter path: ";
            string path;
            cin >> path;
            write_in_txt_file(&system, path);
        }

    }

    return 0;
}
