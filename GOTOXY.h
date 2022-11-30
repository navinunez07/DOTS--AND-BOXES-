//
// Created by nivan on 28/11/2022.
//

#ifndef PROYECTO_FINAL_LAB_DEFINITIVO_GOTOXY_H
#define PROYECTO_FINAL_LAB_DEFINITIVO_GOTOXY_H

#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
void gotoxy(int x,int y){
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon,dwPos);
}
#endif //PROYECTO_FINAL_LAB_DEFINITIVO_GOTOXY_H
