# CLI-Based Contact Manager

## Project

A simple CLI-based Contact Manager built in C that allows users to perform core contact operations with automatic text file persistence:

- **Display Contacts** – View all saved contacts.
- **Search Contact** – Search entries by name.
- **Add Contact** – Append new contacts dynamically.
- **Edit Contact** – Modify existing entry details.
- **Delete Contact** – Remove entries and resize storage.

Contact data is stored as CSV records in:

```text
Contact-Manager/contacts.txt
```

**Compiler tested:** `gcc version 13.3.0`

## Objective

The objective of this project is to practice core C programming concepts:

1. **Control Flow** (`do-while`, `switch-case`)
2. **Structs & Struct Arrays** (`Contact`)
3. **Dynamic Memory Management** (`malloc`, `realloc`, `free`)
4. **Pointers & Double Pointers** (passing array pointers by reference)
5. **File I/O** (`fopen`, `fgets`, `fprintf`, `sscanf`)

## Quick Start

### Step 1: Clone the Repository

```bash
git clone https://github.com/sparsh240/CLI-Contact-Manager.git $HOME/contactMgr
cd $HOME/contactMgr
```

**Important:** Do not delete `Contact-Manager/contacts.txt` — it stores the contacts.

### Step 2: Compile

**Linux / macOS:**

```bash
gcc Contact-Manager/contact_manager.c -o manager
```

**Windows:**

```bash
gcc Contact-Manager/contact_manager.c -o manager.exe
```

### Step 3: Run

**Linux / macOS:**

```bash
./manager
```

**Windows:**

```cmd
manager.exe
```