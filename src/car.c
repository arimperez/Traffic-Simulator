#include "Car.h"
#include <stdio.h>
#include <stdlib.h>



Car * createCar (char from, char going, int timeArrived)
{
    Car *c = malloc(sizeof(Car));
    c->from = from;
    c->going = going;
    c->timeArrived = timeArrived;

    //printf("Creating: %c %c %d", c->from, c->going, c->timeArrived);

    return c;
}

char getFromDirec (Car * c)
{
    return (c->from);
}

char getGoingDirec (Car * c)
{
    return (c->going);
}

int getArrival(Car * c)
{
    return (c->timeArrived);
}

void printCar (void *c)
{

    //printf("~~~~~%d\n", a->timeArrived);
    //printf(":::::%c\n",getGoingDirec(c));
    printf("%c %c %d", getFromDirec(c), getGoingDirec(c), getArrival(c));
}

void deleteCar(void *c)
{
    free(c);
}

int compareCar(const void *first,const void *second)
{

    Car *a = (Car *)first;
    Car *b = (Car *)second;
    return (getArrival(a) - getArrival(b));

}
