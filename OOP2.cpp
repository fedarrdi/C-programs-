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
    Player(const string& name, float health, float defense, const std::vector<Ability>& abilities) : Character(name, health, defense)
    {
        if(!abilities.size())
        {
            this->name = "";
            return;
        }
        
        for(auto curr_ability : abilities)
            this->abilities.push_back(curr_ability);

    }

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

    static bool fight(Player& player, std::vector<Enemy>& enemies)
    {
        PlayerHelper player_helper;

        float player_damage_on_attack = player_helper.getTotalPlayerDamage(player);

        for(;currentEnemyIndex < enemies.size();currentEnemyIndex++)
        {
            Enemy curr_enemy = enemies[currentEnemyIndex];

            float curr_enemy_defense = curr_enemy.getDefense(), curr_enemy_health = curr_enemy.getHealth();
            float player_defense = player.getDefense(), player_health = player.getHealth();

            for(int move = 0;curr_enemy.getHealth() != 0 && player.getHealth() != 0; move = !move)
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
    input_file.open("input.txt", ios::in);

    string buffer;

    getline(input_file, buffer);
    stringstream ss;
    ss << buffer;

    vector<Ability> a;
    string player_name;
    float health = 0, defense = 0;
    ss >> player_name >> health >> defense;

    if(player_name.empty() || health <= 0 || defense <= 0)
    {
        cout <<  "Invalid player stats!" << endl;
        return 0;
    }

    Player player(player_name, health ,defense, a);

    string ability_name;
    float damage_a = 0;

    while(ss)
    {
        ss >> ability_name >> damage_a;

        if(ability_name.empty() || damage_a <= 0)
        {
            cout <<  "Invalid ability stats!" << endl;
            return 0;
        }

        player.addAbility(Ability(ability_name, damage_a));
    }
    vector<Enemy> enemies;
    string enemy_name;

    float damage_e = 0, health_e = 0, defense_e = 0;
    while(getline(input_file, buffer))
    {
        ss.clear();
        ss << buffer;
        ss >> enemy_name >> health_e >> defense_e >> damage_e;

        if(enemy_name.empty() || health_e <= 0 || defense_e <= 0 || damage_e <= 0)
        {
            cout <<  "Invalid enemy stats!" << endl;
            return 0;
        }

        auto *new_enemy = new Enemy(enemy_name, health_e, defense_e, damage_e);
        enemies.push_back(*new_enemy);
    }
    
    if(enemies.empty())
    {
        cout << "Invalid enemy stats!" << endl;
        return 0;
    }

    input_file.close();


    cout << "print_player " << endl;
    cout << "player health " << player.getHealth() << endl;
    cout << "player name " << player.getName() << endl;
    cout << "player defense " << player.getDefense() << endl << endl;
    vector<Ability> abilities = player.getAbilities();

    for(auto curr_ability : abilities)
    {
        cout << "ability print"  << endl;
        cout << "ability damage " << curr_ability.getDamage() << endl;
        cout << "ability name " << curr_ability.getName() << endl << endl;
    }
    for(auto curr_enemy : enemies)
    {
        cout << "enemy print" << endl;
        cout << "enemy name " << curr_enemy.getName() << endl;
        cout << "enemy health " << curr_enemy.getHealth() << endl;
        cout << "enemy defens " << curr_enemy.getDefense() << endl;
        cout << "enemy damage " << curr_enemy.getDamage() << endl << endl;
    }

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
