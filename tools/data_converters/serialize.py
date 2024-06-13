def write_fx_data(data, output_file_name):
    output_file_path = "fxdata/generated/" + output_file_name + ".bin"
    with open(output_file_path, 'wb') as file:
        for d in data:
            file.write(d)
    print("Serialized seeds written to:", output_file_path)




