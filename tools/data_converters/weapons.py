import csv
import sys
import pprint
import struct
from serialize import write_fx_data
# Rest of the code...
class Weapon:
    def __init__(self, ap, effect, t, power, finesse, bulk, mana, speed, luck, rolls, upper, lower):
        self.effect = effect
        self.ap = ap
        self.type = t
        self.power = power
        self.finesse = finesse
        self.bulk = bulk
        self.mana = mana
        self.luck = luck
        self.speed = speed
        self.rolls = rolls
        self.upper = upper
        self.lower = lower




def effect_to_int(effect):
    effects = {"none": 0, "bleed": 1, "burn": 2, "freeze": 3, "poison": 4, "shock": 5}
    return effects[effect.lower()]

def type_to_int(t):
    type = {"physical": 0, "ranged": 1, "magic": 2}
    return type[t.lower()]


#     uint8_t power;     // physical
#     uint8_t finesse;   // ranged
#     uint8_t bulk;      // health
#     uint8_t mana;      // magic
#     uint8_t speed;     // initiative
#     uint8_t luck;
def serialize_weapon(weapon):
    serialized_data = struct.pack('BBBBBBBBBBBB', weapon.effect,weapon.ap, weapon.type, weapon.rolls, weapon.lower, weapon.upper, weapon.power, weapon.finesse, weapon.bulk, weapon.mana, weapon.speed, weapon.luck)
    return serialized_data

def read_csv_to_weapon(file_path):
    data_dict = []
    with open(file_path, 'r') as file:
        reader = csv.DictReader(file, delimiter='	')
        for row in reader:
            ap = int(row['ap'])
            effect = (effect_to_int(str(row['effect'])))
            t = (type_to_int(str(row['type'])))
            rolls = int(row['rolls'])
            upper = int(row['upper'])
            lower = int(row['lower'])
            power = int(row['power'])
            finesse = int(row['finesse'])
            bulk = int(row['bulk'])
            mana = int(row['mana'])
            speed = int(row['speed'])
            luck = int(row['luck'])
            weapon_obj = Weapon(ap, effect, t, power, finesse, bulk, mana, speed, luck, rolls, upper, lower)
            data_dict.append(weapon_obj)
    return data_dict

def serialize_weapon_list(weapon_list):
    serialized_data_list = []
    for weapon in weapon_list:
        serialized_data = serialize_weapon(weapon)
        serialized_data_list.append(serialized_data)
    return serialized_data_list


def main():
    if len(sys.argv) < 2:
        print("Please provide a relative file path as a command line argument.")
        return
   

    file_path = sys.argv[1]
    data = read_csv_to_weapon(file_path)
    serialized_data_list = serialize_weapon_list(data)
    write_fx_data(serialized_data_list, "weapons")

    # Perform further operations with the data_dict


if __name__ == "__main__":
    main()