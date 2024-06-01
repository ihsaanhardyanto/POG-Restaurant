# Restaurant Ordering System

This program is a console-based restaurant ordering system written in C. It includes functionality for viewing the menu, placing orders, 
and managing a cart, as well as an admin panel for managing the menu items.

## Main Functionalities
### Viewing the Menu
The program reads the menu items from a file named Menu.txt.
Menu items are displayed in a paginated format, showing 10 items per page.
Users can navigate between pages using the '>' and '<' keys.

### Placing an Order:

Users can search for menu items by typing a substring of the item name.
The search is case-insensitive and updates results as the user types.
When the user presses Enter, the selected item is added to their order.

### Viewing the Cart

Displays all items that have been added to the cart.
Shows the total price of all items in the cart.
Provides an option to pay for the items in the cart.
If the payment amount is sufficient, the cart is cleared; if not, the user is informed that their balance is insufficient.

### Admin Panel

Accessed by selecting the hidden option 123 in the main menu.
Allows admins to add new menu items or remove existing ones.
New menu items are appended to the Menu.txt file.
Menu items can be removed by specifying their name, which updates the Menu.txt file accordingly.

## Menu Options
### Menu

Displays the list of menu items, sorted alphabetically.
Allows pagination to navigate through items if there are more than 10.
### Order

Enables users to search for menu items and add them to their order.
Real-time search feedback as the user types.
### Cart

Shows items currently in the user's cart along with the total price.
Provides options to pay for the items or go back to the main menu.

### Exit

Exits the program with a farewell message.

## Admin Menu
### Add Menu

Prompts the admin to enter the name and price of a new menu item.
Adds the new item to the Menu.txt file.

### Remove Menu

Prompts the admin to enter the name of the menu item to be removed.
Removes the specified item from the Menu.txt file.

### Exit
Exits the admin menu and returns to the main menu.

## Additional Details
### File Handling
The Menu.txt file is used to store menu items with their names and prices.
The program reads from this file to display menu items and writes to it when adding or removing items.
