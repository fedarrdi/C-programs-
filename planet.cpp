#include<iostream>
#include <cstdio>

//============================================================================
// Homework on basic class
//============================================================================

class Planet
{
    //TODO add fields
    const char *name;
    double distance_to_sun, diameter, weight;

public:
    Planet(const char *name, double distance_to_sun, double diameter, double weight)
    {
        this->name = name;
        this->distance_to_sun = distance_to_sun;///km
        this->diameter = diameter;
        this->weight = weight;
    }

    //~Planet();

    //TODO add getters and setters

    void print()
    {
        std::cout << "Planet: ";
        printf("%s", name);

        std::cout << "distance_to_sun = " << distance_to_sun << "\n diameter = " << diameter << "\n" << "weight = " << weight << "\n";
    }

    double get_seconds_to_sun() const
    {                               /// light speed in m/sec
        return distance_to_sun*1000/299792;
    }

};

int main()
{

    //Get all the parameters from the console
    //Make sure that the values are valid!
    //Then create an object of type Planet and test all the methods.
    int size;
    std::cin >> size;
    while(size > 50)
        std::cin >> size;

    char *planet_name = new char[size];
    scanf("%s", planet_name);

    int dist_to_sun, diameter, weight;
    std::cin >> dist_to_sun >> diameter >> weight;

    Planet my_planet = Planet(planet_name, dist_to_sun, diameter, weight);

    my_planet.print();

    std::cout << my_planet.get_seconds_to_sun() << std::endl;

    return 0;
}