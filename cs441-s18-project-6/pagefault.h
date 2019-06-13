/*
 * 
 *
 * CS 441/541: Page Fault Algorithm Simulator (Project 6)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/******************************
 * Defines
 ******************************/


/******************************
 * Structures
 ******************************/
struct page {
    int page_num;
    char access_type;//stores corresponding actions for pages (reads or writes)
    int ref_bit; //these bits will prolly be needed in the frame struct - not here
    int mod_bit;
}; typedef struct page page;

struct frame {
    int page_num;
    int used_again;
    int recently_used;
    int ref_bit; //these bits will prolly be needed in the frame struct - not here
    int mod_bit;
};
typedef struct frame frame;

/******************************
 * Global Variables
 ******************************/
int num_pages; //# of pages in the file
page* page_array; //stores each page number, access type, ref_bit and mod bit in an array
char** pages; //stores all of the page numbers as chars for building reference string

/******************************
 * Function declarations
 ******************************/
int reset_array(); //function to reset the page_array (or frames?) member vars to original values after each
//replacement algorithm runs?
/*
 * params:
 * **frames = the array of frames to initialize
 * num_frames = the number of frames to initialize in the array
 */
int init_frames(frame **frames, int num_Frames); //initialize the frames array to -1 in each

int read_File(FILE* fd); //returns -1 on failure

int optimal(int num_frames); //optimal

int fifo(int num_frames); //num_frames = the number of frames to use, use ALL if num_frames == 0

int lru(int num_frames); //least reacently used

int Lru_sc(int num_frames); //lru second chance

int Lru_esc(int num_frames); //lru second chance enhanced
