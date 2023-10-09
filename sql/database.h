#ifndef DATABASE_H
#define DATABASE_H

#include "structures.h"

void make_or_open_database();
void close_database();
void insert_user(user *);
void update_user(int, user *);
user * get_user(const char *);
void delete_user(user *);
user *get_notapproved();
void insert_self(self *);
self *get_self(const char *);
void insert_food(food *);
food *get_food(const char *);

#endif //DATABASE_H
