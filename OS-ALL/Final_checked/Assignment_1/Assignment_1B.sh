#!/bin/bash

ADDRESS_BOOK_FILE="address_book.txt"

create_address_book() {
    touch "$ADDRESS_BOOK_FILE"
    echo "Address book created."
}

view_address_book() {
    if [ ! -s "$ADDRESS_BOOK_FILE" ]; then
        echo "Address book is empty."
        return
    fi

    cat -n "$ADDRESS_BOOK_FILE"
}

insert_record() {
    read -p "Enter name: " name
    read -p "Enter phone number: " phone

    echo "$name - $phone" >> "$ADDRESS_BOOK_FILE"
    echo "Record inserted successfully."
}

delete_record() {
    view_address_book
    read -p "Enter the line number to delete: " line_number

    sed -i "${line_number}d" "$ADDRESS_BOOK_FILE"
    echo "Record deleted successfully."
}

modify_record() {
    view_address_book
    read -p "Enter the line number to modify: " line_number
    read -p "Enter new name: " new_name
    read -p "Enter new phone number: " new_phone

    sed -i "${line_number}s/.*/${new_name} - ${new_phone}/" "$ADDRESS_BOOK_FILE"
    echo "Record modified successfully."
}

while true; do
    echo -e "\nOptions:"
    echo "1) Create address book."
    echo "2) View address book."
    echo "3) Insert a record."
    echo "4) Delete a record."
    echo "5) Modify a record."
    echo "6) Exit"

    read -p "Enter your choice (1-6): " choice

    case "$choice" in
        1)
            create_address_book;;
        2)
            view_address_book;;
        3)
            insert_record;;
        4)
            delete_record;;
        5)
            modify_record;;
        6)
            echo "Exiting the address book program."
            break;;
        *)
            echo "Invalid choice. Please try again.";;
    esac
done
