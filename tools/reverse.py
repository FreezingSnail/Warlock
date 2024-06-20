from PIL import Image
import re

def parse_c_header(filename):
    with open(filename, 'r') as f:
        content = f.read()

    pattern = r'const uint8_t PROGMEM (\w+)\[] = {(.*?)};'
    matches = re.findall(pattern, content, re.DOTALL)

    arrays = {}
    for name, values in matches:
        values = values.split(',')
        values = [value.strip() for value in values if value.strip()]
        arrays[name] = values

    return arrays


def print_img(width, height, data, name):
    data = [int(value, 16) for value in data]
    binary_values = [bin(value)[2:].zfill(8)[::-1] for value in data]

    w =int(width, 10) 
    h = int(height, 10)
    # Create a new image with white background
    img = Image.new('RGB', (w, h), color = 'black')

    # Map binary values to image rows
    index = 0

    for i in range(h//8):
        for j in range(w):
            byte = binary_values[index]
            for k, bit in enumerate(byte):
                if bit == '1':
                    img.putpixel((j,(i*8)+k), (255, 255, 255))
            index += 1
    img.save("decomp/"+name+'.png')


def main():
    filename = 'img.h'
    arrays = parse_c_header(filename)
    for name, data in arrays.items():
        print(name, data[:3])
        print_img(data[0], data[1], data[2:], name)

if __name__ == "__main__":
    main()

