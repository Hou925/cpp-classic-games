#pragma once
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <windows.h>

void choose(int select);
void set_matrix(int xmax, int ymax, int mat[10][10]);
void print_matrix(int mat[10][10], int xmax, int ymax);
void print_result_matrix(char mat0[10][10], int xmax, int ymax);
void print_colored_matrix(int mat[10][10], char mat0[10][10], int xmax, int ymax);
int find_same(int mat[10][10], int cx, int cy, int sign, int xmax, int ymax, char mat0[10][10]);
void choose(int select);
char que_clear(int cx, int cy);
void clear_matrix(int mat[10][10], int xmax, int ymax, char mat0[10][10]);
void print_cleared_matrix(int mat[10][10], char mat0[10][10], int xmax, int ymax);
void scoring(int &score, int xmax, int ymax, char mat0[10][10],int tag0);
void ending();
void pause();
void fall_matrix(int mat[10][10], int xmax, int ymax,int tag);
int judge_gameover(int mat[10][10], int xmax, int ymax);
void final_scoring(int& score, int xmax, int ymax, int mat[10][10]);
void gameover(int mat[10][10], int xmax, int ymax,int tag);
void print_one_block(int number, int x, int y,int color);
void print_initial_mat(int mat[10][10], int xmax, int ymax);
void print_background(int xmax, int ymax);
void print_initial_border_mat(int mat[10][10], int xmax, int ymax);
void print_background_border(int xmax, int ymax);
void input(int& xmax, int& ymax);
void select_4(int mat[10][10], int &xmax, int &ymax);
void select_5(int mat[10][10], int &xmax, int &ymax);
void select_6(int mat[10][10], char mat0[10][10], int& xmax, int& ymax, int& score);
void select_7(int mat[10][10], char mat0[10][10], int& xmax, int& ymax, int& score);
void falling_blocks(int mat[10][10], int xmax, int ymax, int tag);