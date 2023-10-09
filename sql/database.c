#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "sqlite3.h"
#include "database.h"


const char DATABASE_FILE_NAME[] = "project_sqlite.db";
sqlite3 *db = NULL;

void make_user_table() {
    char *sql = "CREATE TABLE USERS("  \
      "ID INTEGER PRIMARY KEY     NOT NULL," \
      "NAME           CHAR(50)    NOT NULL," \
      "FAMILY         CHAR(50)    NOT NULL," \
      "USER_ID        CHAR(50)    NOT NULL," \
      "NATIONAL_ID    CHAR(50)    NOT NULL," \
      "GENDER         CHAR(50)     NOT NULL," \
      "BIRTHDATE_Y    INT         NOT NULL," \
      "BIRTHDATE_M    INT         NOT NULL," \
      "BIRTHDATE_D    INT         NOT NULL," \
      "APPROVED       INT         NOT NULL," \
      "MASOL          INT         NOT NULL," \
      "MONEY_BALANCE  INT         NOT NULL," \
      "PASSWORD       CHAR(50)    NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    sql = "CREATE UNIQUE INDEX unique_user_id ON USERS (USER_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    fprintf(stdout, "USERS Table created successfully\n");
}

void make_self_table() {
    fprintf(stdout, "Making self table\n");
    char *sql = "CREATE TABLE SELF("  \
      "ID INTEGER PRIMARY KEY     NOT NULL," \
      "NAME           CHAR(50)    NOT NULL," \
      "ADDRESS        CHAR(50)    NOT NULL," \
      "SELF_ID        CHAR(50)    NOT NULL," \
      "LUNCH_TIME     CHAR(50)    NOT NULL," \
      "DINNER_TIME    CHAR(50)    NOT NULL," \
      "GIRLISH        INT         NOT NULL," \
      "CAPACITY       INT         NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    sql = "CREATE UNIQUE INDEX unique_self_id ON SELF (SELF_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    fprintf(stdout, "SELF Table created successfully\n");
}

void make_food_table() {
    fprintf(stdout, "Making food table\n");
    char *sql = "CREATE TABLE FOOD("  \
      "ID INTEGER PRIMARY KEY     NOT NULL," \
      "NAME           CHAR(50)    NOT NULL," \
      "FOOD_ID        CHAR(50)    NOT NULL," \
      "COST           INT         NOT NULL," \
      "DESERT         INT         NOT NULL);";

    /* Execute SQL statement */
    char *db_error_message = NULL;
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }

    sql = "CREATE UNIQUE INDEX unique_food_id ON FOOD (FOOD_ID);";
    rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        exit(1);
    }
    fprintf(stdout, "FOOD Table created successfully\n");
}

void make_tables() {
    make_user_table();
    make_self_table();
    make_food_table();
}

void update_user(int id_of_user, user *new_user) {
    char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "UPDATE USERS SET NAME = '%s', FAMILY = '%s', USER_ID = '%s', NATIONAL_ID = '%s', GENDER = '%s', BIRTHDATE_Y = %d,"
                 "BIRTHDATE_M = %d, BIRTHDATE_D = %d, APPROVED = %d, MASOL = %d, MONEY_BALANCE = %d, PASSWORD = '%s' WHERE ID = %d;",
            new_user->name, new_user->family, new_user->user_id, new_user->national_id, new_user->gender, new_user->birthdate_year, 
            new_user->birthdate_month, new_user->birthdate_day, new_user->approved, new_user->masol, new_user->money_balance, new_user->password, id_of_user);

    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    fprintf(stdout, "User updated successfully\n");
}

void insert_user(user *new_user) {
    char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO USERS (NAME, FAMILY, USER_ID, NATIONAL_ID, GENDER,BIRTHDATE_Y,"
                 "BIRTHDATE_M, BIRTHDATE_D, APPROVED, MASOL, MONEY_BALANCE, PASSWORD) VALUES ('%s','%s','%s','%s','%s','%d','%d','%d','%d','%d','%d','%s');",
            new_user->name, new_user->family, new_user->user_id, new_user->national_id,
            new_user->gender, new_user->birthdate_year, new_user->birthdate_month,
            new_user->birthdate_day, new_user->approved, new_user->masol, new_user->money_balance, new_user->password);
    
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_user->id = sqlite3_last_insert_rowid(db);
    fprintf(stdout, "User created successfully\n");
}

void insert_self(self *new_self) {
    char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO SELF (NAME, ADDRESS, SELF_ID, LUNCH_TIME, DINNER_TIME, GIRLISH,"
                 "CAPACITY) VALUES ('%s','%s','%s','%s','%s','%d','%d');",
            new_self->name, new_self->address, new_self->self_id, new_self->lunch_time,
            new_self->dinner_time, new_self->girlish, new_self->capacity);
    
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_self->id = sqlite3_last_insert_rowid(db);
    fprintf(stdout, "Self created successfully\n");
}

void insert_food(food *new_food) {
    char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "INSERT INTO FOOD (NAME, FOOD_ID, COST, DESERT) VALUES ('%s','%s','%d', '%d');",
            new_food->name, new_food->food_id, new_food->cost, new_food->desert);
    
    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    new_food->id = sqlite3_last_insert_rowid(db);
    fprintf(stdout, "FOOD created successfully\n");
}

