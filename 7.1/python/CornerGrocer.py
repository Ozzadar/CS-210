
def calculate_word_frequency(filepath: str) -> dict:
    items = {}

    # Open file in read-only mode
    try:
        with open("data/CS210_Project_Three_Input_File.txt", 'r') as file:
            # Get all lines in file
            lines = file.readlines()

            # loop through them
            for line in lines:
                # Strip any leading or trailing whitespace
                key = line.strip()

                # add it to dictionary if it hasn't been counted before
                if key not in items.keys():
                    items[key] = 0

                items[key] += 1
    except IOError as e:
        print("I/O error({0}): {1}".format(e.errno, e.strerror))

    return items


def print_item_frequencies_in_file(filepath: str) -> None:
    width = 120
    print("Calculating Frequency for words in file:", filepath)
    items = calculate_word_frequency(filepath)

    print(('*' * 50).center(width, ' '))
    print("Day's purchases".center(width, ' '))
    print(('*' * 50).center(width, ' '))

    for key, value in items.items():
        print(f'{key:<20} {value:>20}'.center(width, ' '))

    print(('*' * 50).center(width, ' '))


def get_frequency_for_item_in_file(item: str, filepath: str) -> int:
    items = calculate_word_frequency(filepath)

    # if the item is not in the list, return 0
    # otherwise return the counted number
    return 0 if item not in items.keys() else items[item]


def output_frequencies_to_file(in_file: str, out_file: str) -> None:
    items = calculate_word_frequency(in_file)

    # open the file for writing, we will overwrite
    try:
        with open(out_file, 'w') as f:
            for key, value in items.items():
                print(key, value, file=f)

    except IOError as e:
        print("I/O error({0}): {1}".format(e.errno, e.strerror))