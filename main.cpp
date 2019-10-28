//
//  main.cpp
//  Dining philosophers problem solved with Windows API
//
//  Created by Yagunov Pavel on 20/10/2019.
//  Copyright © 2019 Yagunov Pavel. All rights reserved.
//

#include <cstdio>
#include <windows.h>
#include <unistd.h>


#define PHIL_AMOUNT 5
//Объявление вилок
bool fork0isInUse = false;
bool fork1isInUse = false;
bool fork2isInUse = false;
bool fork3isInUse = false;
bool fork4isInUse = false;
int phNames[] = {1, 2, 3, 4, 5};

//Объявление критических секций
CRITICAL_SECTION csF0;
CRITICAL_SECTION csF1;
CRITICAL_SECTION csF2;
CRITICAL_SECTION csF3;
CRITICAL_SECTION csF4;
CRITICAL_SECTION csoutput;


DWORD WINAPI eat(LPVOID params); //функции потока

int main(int argc, char *argv[]) {
    HANDLE threads[PHIL_AMOUNT];


    //Инициализируем критическую секцию
    InitializeCriticalSection(&csF0);
    InitializeCriticalSection(&csF1);
    InitializeCriticalSection(&csF2);
    InitializeCriticalSection(&csF3);
    InitializeCriticalSection(&csF4);
    InitializeCriticalSection(&csoutput);
    printf("The start of the dinner.\n");
    //Запустим 5 потоков
    for (int i = 0; i < 5; ++i) {
        threads[i] = CreateThread(nullptr, 0, eat, &phNames[i], 0, nullptr);
    }
    WaitForMultipleObjects(PHIL_AMOUNT, threads, true, 1000000);


    //Удаляем критическую секцию
    DeleteCriticalSection(&csF0);
    DeleteCriticalSection(&csF1);
    DeleteCriticalSection(&csF2);
    DeleteCriticalSection(&csF3);
    DeleteCriticalSection(&csF4);
    DeleteCriticalSection(&csoutput);

    for (int i = 0; i < PHIL_AMOUNT; i++) {
        CloseHandle(&threads[i]);
    }

    return 0;
}

