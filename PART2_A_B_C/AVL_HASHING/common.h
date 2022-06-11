#ifndef COMMON_H
#define COMMON_H

typedef struct date
{
    int month;
    int day;
    int year;

}date;

typedef struct measurements{ //struct with floats and string only for the date

    char date[50];
    float temp, phosphate;
    float silicate,  nitrite, nitrate;
    float salinity,  oxygen;

}measurements;



#endif  COMMON_H
