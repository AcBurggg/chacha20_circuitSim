#generated using ChatGPT. 



import argparse
import os

def read_input(args):
    if args.text:
        return args.text
    elif args.file:
        if not os.path.isfile(args.file):
            raise FileNotFoundError(f"File not found: {args.file}")
        with open(args.file, 'r', encoding='utf-8') as f:
            return f.read()
    else:
        raise ValueError("Either --text or --file must be provided.")

def text_to_hex_blocks(text):
    output_lines = []
    i = 0
    while i < len(text):
        chunk = text[i:i+4]  # Only 4 characters = 8 hex characters
        hex_chunk = ''.join([f"{ord(c):02x}" for c in chunk])
        if len(chunk) < 4:
            pad_length = 4 - len(chunk)
            hex_chunk += '00' * pad_length
        output_lines.append(hex_chunk)
        i += 4
    return '\n'.join(output_lines)

def main():
    parser = argparse.ArgumentParser(description="Convert input text to ASCII hex values in 8-character blocks.")
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument('--text', type=str, help='Direct text input (e.g., "encrypt me now")')
    group.add_argument('--file', type=str, help='Path to a .txt file containing the input text')

    args = parser.parse_args()

    try:
        input_text = read_input(args)
        hex_output = text_to_hex_blocks(input_text)
        with open("hexoutput.dat", "w") as f:
            f.write(hex_output + '\n')
        print("Hex output written to hexoutput.dat")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