static int user_callback(void *data, int argc, char **argv, char **not_used) {
    if (argc != 13) {
        printf("Error in getting a user info from the database!");
        return 1;
    }
    user *fetched_user = (user *) data;
    char *ptr;
    fetched_user->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_user->name, argv[1]);
    strcpy(fetched_user->family, argv[2]);
    strcpy(fetched_user->user_id, argv[3]);
    strcpy(fetched_user->national_id, argv[4]);
    strcpy(fetched_user->gender, argv[5]);
    fetched_user->birthdate_year = (int)strtol(argv[6], &ptr, 10);
    fetched_user->birthdate_month = (int)strtol(argv[7], &ptr, 10);
    fetched_user->birthdate_day = (int)strtol(argv[8], &ptr, 10);
    fetched_user->approved = (int)strtol(argv[9], &ptr, 10);
    fetched_user->masol = (int)strtol(argv[10], &ptr, 10);
    fetched_user->money_balance = (int)strtol(argv[11], &ptr, 10);
    strcpy(fetched_user->password, argv[12]);

    return 0;
}

static int user_callback1(void *data, int argc, char **argv, char **not_used) {
    if (argc != 8) {
        printf("Error in getting a user info from the database!");
        return 1;
    }
    self *fetched_user = (self *) data;
    char *ptr;
    fetched_user->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_user->name, argv[1]);
    strcpy(fetched_user->address, argv[2]);
    strcpy(fetched_user->self_id, argv[3]);
    strcpy(fetched_user->lunch_time, argv[4]);
    strcpy(fetched_user->dinner_time, argv[5]);
    fetched_user->girlish = (int)strtol(argv[6], &ptr, 10);
    fetched_user->capacity = (int)strtol(argv[7], &ptr, 10);
    return 0;
}

static int user_callback2(void *data, int argc, char **argv, char **not_used) {
    if (argc != 5) {
        printf("Error in getting a user info from the database!");
        return 1;
    }
    food *fetched_user = (food *) data;
    char *ptr;
    fetched_user->id = strtol(argv[0], &ptr, 10);
    strcpy(fetched_user->name, argv[1]);
    strcpy(fetched_user->food_id, argv[2]);
    fetched_user->cost = (int)strtol(argv[3], &ptr, 10);
    fetched_user->desert = (int)strtol(argv[4], &ptr, 10);
    return 0;
}

user *get_user(const char *user_id) {
    user *fetched_user = (user *) malloc(sizeof(user));
    if (fetched_user == NULL) {
        printf("Error: Cannot allocate memory for a new user!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM USERS WHERE USER_ID = '%s';", user_id);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_user->id = -1;
    int rc = sqlite3_exec(db, sql, user_callback, (void *) fetched_user, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    // fprintf(stdout, "Operation done successfully\n");
    if (fetched_user->id == -1) {
        free(fetched_user);
        return NULL;
    }
    return fetched_user;
}

self *get_self(const char *self_id) {
    self *fetched_user = (self *) malloc(sizeof(self));
    if (fetched_user == NULL) {
        printf("Error: Cannot allocate memory for a new user!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM SELF WHERE SELF_ID = '%s';", self_id);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_user->id = -1;
    int rc = sqlite3_exec(db, sql, user_callback1, (void *) fetched_user, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    // fprintf(stdout, "Operation done successfully\n");
    if (fetched_user->id == -1) {
        free(fetched_user);
        return NULL;
    }
    return fetched_user;
}

food *get_food(const char *food_id) {
    food *fetched_user = (food *) malloc(sizeof(food));
    if (fetched_user == NULL) {
        printf("Error: Cannot allocate memory for a new user!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM FOOD WHERE FOOD_ID = '%s';", food_id);

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_user->id = -1;
    int rc = sqlite3_exec(db, sql, user_callback2, (void *) fetched_user, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    // fprintf(stdout, "Operation done successfully\n");
    if (fetched_user->id == -1) {
        free(fetched_user);
        return NULL;
    }
    return fetched_user;
}

user *get_notapproved() {
    user *fetched_user = (user *) malloc(sizeof(user));
    if (fetched_user == NULL) {
        printf("Error: Cannot allocate memory for a new user!");
        return NULL;
    }
    char sql[100];
    sprintf(sql, "SELECT * FROM USERS WHERE APPROVED = '0';");

    /* Execute SQL statement */
    char *db_error_message = NULL;
    fetched_user->id = -1;
    int rc = sqlite3_exec(db, sql, user_callback, (void *) fetched_user, &db_error_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return NULL;
    }
    // fprintf(stdout, "Operation done successfully\n");
    if (fetched_user->id == -1) {
        free(fetched_user);
        return NULL;
    }
    return fetched_user;
}

void delete_user(user *new_user) {
    char sql[512];
    char *db_error_message = NULL;
    sprintf(sql, "DELETE FROM USERS WHERE ID = '%ld';", new_user->id);

    int rc = sqlite3_exec(db, sql, NULL, NULL, &db_error_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", db_error_message);
        sqlite3_free(db_error_message);
        return;
    }
    fprintf(stdout, "User deleted successfully\n");
}

void make_or_open_database() {
    // check if db-file exist from before
    FILE *db_file = fopen(DATABASE_FILE_NAME, "rb");
    bool db_was_exist = false;
    if (db_file != NULL) {
        db_was_exist = true;
        fclose(db_file);
    }
    if (sqlite3_open(DATABASE_FILE_NAME, &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    fprintf(stdout, "Opened database successfully\n");
    if (!db_was_exist) {
        make_tables();
    }
}

void close_database() {
    sqlite3_close(db);
}