# PythML Installation Guide

## Prerequisites
Ensure you have the following dependencies installed before proceeding with the installation:

- CMake (3.25+)
- Python (3.8, 3.9, 3.10, 3.11, or 3.12)
- Python development headers
- xsltproc
- HTML Tidy

### Installing Dependencies on Ubuntu
```sh
sudo apt-get update
sudo apt-get install -y cmake python3 python3-dev python3-pip xsltproc tidy
```

## Building HTML Tidy
PYTHML requires an updated version of HTML Tidy. You can build it from source as follows:

```sh
git clone https://github.com/htacg/tidy-html5.git /tmp/tidy-html5
cd /tmp/tidy-html5
cd build/cmake
cmake ../.. -DCMAKE_BUILD_TYPE=Release
make
sudo make install
```

## Installing PYTHML

### Cloning the Repository
```sh
git clone https://github.com/rajpandya737/PYTHML pythml
cd pythml/pythml
```

### Building with CMake
```sh
mkdir -p build
cd build
cmake ..
make
```

## Using PYTHML
After building, you can run PYTHML to process your HTML files with embedded Python code. Simply execute:
```sh
./pythml <your-html-file>
```

Replace `<your-html-file>` with the path to the HTML file containing embedded Python code.


