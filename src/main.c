#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Car.h"
#include "LinkedListApi.h"

int main (int argc, char **argv)
{
    int traffic = 0;
    float seconds = 1;
    int numCars = 0;
    float beforeGreen = 0;
    int index = 0;
    char temp[10];

    char data[3][4];
    char direc[3];
    char going[3];
    int arrive = 0;

    List *north = initializeList(printCar, deleteCar, compareCar);
    List *east = initializeList(printCar, deleteCar, compareCar);
    List *south = initializeList(printCar, deleteCar, compareCar);
    List *west = initializeList(printCar, deleteCar, compareCar);

    List * allCars[4] = {north, east, south, west};


    FILE *userFile = fopen(argv[1], "r");

    //If no file is given
    if (argv[1] == NULL) {
        printf("ERROR! No file given!\n");
        return 0;
    }


    while (fgets(temp, 10, userFile)) {
        sscanf(temp, "%s %s %d", direc, going, &arrive);
        numCars++;


        if (direc[0] == 'N')
        {
            Car *newCar = createCar(direc[0], going[0], arrive);
            insertSorted(north, newCar);
        }

        else if (direc[0] == 'E') {
            Car *newCar = createCar(direc[0], going[0], arrive);
            insertSorted(east, newCar);
        }

        else if (direc[0] == 'S') {
            Car *newCar = createCar(direc[0], going[0], arrive);
            insertSorted(south, newCar);
        }

        else if (direc[0] == 'W') {
            Car *newCar = createCar(direc[0], going[0], arrive);
            insertSorted(west, newCar);
        }


        memset(temp, 0, 10);
        memset(data,0, 2);
    }

    fclose(userFile);




  //**Go through all the cars, stop when there are none left*/
    printf("Initial Vehicle Information  Intersection Arrival Time  Completed Time\n");
    Node * front;
    while (traffic < numCars) {
        beforeGreen = seconds;
        front = getFromFront(allCars[index]); //Node *

        int check = 0;
        int nodeDeleted;
        while (seconds <= beforeGreen + (float)14) {
          //printf("Time: %f\n", seconds);
            nodeDeleted = 1;
            if (allCars[index]->head == NULL) {
                seconds += 1;
            }

            else {
                if (getArrival(front->data) <= seconds) {
                    if (getGoingDirec(front->data) == 'F') {
                        check = seconds + 2;
                      //If there is still time
                        if (check <= beforeGreen + 10) {
                          //Add seconds it takes to move
                            seconds += 2;
                            printCar(front->data);
                            printf("%25d %35.1f\n",  getArrival(front->data), seconds);
                            nodeDeleted = deleteNodeFromList(allCars[index], front->data);
                          //free(front);
                            traffic++;
                          //printForward(allCars[index]);
                        }
                    }

                    else if (getGoingDirec(front->data) == 'R') {
                        check = seconds + 1;
                        //If there is still time
                        if (check <= beforeGreen + 10) {
                          //Add seconds it takes to move
                            seconds += 1.0;
                            printCar(front->data);
                            printf("%25d %35.1f\n",  getArrival(front->data), seconds);
                            //Remove car
                            nodeDeleted = deleteNodeFromList(allCars[index], front->data);

                            traffic++;
                        }
                    }
                    else if (getGoingDirec(front->data) == 'L') {
                        check = seconds + 2.5;
                      //Turning left on yellow is okay, so check if its +13 rather then +10
                        if (check <= beforeGreen + 13) {
                          //Add seconds it takes to move
                            seconds += 2.5;
                            printCar(front->data);
                            printf("%25d %35.1f\n",  getArrival(front->data), seconds);
                          //Remove car
                            nodeDeleted = deleteNodeFromList(allCars[index], front->data);
                          //nodeDeleted = 1;
                            traffic++;
                        }
                    }

                  //If car isn't moving increment time by one.
                    if (nodeDeleted == EXIT_FAILURE) {
                        seconds+=1.0;
                    }

                  //If a car moved, add to number of cars moved
                  //else {
                     // traffic++;
                  //}

                    front = getFromFront(allCars[index]);
                }
                else {
                    seconds += 1.0;
                }
            }


        }
        seconds = beforeGreen + 14.0;
        index++;
        if (index > 3) {
            index = 0;
        }

    }



    //Increment seconds
    //seconds++;




    deleteList(north);
    deleteList(east);
    deleteList(south);
    deleteList(west);

  //free(north->head);
  //free(north->tail);

  //free(north);
  //free(south);
  //free(east);
  //free(west);


  //deleteCar(newCar);


    return 0;

}
