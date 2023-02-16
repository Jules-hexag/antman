#! /usr/bin/env python3
#
# This script is a simple fuzzer for the antman. It generates random files and
# tries to compress and decompress them. It should be run from the root of the
# repository.
#
# Dependencies:
# - `colorama` (pip install colorama)

from os import urandom, remove
from subprocess import DEVNULL, run
from colorama import Fore
from random import randint
from hashlib import md5

antman_bin = "./antman/antman"
giantman_bin = "./giantman/giantman"


def fuzz(count: int):
    # Generate a file with random bytes
    with open("random.fuzz", "w") as f:
        f.write(str(urandom(1024)))

    # Run antman
    with open("random.fuzz.antman", "w") as output:
        proc = run([antman_bin, "random.fuzz", "1"], stdout=output)
        if proc.returncode != 0:
            print(Fore.RED + f"Failed to compress random.fuzz")
            return

    # Run giantman
    with open("random.fuzz.giantman", "w") as output:
        proc = run([giantman_bin, "random.fuzz.antman", "1"], stdout=output)
        if proc.returncode != 0:
            print(Fore.RED + f"Failed to decompress random.fuzz.antman")
            return

    # Compare the original file with the decompressed file
    with open("random.fuzz", "rb") as f:
        original_hash = md5(f.read()).hexdigest()
    with open("random.fuzz.giantman", "rb") as f:
        decompressed_hash = md5(f.read()).hexdigest()

    if original_hash != decompressed_hash:
        print(Fore.RED + f"Decompressed file is not identical to original file")
        return

    print(Fore.GREEN + f"{count} tests passed")

    # Remove output files
    remove("random.fuzz")
    remove("random.fuzz.antman")
    remove("random.fuzz.giantman")


if __name__ == "__main__":
    count = 0

    try:
        while True:
            fuzz(count)
            count += 1
    except KeyboardInterrupt:
        print(Fore.RED + "Program interrupted by user")
