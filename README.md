# C - Simple Bank System

A simple bank management system to simulate bank employee and customer interactions.

Users can:
- Select between Employee or Customer.
- Can register and login for either.

Employees can:
- Manage customer accounts
- View user transaction histories
- Simulate transferring money for the customer
- Can view a customer's loans
- Generate a full report on a customer account
- Close a customer account

Customers can:
- View their account details
- Check their account balance
- Simulate depositing to their accounts
- Apply for loans

My favorite part in making this project was my implementation of what I call "Data Lines"
wherein without using a proper database, I was able to make a type of local database that
properly handles CRUD (Create, Read, Update, Delete) operations by having all the data for
a specific user in just one line and only manipulating that line to perform CRUD.