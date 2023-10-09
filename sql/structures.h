#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
    long id;
    char name[50];
    char family[50];
    char user_id[50];
    char national_id[50];
    char gender[50];
    int birthdate_year;
    int birthdate_month;
    int birthdate_day;
    int approved;
    int masol;
    int money_balance;
    char password[50];
} user;

typedef struct {
    int id;
    char name[50];
    char address[50];
    char self_id[50];
    int capacity;
    char lunch_time[50];
    char dinner_time[50];
    int girlish;
} self;

typedef struct {
    int id;
    char name[50];
    char food_id[50];
    int cost;    
    int desert;
} food;

#endif //STRUCTURES_H
