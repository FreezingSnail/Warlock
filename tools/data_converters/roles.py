import csv
import sys
import pprint
import struct
from serialize import write_fx_data
# Rest of the code...
class Role:
    def __init__(self,  power, finesse, bulk, mana, speed, luck):
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
def serialize_role(role):
    serialized_data = struct.pack('BBBBBB', role.power, role.finesse, role.bulk, role.mana, role.speed, role.luck)
    return serialized_data

def read_csv_to_role(file_path):
    data_dict = []
    with open(file_path, 'r') as file:
        reader = csv.DictReader(file, delimiter='	')
        for row in reader:
            power = int(row['power'])
            finesse = int(row['finesse'])
            bulk = int(row['bulk'])
            mana = int(row['mana'])
            speed = int(row['speed'])
            luck = int(row['luck'])
            role_obj = Role(power, finesse, bulk, mana,speed, luck)
            data_dict.append(role_obj)
    return data_dict

def serialize_role_list(role_list):
    serialized_data_list = []
    for role in role_list:
        serialized_data = serialize_role(role)
        serialized_data_list.append(serialized_data)
    return serialized_data_list


def main():
    if len(sys.argv) < 2:
        print("Please provide a relative file path as a command line argument.")
        return
   

    file_path = sys.argv[1]
    data = read_csv_to_role(file_path)
    serialized_data_list = serialize_role_list(data)
    write_fx_data(serialized_data_list, "roles")

    # Perform further operations with the data_dict


if __name__ == "__main__":
    main()