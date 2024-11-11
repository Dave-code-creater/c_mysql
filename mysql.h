#ifndef MYSQL_H
#define MYSQL_H

#include <stdbool.h>
#include "mysql"


void displayAllFromTable(MYSQL* conn, const char *table);
void finishWithError(MYSQL *con);
bool addRecordIntoTable(MYSQL *conn, const char *value, const char *table, const char *field);
bool deleteTask(MYSQL *conn, const char *table);
bool updateTaskInTable(MYSQL *conn, const char *table, const char *field, const char *newValue, const char *id_field, const char *id_value);

#endif