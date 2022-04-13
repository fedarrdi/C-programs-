#include <iostream>
#include <vector>
using namespace std;

class Product
{

private:
    string name;
    int count;
    double price;

public:

    Product() { }

    Product(string name, int count, double price)
    {
        this->name = name;
        this->count = count;
        this->price = price;
        if(count < 0 || name.size() == 0 || price <= 0)
            this->price = -1;
    }

    Product(Product &other)
    {
        this->name = other.name;
        this->count = other.count;
        this->price = other.price;
    }

    Product& operator=(const Product &other)
    {
        if(this != &other)
        {
            this->name = other.name;
            this->count = other.count;
            this->price = other.price;
        }
        return *this;
    }

    void set_name(string name) { this->name = name; }

    void set_count(int count) { this->count = count; }

    void set_price(double prise) { this->price = prise; }

    string get_name() { return name; }

    int get_count() const { return count; }

    double get_price() const { return  price; }

};



class Property
{

private:
    string address, type;
    double rent;

public:

    Property() { }

    Property(string address, string type, double rent)
    {
        this->address = address;
        this->type = type;
        this->rent = rent;

        if((type.compare("supermarket") && type.compare("pharmacy") && type.compare("non-stop")  && type.compare("other")) || rent <= 0 || !address.size())
            this->rent = -1;
    }

    Property(Property &other)
    {
        this->address = other.address;
        this->type = other.type;
        this->rent = other.rent;
    }

    Property& operator=(const Property& other)
    {
        if(this != &other)
        {
            this->address = other.address;
            this->type = other.type;
            this->rent = other.rent;
        }
        return *this;
    }

    string get_address() { return address; }
    string get_type() { return type; }

    double calc_rent()
    {
        if(!type.compare("supermarket")) return rent * 1.4;

        if(!type.compare("pharmacy")) return  rent * 1.3;

        if(!type.compare("non-stop")) return rent * 1.2;

        if(!type.compare("other")) return rent;
    }

};

class Store : Property
{

private:
    string name;
    vector<Product> products;

public:

    Store(string name, string address, string type, double rent) : Property(address, type, rent),  name(name){ } ///TODO check if valid

    Store (Store &other) : Property(other)
    {
        this->name = other.name;

        this->products.clear();
        for(auto curr : other.products)
            this->products.push_back(curr);
    }

    Store& operator=(const Store &other)
    {
        if(this != &other)
        {
            this->name = other.name;

            this->products.clear();
            for(int i = 0;i < other.products.size();i++)
                this->products.push_back(other.products[i]);

            ((Property *) this)->operator=(other);

        }
        return *this;
    }

    string get_name() { return name; }

    vector<string> revision()
    {
        vector<string> out;
        for(auto curr : products)
            if(curr.get_count() < 5)
                out.push_back(curr.get_name());
        return out;
    }

    int add_product(Product new_product)
    {
        for(auto curr : products)
            if(!curr.get_name().compare(new_product.get_name()))
                return 0;

        this->products.push_back(new_product);
        return 1;
    }

    int reload_product(string name, int count)
    {
        for(auto curr : products)
            if(!curr.get_name().compare(name))
            {
                curr.set_count(curr.get_count() + count);
                return 1;
            }

        return 0;
    }

    int buy_product(string name, int count)
    {
        for(auto curr : this->products)
            if(!curr.get_name().compare(name))
            {
                int in_stock_count = curr.get_count();
                if(in_stock_count - count < 0)
                {
                    curr.set_count(0);
                    return in_stock_count;
                }
                else
                {
                    curr.set_count(in_stock_count - count);
                    return count;
                }
            }

        return 0;
    }

    int check_stock_count(string name)
    {
        for(auto curr : products)
            if(!curr.get_name().compare(name))
            {
                return curr.get_count();
            }
        return -1;
    }

    double check_product_price(string name)
    {
        for(auto curr : products)
            if(!curr.get_name().compare(name))
            {
                return curr.get_price();
            }
        return -1;
    }

    void change_price(string name, double new_price)
    {
        for(auto curr : this->products)
            if(!curr.get_name().compare(name))
            {
                curr.set_price(new_price);
                return;
            }
    }

    void print_information()
    {
        cout << name << " "  << get_address() << " " << get_type() << endl;
        for(auto curr : products)
            cout << curr.get_name() << " " << curr.get_count() << " " << curr.get_price() << endl;
    }

};


class Interface
{
    
};



int main()
{

    return 0;
}
