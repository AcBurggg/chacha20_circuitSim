#generated using ChatGPT. 
#creates the .dat file with the hex values of the plaintext string that is to be encrypted
#can be loaded directly into ROM. Also used in expectedOutput.c in order to get the expected

def extract_plaintext_from_file(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        for line in f:
            if line.startswith("plaintext:"):
                start = line.find('"')
                end = line.rfind('"')
                if start != -1 and end != -1 and end > start:
                    return line[start+1:end]
    raise ValueError("No valid plaintext string found in inputs.txt")

def text_to_hex_blocks(text):
    output_lines = []
    i = 0
    while i < len(text):
        chunk = text[i:i+4]
        hex_chunk = ''.join(f"{ord(c):02x}" for c in chunk)
        if len(chunk) < 4:
            hex_chunk += '00' * (4 - len(chunk))
        output_lines.append(hex_chunk)
        i += 4
    return '\n'.join(output_lines)

def main():
    try:
        input_text = extract_plaintext_from_file("inputs.txt")
        hex_output = text_to_hex_blocks(input_text)
        with open("hexoutput.dat", "w") as f:
            f.write(hex_output + '\n')
        print("Hex output written to hexoutput.dat")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
