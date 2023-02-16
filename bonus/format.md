# Antman file format

The following document describes the format used by the antman compression
algorithm.

Antman algorithm is a generic compression algorithm based on [LZSS][lzss] and
a static [dictionary coder][dict-coder]. For PPM images, an additional encoding step is performed before the compression.

This algorithm is optimized for lyrics, HTML pages and PPM but should work
with any file format.

> Note: due to a lack of time, **dictionary coder and PPM encoding are not
> currently implemented**.

## Data chunks


Each chunk of data starts with the following header:

```c
struct chunk_header {
    uint16_t size;     // size of the chunk
}
```

The maximum size of a chunk is `2^16 - 1 = 65535` bytes (64KB).

In some cases, the compressed chunk size may be larger than the origin one
(i.e. if the chunk is not compressible).

## Compression chunks

Each data chunk contains one or more compression chunks. The type of each chunk
can be determined by looking at the first two bits of the chunk header.

### Uncompressed chunk

Uncompressed chunks (or raw chunks) contains data that haven't been compressed
and should be copied as-is in the output buffer.

```c
struct raw_chunk {  // size = 2 bytes (excluding data)
    uint8_t type: 2;   // 0b00
    uint16_t size: 14; // data size (-1 offset)
    uint8_t data[];    // uncompressed data
};
```

The maximum size of an uncompressed chunk is `2^14 = 16384` bytes (16KB).

Note that `0` is an illegal value for `size` since it is encoded with an offset
of -1 (`0` will be interpreted as `1`).

### LZSS chunk

```c
struct lzss_chunk_small { // size = 2 bytes
    uint8_t type: 2;   // 0b01
    uint8_t offset: 6; // match offset (-1 offset)
    uint8_t length; // match length
}

struct lzss_chunk_large {  // size = 4 bytes
    uint8_t type: 2;   // 0b10
    uint16_t offset: 14; // match offset (-1 offset)
    uint16_t length;   // match length
};
```

For small chunks, the maximum offset is `2^6 = 64` bytes and the maximum length
is `2^8 - 1 = 255` bytes.

For large chunks, the maximum offset is `2^14 = 16383` bytes (16KB) and the
maximum length is `2^16 - 1 = 65535` bytes (64KB).

The chunk variant (small or large) will be defined by the offset and length
values. Matches of less than 4 bytes are encoded as uncompressed chunks.

### Dictionary chunk

```c
struct dict_chunk {  // size = 1 bytes
    uint8_t type: 2;     // 0b11
    uint8_t index: 6;    // index of the word in the dictionary
};
```

The dictionary contains 64 words.

Dictionary chunks will be prioritized over LZSS chunks when compressing because
of their smaller size.

## Dictionary

The dictionary is optimized for HTML encoding and contains some common English
words.

## PPM encoding

To improve compression rates, PPM images are encoded using binary instead of
ASCII numbers before compression.

[lzss]: https://en.wikipedia.org/wiki/Lempel%E2%80%93Ziv%E2%80%93Storer%E2%80%93Szymanski
[dict-coder]: https://en.wikipedia.org/wiki/Dictionary_coder
