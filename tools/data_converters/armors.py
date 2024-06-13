import csv
import sys
import pprint
import struct
from serialize import write_fx_data
# Rest of the code...
class Armor:
    def __init__(self, ap, power, finesse, bulk, mana, speed, luck):
        self.ap = ap
        self.power = power
        self.finesse = finesse
        self.bulk = bulk
        self.mana = mana
        self.luck = luck
        self.speed = speed


#     uint8_t power;     // physical
#     uint8_t finesse;   // ranged
#     uint8_t bulk;      // health
#     uint8_t mana;      // magic
#     uint8_t speed;     // initiative
#     uint8_t luck;
def serialize_armor(armor):
    serialized_data = struct.pack('BBBBBBB', armor.ap, armor.power, armor.finesse, armor.bulk, armor.mana, armor.speed, armor.luck)
    return serialized_data

def read_csv_to_armor(file_path):
    data_dict = []
    with open(file_path, 'r') as file:
        reader = csv.DictReader(file, delimiter='	')
        for row in reader:
            ap = int(row['ap'])
            power = int(row['power'])
            finesse = int(row['finesse'])
            bulk = int(row['bulk'])
            mana = int(row['mana'])
            speed = int(row['speed'])
            luck = int(row['luck'])
            armor_obj = Armor(ap, power, finesse, bulk, mana,speed, luck)
            data_dict.append(armor_obj)
    return data_dict

def serialize_armor_list(armor_list):
    serialized_data_list = []
    for armor in armor_list:
        serialized_data = serialize_armor(armor)
        serialized_data_list.append(serialized_data)
    return serialized_data_list


def main():
    if len(sys.argv) < 3:
        print("Please provide a relative file path as a command line argument.")
        return
   

    file_path = sys.argv[1]
    output_filename = sys.argv[2]
    data = read_csv_to_armor(file_path)
    serialized_data_list = serialize_armor_list(data)
    write_fx_data(serialized_data_list, output_filename)

    # Perform further operations with the data_dict


if __name__ == "__main__":
    main()