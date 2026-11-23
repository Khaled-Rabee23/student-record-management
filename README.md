# Student Record Management System

A C++ console application demonstrating two approaches to storing and managing student records:

1. **Fixed-length records** — uses fixed-size character arrays for names and dates of birth.
2. **Variable-length records** — uses `std::string` for text fields and includes a secondary index by name.

Both versions support common record-management operations and persist records in comma-separated text files.

## Project structure

```text
student-record-management/
├── data/
│   ├── users3.txt
│   └── users6.txt
├── src/
│   ├── fixed_length.cpp
│   └── variable_length.cpp
├── .gitignore
├── Makefile
└── README.md
```

## Requirements

- A C++ compiler (GCC or Clang)
- GNU Make
- C++11 or later

On Debian/Ubuntu:

```bash
sudo apt update
sudo apt install build-essential
```

## Build both versions

From the project root:

```bash
make
```

This creates:

- `build/fixed_length`
- `build/variable_length`

## Run

Run the fixed-length implementation:

```bash
make run-fixed
```

Run the variable-length implementation:

```bash
make run-variable
```

Or execute the compiled programs directly from the project root:

```bash
./build/fixed_length
./build/variable_length
```

Run from the project root because the programs use relative paths under `data/`.

## Features represented in the implementations

| Feature | Fixed-length version | Variable-length version |
|---|---|---|
| Record storage | Fixed-size array of `Record` | Fixed-size array of `Record` |
| Name and date fields | `char` arrays | `std::string` |
| Create record | Yes | Yes |
| Update record | Yes | Yes |
| Delete record | Yes; shifts later records | Yes; marks record deleted and tracks reusable slots |
| Display records | Yes | Yes |
| Sequential search | Yes | Yes |
| Primary index | `std::map<int, int>` | `std::map<int, int>` |
| Binary search | Yes | Not exposed in the menu |
| Secondary name index | No | `std::unordered_map<std::string, std::vector<int>>` |
| File persistence | `users3.txt` | `users6.txt` |

This table describes the supplied source code's intended and implemented menu/features; it is not a correctness certification.

## Data format

Each line is a comma-separated record:

```text
id,name,score,date_of_birth
```

Example:

```text
1,Alice,90,23/05/1998
```

The sample data files each contain 50 records.

## Important implementation notes

- The fixed-length implementation uses `char name[50]` and `char DofB[15]`, so input is limited by those array sizes.
- The variable-length implementation uses `std::string`, a primary index by ID, a secondary index by name, and an avail list for deleted slots.
- The original implementations are kept as two separate programs so their storage approaches can be compared.
- The source code has been adjusted only to use the repository's `data/` paths and remove the personal student-number header comments.
- The original code contains logic that deserves review before relying on it for real data. In particular, index maintenance, deleted-record handling, and capacity/input validation should be tested carefully.

## Clean generated binaries

```bash
make clean
```
