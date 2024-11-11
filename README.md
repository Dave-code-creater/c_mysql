
# MySQL C Library

This C library provides utility functions to interact with a MySQL database using the MySQL Connector/C API. It includes functions to connect to a MySQL database and perform basic operations like displaying records, adding, updating, and deleting records in a table. 

Due to the limitations of C and the varied nature of table structures, this library does not include a `createTable` function.

## Features

- **Display Records**: Retrieve and display all records from a specified table.
- **Add Record**: Insert a single record into a specified table and field.
- **Update Record**: Update a specified field of a record in a table.
- **Delete Table**: Drop (delete) a specified table from the database.

## Requirements

- **MySQL Connector/C**: Make sure the MySQL client library is installed (`libmysqlclient-dev` on Debian/Ubuntu or `mysql-devel` on Red Hat-based systems).
- **MySQL Database**: You need access to a MySQL database with the appropriate credentials.

## Compilation

To compile the program, use the following command:

```bash
gcc -o mysql_library mysql_library.c -lmysqlclient
```
---
**NOTE**:
This is was written on Linux so Mysql Connector is required
---

## Function

This functions handles error, reporting and safely closes the MySQL connections.
* finishWithError
```bash
void finishWithError(MySQL *con);
```
Parameters:

    con: MySQL connection object.

This function prints the error message to stderr and terminates the program by closing the MySQL connection.
* displayAllFromTable

Displays all records from a specified table.

void displayAllFromTable(MYSQL *conn, const char *table);

Parameters:

    conn: The MySQL connection object.
    table: The name of the table to retrieve data from.

This function fetches and prints all records from the specified table.
* addRecordIntoTable

Adds a record into a specified table and field.

bool addRecordIntoTable(MYSQL *conn, const char *value, const char *table, const char *field);

Parameters:

    conn: The MySQL connection object.
    value: The value to be inserted.
    table: The name of the table where the record will be inserted.
    field: The name of the field into which the value will be inserted.

This function inserts a value into a table's field. It returns true if the insertion is successful and false otherwise.
* deleteTask

Deletes (drops) a specified table from the database.

bool deleteTask(MYSQL *conn, const char *table);

Parameters:

    conn: The MySQL connection object.
    table: The name of the table to be deleted.

This function deletes the specified table from the database. It returns true if the operation is successful, otherwise false.
* updateTaskInTable

Updates a specified field in a record within a table.

bool updateTaskInTable(MYSQL *conn, const char *table, const char *field, const char *newValue, const char *id_field, const char *id_value);

Parameters:

    conn: The MySQL connection object.
    table: The name of the table to be updated.
    field: The name of the field to be updated.
    newValue: The new value to be assigned to the field.
    id_field: The ID field name (typically primary key).
    id_value: The ID value of the record to be updated.

This function updates a field in the specified table for the given record ID. It returns true if the update is successful, otherwise false.
Example Usage

Here is an example showing how to use the displayAllFromTable function:
```C
#include <mysql/mysql.h>

MYSQL *conn;
conn = mysql_init(NULL);

if (conn == NULL) {
    fprintf(stderr, "mysql_init() failed
");
    exit(1);
}

if (mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0) == NULL) {
    finishWithError(conn);
}

displayAllFromTable(conn, "my_table");

mysql_close(conn);
```
## License

MIT
