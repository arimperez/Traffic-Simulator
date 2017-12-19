#ifndef CAR_H
#define CAR_H

/* Structure to store car data through an intersection */
typedef struct Car {
    char from;
    char going;
    int timeArrived;

} Car;

/**
 * Create Car struct for traffic simulation
 * @param char from
 * @param char going
 * @param int arrivalTime
 * @Return Car struct pointer
 */

Car * createCar (char from, char going, int arrivalTime);

/**
 * Return directions car came from
 * @param Car * c
 * @Return char fromDirection
 */

char getFromDirec (Car * c);

/**
 * Return directions car is going to go
 * @param Car * c
 * @Return char goingDirection
 */

char getGoingDirec (Car * c);

/**
 * Print car data
 * @param void *c (Car struct)
 * @Return None
 */

void printCar (void *c);

/**
 * Delete car struct
 * @param Void *c (Car struct)
 * @Return None
 */

void deleteCar (void *c);

/**
 * Return cars arrival time
 * @param Car * c
 * @Return int arrivalTime
 */

int getArrival(Car * c);

/**
 * Determine if first is bigger the second
 * @param const void *first
 * @param const void *second
 * @Return int difference between first and second element
 */


int compareCar(const void *first,const void *second);



#endif
