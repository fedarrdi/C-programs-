#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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
    return 0;
}
