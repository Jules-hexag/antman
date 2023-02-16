#! /usr/bin/env python3
#
# This script is used to test the compression ratio of the antman. It should be
# run from the root of the repository.
#
# Dependencies:
# - `colorama` (pip install colorama)

from glob import glob
from subprocess import run
from time import time
from os import path, remove
from hashlib import md5

from colorama import Fore

antman_bin = "./antman/antman"
giantman_bin = "./giantman/giantman"


def test_file(file: str):
    output_compressed = file + ".antman"
    output_decompressed = file + ".giantman"

    # Run antman and get execution time
    compression_start = time()
    with open(output_compressed, "w") as output:
        run([antman_bin, file, "1"], stdout=output)
    compression_end = time()

    # Compute size difference between original and compressed file
    original_size = path.getsize(file)
    compressed_size = path.getsize(output_compressed)
    size_difference = original_size - compressed_size
    ratio = size_difference / original_size

    # Decompress file and get execution time
    decompression_start = time()
    with open(output_decompressed, "w") as output:
        run([giantman_bin, output_compressed, "1"], stdout=output)
    decompression_end = time()

    # Print results
    print(Fore.BLUE + path.basename(file), end="\t")
    print(Fore.GREEN + f"{ratio:.2%}", end="\t")
    print(Fore.YELLOW + f"{compression_end - compression_start:.2f}s", end="\t")
    print(Fore.RED + f"{decompression_end - decompression_start:.2f}s")

    # Ensure decompressed file is identical to original file
    with open(file, "rb") as f:
        original_hash = md5(f.read()).hexdigest()
    with open(output_decompressed, "rb") as f:
        decompressed_hash = md5(f.read()).hexdigest()

    if original_hash != decompressed_hash:
        print(Fore.RED + "Decompressed file is not identical to original file")

    # Remove output file
    remove(output_compressed)
    remove(output_decompressed)


if __name__ == "__main__":
    files = glob("./bonus/test_files/*")

    for file in files:
        test_file(file)
