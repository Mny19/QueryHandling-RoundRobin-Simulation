import os
import sys
from tqdm import tqdm
from termcolor import colored, cprint
from PIL import Image

class Encryption:

    def __init__(self, filename):
        self.filename = filename

    def encryption(self):
        try:
            original_image = Image.open(self.filename)
        except (IOError, FileNotFoundError):
            cprint('File with name {} is not found.'.format(self.filename), color='red', attrs=['bold', 'blink'])
            sys.exit(0)

        try:
            encrypted_file_name = 'cipher_' + self.filename
            encrypted_image = Image.new("RGB", original_image.size)

            key = 192
            cprint('Encryption Process is in progress...!', color='green', attrs=['bold'])
            for i in range(original_image.size[0]):
                for j in range(original_image.size[1]):
                    pixel = original_image.getpixel((i, j))
                    encrypted_pixel = tuple(val ^ key for val in pixel)
                    encrypted_image.putpixel((i, j), encrypted_pixel)

            encrypted_image.show()

        except Exception as e:
            cprint('Something went wrong with {}: {}'.format(self.filename, str(e)), color='red', attrs=['bold', 'blink'])

if __name__ == "__main__":
    space_count = 30 * ' '
    cprint('{} Image Encryption Tool. {}'.format(space_count, space_count), 'red')

    cprint('Enter the filename for Encryption with proper extension:', end=' ', color='yellow', attrs=['bold'])
    file = input()

    E1 = Encryption(file)
    E1.encryption()
