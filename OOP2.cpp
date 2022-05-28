#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

class Character
{

public:

    Character(string name, float health, float defense)
    {
        this->name = (health < 0 || defense < 0) ? "" : name;
        this->health = health;
        this->defense = defense;
    }

    float getHealth() const { return health; }

    float getDefense() const { return defense; }

    const string &getName() const { return name; }

    void setHealth(const float health) { this->health = health;}

    void setDefense(const float defense) { this->defense = defense; }

    void setName(const string& name) { this->name = name; }

protected:
    float health;
    float defense;
    string name;
};

class Enemy : public Character
{

public:
    Enemy(const string& name, float health, float defense, float damage) : Character(name, health, defense), damage(damage) { }

    float getDamage() const { return  damage; }

    void setDamage(const float damage) { this->damage = damage; }

private:
    float damage;

};

class Ability
{

public:
    Ability(const string& name, const float damage) : name(name), damage(damage) { }

    float getDamage() const { return damage; }

    void setDamage(const float damage) { this->damage = damage; }

    const string& getName() const { return name; }

    void setName(const string& name) {this->name = name; }

private:
    string name;
    float damage;

};

class Player : public Character
{

public:
    Player(const string& name, float health, float defense) : Character(name, health, defense) {};

    Player& addAbility(const Ability& ability)
    {
        for(auto curr_ability : abilities)
            if(curr_ability.getName() == ability.getName())
                return *this;

        this->abilities.push_back(ability);
        return *this;
    }

    const vector<Ability>& getAbilities() const { return abilities; }

private:
    vector<Ability> abilities;

};

class PlayerHelper
{

public:
    static float getTotalPlayerDamage(const Player& player)
    {
        const vector<Ability> &player_abilities = player.getAbilities();

        float damage_all = 0;
        for(auto curr_player_ability : player_abilities)
            damage_all += curr_player_ability.getDamage();

        return damage_all;
    }

};

class Arena
{

public:
    static int currentEnemyIndex;

    static bool fight(Player& player, vector<Enemy>& enemies)
    {
        PlayerHelper player_helper;

        float player_damage_on_attack = player_helper.getTotalPlayerDamage(player);

        for(;currentEnemyIndex < enemies.size();currentEnemyIndex++)
        {
            Enemy curr_enemy = enemies[currentEnemyIndex];

            float curr_enemy_defense = curr_enemy.getDefense(), curr_enemy_health = curr_enemy.getHealth();
            float player_defense = player.getDefense(), player_health = player.getHealth();

            for(int move = 0;curr_enemy_health != 0 && player.getHealth() != 0; move = !move)
            {
                if (!move)
                {
                    curr_enemy_defense -= player_damage_on_attack;

                    if (curr_enemy_defense < 0)
                    {
                        curr_enemy_health += curr_enemy_defense;
                        curr_enemy_defense = 0;
                    }

                    if (curr_enemy_health <= 0)
                    {
                        curr_enemy.setHealth(0);
                        curr_enemy.setDefense(0);
                    }

                }

                if(move)
                {
                    player_defense -= curr_enemy.getDamage();

                    if(player_defense < 0)
                    {
                        player_health += player_defense;
                        player_defense = 0;
                    }

                    player.setDefense(player_defense);
                    player.setHealth(player_health);


                    if (player_health <= 0)
                    {
                        player.setDefense(0);
                        player.setHealth(0);

                        return false;
                    }

                }

            }
        }
        return true;
    }
};

int Arena::currentEnemyIndex = 0;

int main()
{

    ifstream input_file;
    input_file.open(R"(C:\Users\fedar\CLionProject\OOP2\input.txt)", ios::in);

    string buffer;
    stringstream ss;

    getline(input_file, buffer);
    ss << buffer;

    string player_name;
    float health, defense;
    ss >> player_name >> health >> defense;
    Player player(player_name, health, defense);

    string ability_name;
    float damage;
    while(ss)
    {
        ss >> ability_name >> damage;
        player.addAbility(Ability(ability_name, damage));
    }


    vector<Enemy> enemies;
    for(float health, defense, damage;getline(input_file, buffer);)
    {
        ss << buffer;
        string enemy_name;
        ss >> enemy_name >> health >> defense >> damage;
        enemies.push_back(Enemy(enemy_name, health, defense, damage));
    }

    input_file.close();

    bool player_win = Arena::fight(player, enemies);
    ofstream output_File("output.txt");

    if(player_win)
    {
        output_File << "Player Won!\n";
        output_File << "Player health: " << player.getHealth() << "\n";
        output_File << "Player defense: " << player.getDefense() << "\n";
    }
    else
    {
        output_File << "Player Lost!\n";
        output_File << "Enemy " << Arena::currentEnemyIndex << "health: " << enemies[Arena::currentEnemyIndex].getHealth() << "\n";
        output_File << "Enemy " << Arena::currentEnemyIndex << "defense: " << enemies[Arena::currentEnemyIndex].getDefense() << "\n";
    }

    output_File.close();

    return 0;
}
