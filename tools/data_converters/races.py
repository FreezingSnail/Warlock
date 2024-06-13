import csv
import sys
import pprint
import struct
from serialize import write_fx_data
# Rest of the code...
class Race:
    def __init__(self, race, power, finesse, bulk, mana, speed, luck):
        self.race = race
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
def serialize_race(race):
    serialized_data = struct.pack('BBBBBB', race.power, race.finesse, race.bulk, race.mana, race.speed, race.luck)
    return serialized_data

def read_csv_to_race(file_path):
    data_dict = []
    with open(file_path, 'r') as file:
        reader = csv.DictReader(file, delimiter='	')
        for row in reader:
            race = row['race']
            power = int(row['power'])
            finesse = int(row['finesse'])
            bulk = int(row['bulk'])
            mana = int(row['mana'])
            speed = int(row['speed'])
            luck = int(row['luck'])
            race_obj = Race(race, power, finesse, bulk, mana,speed, luck)
            data_dict.append(race_obj)
    return data_dict

def serialize_race_list(race_list):
    serialized_data_list = []
    for race in race_list:
        serialized_data = serialize_race(race)
        serialized_data_list.append(serialized_data)
    return serialized_data_list


def main():
    if len(sys.argv) < 2:
        print("Please provide a relative file path as a command line argument.")
        return

    file_path = sys.argv[1]
    data = read_csv_to_race(file_path)
    serialized_data_list = serialize_race_list(data)
    write_fx_data(serialized_data_list, "races")

    # Perform further operations with the data_dict


if __name__ == "__main__":
    main()