#include <mysql/mysql.h>
#include <string.h>

void finishWithError(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}



void displayAllFromTable(MYSQL* conn, const char *table)
{
    // Validate input
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    if (strcmp(table, "") == 0)
    {
        fprintf(stderr, "Invalid parameters\n");
        exit(1);
    }

    // Set up the default query is shorter than 256 characters
    char query[256];
    char queryTable[20];

    mysql_real_escape_string(conn, queryTable , table, strlen(table));
    snprintf(query, sizeof(query), "SELECT * FROM '%s'");


    if (mysql_query(conn, queryTable))
    {
        finish_with_error(conn);
    }
    MYSQL_RES *result = mysql_store_result(conn);

    if (result == NULL)
    {
        finish_with_error(conn);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            printf("%s ", row[i] ? row[i] : "NULL");
        }

        printf("\n");
    }
}

bool addRecordIntoTable(MYSQL *conn, const char *value, const char *table, const char *field) {
    char query[512];
    char escapedValue[64];
    char escapedTable[64];
    char escapedField[64];

    // Validate input
     if (conn == NULL) {
        fprintf(stderr, "Invalid MySQL connection.\n");
        return false;
    }
    if (table == NULL || strlen(table) == 0) {
        fprintf(stderr, "Table name cannot be empty.\n");
        return false;
    }
    if (field == NULL || strlen(field) == 0) {
        fprintf(stderr, "Field name cannot be empty.\n");
        return false;
    }
    if (value == NULL || strlen(value) == 0) {
        fprintf(stderr, "New value cannot be empty.\n");
        return false;
    }
    
    mysql_real_escape_string(conn, escapedValue, value, strlen(value));
    mysql_real_escape_string(conn, escapedTable, table, strlen(table));
    mysql_real_escape_string(conn, escapedField, field, strlen(field));

    
    snprintf(query, sizeof(query), "INSERT INTO `%s` (`%s`) VALUES ('%s')", escapedTable, escapedField, escapedValue);

    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        return false;
    }

    return true;
}

bool deleteTask(MYSQL *conn, const char *table){
    char query[512];
    char escapedTable[64];

    // Validate input
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return false;
    }
    if (strcmp(table, "") == 0)
    {
        fprintf(stderr, "Invalid parameters\n");
        return false;
    }
    
    mysql_real_escape_string(conn, escapedTable, table, strlen(table));

    snprintf(query, sizeof(query), "DROP TABLE '%s'", escapedTable)
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        return false;
    }
    return true;
}
bool updateTaskInTable(MYSQL *conn, const char *table, const char *field, const char *newValue, const char *id_field, const char *id_value) {
    // Validate inputs
    if (conn == NULL) {
        fprintf(stderr, "Invalid MySQL connection.\n");
        return false;
    }
    if (table == NULL || strlen(table) == 0) {
        fprintf(stderr, "Table name cannot be empty.\n");
        return false;
    }
    if (field == NULL || strlen(field) == 0) {
        fprintf(stderr, "Field name cannot be empty.\n");
        return false;
    }
    if (newValue == NULL || strlen(newValue) == 0) {
        fprintf(stderr, "New value cannot be empty.\n");
        return false;
    }
    if (id_field == NULL || strlen(id_field) == 0) {
        fprintf(stderr, "ID field name cannot be empty.\n");
        return false;
    }
    if (id_value == NULL || strlen(id_value) == 0) {
        fprintf(stderr, "ID value cannot be empty.\n");
        return false;
    }
    if (strlen(table) >= 64 || strlen(field) >= 64 || strlen(newValue) >= 256 || strlen(id_field) >= 64 || strlen(id_value) >= 256) {
        fprintf(stderr, "Input parameter is too long.\n");
        return false;
    }

    // Prepare buffers for escaped values
    char query[512];
    char escapedTable[64];
    char escapedField[64];
    char escapedValue[256];
    char escapedIdField[64];
    char escapedIdValue[256];

    // Escape input strings
    mysql_real_escape_string(conn, escapedTable, table, strlen(table));
    mysql_real_escape_string(conn, escapedField, field, strlen(field));
    mysql_real_escape_string(conn, escapedValue, newValue, strlen(newValue));
    mysql_real_escape_string(conn, escapedIdField, id_field, strlen(id_field));
    mysql_real_escape_string(conn, escapedIdValue, id_value, strlen(id_value));

    // Construct and execute the update query
    snprintf(query, sizeof(query), "UPDATE `%s` SET `%s` = '%s' WHERE `%s` = '%s'",
             escapedTable, escapedField, escapedValue, escapedIdField, escapedIdValue);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Update query failed: %s\n", mysql_error(conn));
        return false;
    }

    return true;
}