DWORD WINAPI eat(LPVOID params) {
    int *name_ptr = (int *) params;
    int phil = *name_ptr;

    while (true) {
        if (phil == 1) {
            EnterCriticalSection(&csF0);
            if (!fork0isInUse) {
                fork0isInUse = true;
                LeaveCriticalSection(&csF0);
                EnterCriticalSection(&csF1);
                if (!fork1isInUse) {
                    fork1isInUse = true;
                    EnterCriticalSection(&csoutput);
                    printf("Philosopher #%d is eating:\n", phil);
                    LeaveCriticalSection(&csoutput);
                    LeaveCriticalSection(&csF1);
                    sleep(1);
                    EnterCriticalSection(&csF1);
                    fork1isInUse = false;
                    LeaveCriticalSection(&csF1);
                    EnterCriticalSection(&csF0);
                    fork0isInUse = false;
                    EnterCriticalSection(&csoutput);
                    printf("Philosopher #%d is thinking:\n", phil);
                    LeaveCriticalSection(&csoutput);
                    LeaveCriticalSection(&csF0);

                    sleep(1);
                } else {
                    LeaveCriticalSection(&csF1);
                    EnterCriticalSection(&csF0);
                    fork0isInUse = false;
                    LeaveCriticalSection(&csF0);
                }
            } else {
                LeaveCriticalSection(&csF0);
            }
        }
        if (phil == 2) {
            EnterCriticalSection(&csF1);
            if (!fork1isInUse) {
                fork1isInUse = true;
                LeaveCriticalSection(&csF1);
                EnterCriticalSection(&csF2);
                if (!fork2isInUse) {
                    fork2isInUse = true;
                    EnterCriticalSection(&csoutput);
                    printf("Philosopher #%d is eating:\n", phil);
                    LeaveCriticalSection(&csoutput);
                    LeaveCriticalSection(&csF2);

                    sleep(1);
                    EnterCriticalSection(&csF2);
                    fork2isInUse = false;
                    LeaveCriticalSection(&csF2);
                    EnterCriticalSection(&csF1);
                    fork1isInUse = false;
                    EnterCriticalSection(&csoutput);
                    printf("Philosopher #%d is thinking:\n", phil);
                    LeaveCriticalSection(&csoutput);
                    LeaveCriticalSection(&csF1);

                    sleep(1);
                } else {
                    LeaveCriticalSection(&csF2);
                    EnterCriticalSection(&csF1);
                    fork1isInUse = false;
                    LeaveCriticalSection(&csF1);
                }
            } else {
                LeaveCriticalSection(&csF1);
            }
        }
        if (phil == 3) {
            EnterCriticalSection(&csF2);
            if (!fork2isInUse) {
                fork2isInUse = true;
                LeaveCriticalSection(&csF2);
                EnterCriticalSection(&csF3);
                if (!fork3isInUse) {
                    fork3isInUse = true;
                    EnterCriticalSection(&csoutput);
                    printf("Philosopher #%d is eating:\n", phil);
                    LeaveCriticalSection(&csoutput);
                    LeaveCriticalSection(&csF3);

                    sleep(1);
                    EnterCriticalSection(&csF3);
                    fork3isInUse = false;
                    LeaveCriticalSection(&csF3);
                    EnterCriticalSection(&csF2);
                    fork2isInUse = false;
                    EnterCriticalSection(&csoutput);
                    printf("Philosopher #%d is thinking:\n", phil);
                    LeaveCriticalSection(&csoutput);
                    LeaveCriticalSection(&csF2);

                    sleep(1);
                } else {
                    LeaveCriticalSection(&csF3);
                    EnterCriticalSection(&csF2);
                    fork2isInUse = false;
                    LeaveCriticalSection(&csF2);
                }
            } else {
                LeaveCriticalSection(&csF2);
            }
        }
        if (phil == 4) {
            EnterCriticalSection(&csF3);
            if (!fork3isInUse) {
                fork3isInUse = true;
                LeaveCriticalSection(&csF3);
                EnterCriticalSection(&csF4);
                if (!fork4isInUse) {
                    fork4isInUse = true;
                    EnterCriticalSection(&csoutput);
                    printf("Philosopher #%d is eating:\n", phil);
                    LeaveCriticalSection(&csoutput);
                    LeaveCriticalSection(&csF4);

                    sleep(1);
                    EnterCriticalSection(&csF4);
                    fork4isInUse = false;
                    LeaveCriticalSection(&csF4);
                    EnterCriticalSection(&csF3);
                    fork3isInUse = false;
                    EnterCriticalSection(&csoutput);
                    printf("Philosopher #%d is thinking:\n", phil);
                    LeaveCriticalSection(&csoutput);
                    LeaveCriticalSection(&csF3);

                    sleep(1);
                } else {
                    LeaveCriticalSection(&csF4);
                    EnterCriticalSection(&csF3);
                    fork3isInUse = false;
                    LeaveCriticalSection(&csF3);
                }
            } else {
                LeaveCriticalSection(&csF3);
            }
        }
        if (phil == 5) {
            EnterCriticalSection(&csF4);
            if (!fork4isInUse) {
                fork4isInUse = true;
                LeaveCriticalSection(&csF4);
                EnterCriticalSection(&csF0);
                if (!fork0isInUse) {
                    fork0isInUse = true;
                    EnterCriticalSection(&csoutput);
                    printf("Philosopher #%d is eating:\n", phil);
                    LeaveCriticalSection(&csoutput);
                    LeaveCriticalSection(&csF0);

                    sleep(1);
                    EnterCriticalSection(&csF0);
                    fork0isInUse = false;
                    LeaveCriticalSection(&csF0);
                    EnterCriticalSection(&csF4);
                    fork4isInUse = false;
                    EnterCriticalSection(&csoutput);
                    printf("Philosopher #%d is thinking:\n", phil);
                    LeaveCriticalSection(&csoutput);
                    LeaveCriticalSection(&csF4);

                    sleep(1);
                } else {
                    LeaveCriticalSection(&csF0);
                    EnterCriticalSection(&csF4);
                    fork4isInUse = false;
                    LeaveCriticalSection(&csF4);
                }
            } else {
                LeaveCriticalSection(&csF4);
            }
        }
    }
}