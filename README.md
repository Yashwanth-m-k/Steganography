# Steganography Project

This is a simple yet powerful Steganography tool that hides secret files (such as text or code) within BMP image files using the Least Significant Bit (LSB) technique. The project supports both **encoding** and **decoding** operations, allowing you to hide and retrieve data seamlessly.

## Project Description

The **Steganography** project allows you to hide files within an image without affecting its visual appearance. The tool embeds secret files (such as `.txt`, `.c`, `.sh`, or other file types) into the least significant bits of a BMP image’s pixel data. Once encoded, the image appears unchanged, but it contains hidden data that can later be decoded and retrieved.

### Key Components:
1. **Encoding**: 
   - Allows encoding a secret file (text, code, or any other type) into a BMP image.
   - The secret file's size, extension, and content are embedded in the image’s pixel data using LSB encoding.
   - The image visually remains unchanged, but it holds hidden data inside it.

2. **Decoding**:
   - Retrieves the hidden secret file from a BMP image.
   - The system extracts the secret data from the image's least significant bits and reconstructs the original file with its content and extension.

---

## Features:
- **Encoding and Decoding**: Supports both encoding a secret file into an image and decoding it back into its original format.
- **LSB Encoding**: Hides data using the least significant bit of each byte, ensuring minimal visual impact on the image.
- **Flexible File Support**: Supports `.txt`, `.c`, `.sh`, or other file types for encoding.
- **User-Friendly Command-Line Interface**: Simple CLI to encode/decode files with ease.
- **Cross-Platform**: Works on any system that supports C (Linux, macOS, Windows).

---

## Prerequisites:

Before running this project, make sure you have the following installed:

- **C Compiler**: GCC or Clang (for compiling C code)
- **Make** (optional but recommended for easy compilation)
- **BMP Images**: The project works with `.bmp` image files.

---

## Installation:

To install the project, follow these steps:

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/yourusername/steganography.git
## usage :
Encode Example:
./a.out : Encoding: ./a.out -e <.bmp.file> <.txt.file> [output file <.bmp.file> ]
Decode Example:
./a.out : Decoding: ./a.out -d <.bmp.file> [output file]
