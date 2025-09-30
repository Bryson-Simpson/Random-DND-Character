#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <json/json.h>
#include <sys/stat.h>   // for mkdir
#include <sys/types.h>  // for mkdir

using namespace std;

class Character {
public:
    string name;
    string charClass;
    string race;
    string feat;
    string background;
    int level = 1;
    int strength;
    int dexterity;
    int constitution;
    int intelligence;
    int wisdom;
    int charisma;

    int abilityMod(int score) const {
        return (score - 10) / 2;
    }

    int proficiencyBonus() const {
        if (level <= 4) return 2;
        else if (level <= 8) return 3;
        else if (level <= 12) return 4;
        else if (level <= 16) return 5;
        else return 6;
    }

    int armorClass() const { return 10 + abilityMod(dexterity); }
    int initiative() const { return abilityMod(dexterity); }
    int speed() const { return 30; }
    int hitPoints() const { return 8 + abilityMod(constitution); }
};

class RandomNumAbilities {
public:
    int rollAbility() {
        int score = 0;
        do {
            int rolls[4];
            for (int i = 0; i < 4; ++i) {
                rolls[i] = rand() % 6 + 1;  // roll 1d6
            }
            sort(rolls, rolls + 4);
            score = rolls[1] + rolls[2] + rolls[3];  // drop the lowest
        } while (score < 10);  // reroll if below 10
        return score;
    }
};


class RandomClass {
public:
    string getRandomClass() {
        string classes[] = {"Fighter", "Wizard", "Rogue", "Cleric", "Ranger", "Paladin", "Artificer", "Barbarian", "Bard", "Druid", "Monk", "Sorcerer", "Warlock"};
        int index = rand() % 13;
        return classes[index];
    }
};

class RandomRace {
public:
    string getRandomRace() {
        string races[] = {"Human", "Elf", "Dwarf", "Halfling", "Orc", "Gnome", "Tiefling", "Dragonborn", "Half-Elf", "Half-Orc", "Aasimar", "Genasi", "Goliath", "Kenku", "Tabaxi", "Triton", "Yuan-ti", "Firbolg", "Goblin", "Hobgoblin", "Kobold", "Lizardfolk", "Bugbear", "Centaur", "Minotaur", "Satyr", "Warforged", "Changeling", "Shifter", "Kaladesh", "Vedalken", "Simic Hybrid", "Loxodon", "Aetherborn", "Merfolk", "Sphinx", "Naga", "Elemental", "Fey", "Undead", "Drow", "Duergar", "Svirfneblin", "Aarakocra", "Genasi (Air)", "Genasi (Earth)", "Genasi (Fire)", "Genasi (Water)", "Githyanki", "Githzerai", "Locathah", "Grung", "Autognome", "Plasmoid", "Thri-kreen", "Owlfolk", "Rabbitfolk"};
        int index = rand() % 58;
        return races[index];
    }
};

class RandomFeats {
public:
    string getRandomFeat() {
        string feats[] = {"Alert", "Athlete", "Actor", "Charger", "Crossbow Expert", "Defensive Duelist", "Dual Wielder", "Dungeon Delver", "Durable", "Elemental Adept", "Grappler", "Great Weapon Master", "Healer", "Inspiring Leader", "Keen Mind", "Lightly Armored", "Linguist", "Lucky", "Mage Slayer", "Magic Initiate", "Martial Adept", "Medium Armor Master", "Mobile", "Mounted Combatant", "Observant", "Polearm Master", "Resilient", "Ritual Caster", "Savage Attacker", "Sentinel", "Sharpshooter", "Shield Master", "Skilled", "Skulker", "Spell Sniper", "Tavern Brawler", "Tough", "War Caster", "Weapon Master"};
        int index = rand() % 38;
        return feats[index];
    }
};

class RandomBackground {
public:
    string getRandomBackground() {
        string backgrounds[] = {"Acolyte", "Charlatan", "Criminal", "Entertainer", "Folk Hero", "Guild Artisan", "Hermit", "Noble", "Outlander", "Sage", "Sailor", "Soldier", "Urchin"};
        int index = rand() % 13;
        return backgrounds[index];
    }
};

class D20CharacterGenerator {
public:
    Character generateCharacter(string name) {
        RandomNumAbilities abilityRoller;
        RandomClass classGenerator;
        RandomRace raceGenerator;
        RandomFeats featGenerator;

        Character newChar;
        newChar.name = name;
        newChar.race = raceGenerator.getRandomRace();
        newChar.background = RandomBackground().getRandomBackground();
        newChar.feat = featGenerator.getRandomFeat();
        newChar.charClass = classGenerator.getRandomClass();
        newChar.strength = abilityRoller.rollAbility();
        newChar.dexterity = abilityRoller.rollAbility();
        newChar.constitution = abilityRoller.rollAbility();
        newChar.intelligence = abilityRoller.rollAbility();
        newChar.wisdom = abilityRoller.rollAbility();
        newChar.charisma = abilityRoller.rollAbility();

        return newChar;
    }
};

