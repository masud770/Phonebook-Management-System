# 📒 Phonebook Management System in C

This project is an **academic team project** developed as part of our coursework in C programming.  
It is a console-based **Phonebook Management System** that allows users to store, view, search, modify, and delete contact information.  
The project demonstrates the use of **structured programming, file handling, and data validation** in C.

---

## 🧩 Features
✅ Add New Contact – Save full contact details such as name, address, parents’ names, mobile number, and email.  
✅ List All Contacts – View all saved records in a clean format.  
✅ Search Contact – Find a contact by name quickly.  
✅ Modify Contact – Edit existing contact details.  
✅ Delete Contact – Safely remove a record from storage.  
✅ Email Validation – Validates the format of the entered email.  
✅ File-Based Storage – Stores data persistently using binary files (.dat).  
✅ User-Friendly Interface – Simple and menu-driven console design.

---

## 🏗️ System Architecture
**Core Components:**
- `struct person` – Defines the data structure for each contact.
- `isValidEmail()` – Checks and validates email syntax.
- File operations – `fopen()`, `fwrite()`, `fread()`, `fseek()`, `remove()`, `rename()`.
- Core functions – `menu()`, `addrecord()`, `listrecord()`, `modifyrecord()`, `deleterecord()`, `searchrecord()`.
- Input handling – `got()` function for safe text input.

---

## 🧠 Function Overview
| Function | Description |
|-----------|-------------|
| menu() | Displays the main menu and handles user choices. |
| addrecord() | Adds a new contact record. |
| listrecord() | Lists all stored contacts. |
| searchrecord() | Searches a record by name. |
| modifyrecord() | Updates an existing record. |
| deleterecord() | Deletes a record permanently. |
| isValidEmail() | Validates entered email format. |
| got() | Handles safe input from user (custom gets()). |

---

## 🖥️ User Interface
The program runs in a command-line environment with a text-based interface.  
The main menu appears as follows:

