import math
from collections import Counter

def calculate_entropy(data):
    """
    Calculate the entropy of a given data set.
    
    :param data: A byte string for which to calculate the entropy.
    :return: The entropy value.
    """
    if not data:
        return 0.0

    # Calculate the frequency of each byte in the data
    byte_count = Counter(data)
    total_bytes = len(data)
    
    # Calculate the entropy
    entropy = 0.0
    for count in byte_count.values():
        probability = count / total_bytes
        entropy -= probability * math.log2(probability)
    
    return entropy

def read_file(file_path):
    """
    Read the content of a file.
    
    :param file_path: Path to the file to be read.
    :return: The content of the file.
    """
    with open(file_path, 'rb') as file:
        return file.read()

if __name__ == "__main__":
    import argparse
    
    parser = argparse.ArgumentParser(description="Calculate the entropy of a file.")
    parser.add_argument("file", help="Path to the file")
    args = parser.parse_args()
    
    file_content = read_file(args.file)
    entropy = calculate_entropy(file_content)
    
    print(f"The entropy of the file '{args.file}' is: {entropy}")