class D20CharacterPrinter {
public:
    void printCharacter(const Character& c) {
        cout << "Name: " << c.name << endl;
        cout << "Class: " << c.charClass << " Level " << c.level << endl;
        cout << "Race: " << c.race << endl;
        cout << "Background: " << c.background << endl;
        cout << "Feat: " << c.feat << endl;
        cout << "Strength: " << c.strength << " (mod " << c.abilityMod(c.strength) << ")" << endl;
        cout << "Dexterity: " << c.dexterity << " (mod " << c.abilityMod(c.dexterity) << ")" << endl;
        cout << "Constitution: " << c.constitution << " (mod " << c.abilityMod(c.constitution) << ")" << endl;
        cout << "Intelligence: " << c.intelligence << " (mod " << c.abilityMod(c.intelligence) << ")" << endl;
        cout << "Wisdom: " << c.wisdom << " (mod " << c.abilityMod(c.wisdom) << ")" << endl;
        cout << "Charisma: " << c.charisma << " (mod " << c.abilityMod(c.charisma) << ")" << endl;
        cout << "Prof Bonus: +" << c.proficiencyBonus() << endl;
    }

    void exportToJson(const Character& c, const string& filename) {
    Json::Value charData;

    // Basic info
    charData["CharacterName"] = c.name;
    charData["ClassLevel"]    = c.charClass + " " + to_string(c.level);
    charData["Race"]          = c.race;
    charData["Background"]    = c.background;
    charData["Feat+Traits"]   = c.feat;

    // Abilities
    charData["STR"] = c.strength;
    charData["DEX"] = c.dexterity;
    charData["CON"] = c.constitution;
    charData["INT"] = c.intelligence;
    charData["WIS"] = c.wisdom;
    charData["CHA"] = c.charisma;

    // Modifiers (always integers, no "+")
    charData["STRmod"] = c.abilityMod(c.strength);
    charData["DEXmod"] = c.abilityMod(c.dexterity);
    charData["CONmod"] = c.abilityMod(c.constitution);
    charData["INTmod"] = c.abilityMod(c.intelligence);
    charData["WISmod"] = c.abilityMod(c.wisdom);
    charData["CHamod"] = c.abilityMod(c.charisma);

    // Derived stats
    charData["ProfBonus"] = c.proficiencyBonus();
    charData["AC"]        = c.armorClass();
    charData["Initiative"]= c.initiative();
    charData["Speed"]     = c.speed();
    charData["HPMax"]     = c.hitPoints();
    charData["HPCurrent"] = c.hitPoints();

    // Saving throws (always raw integers)
    charData["ST Strength"]     = c.abilityMod(c.strength);
    charData["ST Dexterity"]    = c.abilityMod(c.dexterity);
    charData["ST Constitution"] = c.abilityMod(c.constitution);
    charData["ST Intelligence"] = c.abilityMod(c.intelligence);
    charData["ST Wisdom"]       = c.abilityMod(c.wisdom);
    charData["ST Charisma"]     = c.abilityMod(c.charisma);

    // Skills (always raw integers)
    charData["Acrobatics"]    = c.abilityMod(c.dexterity);
    charData["Animal"]        = c.abilityMod(c.wisdom);
    charData["Arcana"]        = c.abilityMod(c.intelligence);
    charData["Athletics"]     = c.abilityMod(c.strength);
    charData["Deception"]     = c.abilityMod(c.charisma);
    charData["History"]       = c.abilityMod(c.intelligence);
    charData["Insight"]       = c.abilityMod(c.wisdom);
    charData["Intimidation"]  = c.abilityMod(c.charisma);
    charData["Investigation"] = c.abilityMod(c.intelligence);
    charData["Medicine"]      = c.abilityMod(c.wisdom);
    charData["Nature"]        = c.abilityMod(c.intelligence);
    charData["Perception"]    = c.abilityMod(c.wisdom);
    charData["Performance"]   = c.abilityMod(c.charisma);
    charData["Persuasion"]    = c.abilityMod(c.charisma);
    charData["Religion"]      = c.abilityMod(c.intelligence);
    charData["SleightofHand"] = c.abilityMod(c.dexterity);
    charData["Stealth"]       = c.abilityMod(c.dexterity);
    charData["Survival"]      = c.abilityMod(c.wisdom);


        // --- Ensure output folder exists ---
        string folder = "../output";
        mkdir(folder.c_str(), 0755);  // creates if not exists (safe to call)

        // --- Write file ---
        ofstream file(filename, ios::trunc);  // force overwrite
        cout << "✅ Writing JSON to: " << filename << endl;  // debug
        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        Json::StreamWriterBuilder writer;
        file << Json::writeString(writer, charData);
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    string characterName;
    cout << "Enter your character's name: ";
    getline(cin, characterName);

    D20CharacterGenerator generator;
    Character myCharacter = generator.generateCharacter(characterName);

    D20CharacterPrinter printer;
    printer.printCharacter(myCharacter);
    printer.exportToJson(myCharacter, "../output/character.json");

    return 0;
}