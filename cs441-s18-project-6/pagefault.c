/*
 * 
 *
 * CS 441/541: Page Fault Algorithm Simulator (Project 6)
 */
#include "pagefault.h"


int main(int argc, char **argv) {
    
    int read_rtn; //value returned by readFile function
    FILE *fd = NULL; //file pointer
    char* temp_arg;
    int i;
    char* file_name; //name of file to read
    int num_frames = 0; //number of frames, if 0 then use ALL
    pages = NULL; //global
    page_array = NULL;
    num_pages = 0;
    int replacement_rtn = 0; //value to catch from replacement algs- error checking
    /*
     * integer arrays for storing the number of page faults returned by each algorithm
     */
    int* num_opt_faults = NULL;
    int* num_fifo_faults = NULL;
    int* num_lru_faults = NULL;
    int* num_lru2nd_faults = NULL;
    int* num_lru2nd_enhanced_faults = NULL;

    //parse commandline
    for(i = 1; i < argc; i++) {
        temp_arg = strdup(argv[i]);
        if(strcmp(temp_arg, "-f") == 0) { //read a -f so next thing to read is the # frames
            ++i;
            if(i < argc) { //check to make sure there was a number after the
                num_frames = atoi(argv[i]);
                if (num_frames > 7 || num_frames < 1) { //make sure the number supplies was between 1&7
                    printf("Error: Must supply an integer argument between 1 and 7 for the -f option\n");
                    exit(-1);
                }
            } else { //no number supplied
                printf("Error: Must supply an integer argument between 1 and 7 for the -f option\n");
            }
        } else {
            file_name = temp_arg;
        }
    }
    
    //allocate space for pointers to store the number of faults returned by the methods
    if(num_frames == 0) { //use ALL frames
        printf("Num. Frames : All\n");
        num_opt_faults = (int*)malloc(sizeof(int)*7); //create an array of 7
        num_fifo_faults = (int*)malloc(sizeof(int)*7);;
        num_lru_faults = (int*)malloc(sizeof(int)*7);;
        num_lru2nd_faults = (int*)malloc(sizeof(int)*7);;
        num_lru2nd_enhanced_faults = (int*)malloc(sizeof(int)*7);
    } else {
        printf("Num. Frames :  %d\n", num_frames);
        num_opt_faults = (int*)malloc(sizeof(int)*1); //create an array of 7
        num_fifo_faults = (int*)malloc(sizeof(int)*1);;
        num_lru_faults = (int*)malloc(sizeof(int)*1);;
        num_lru2nd_faults = (int*)malloc(sizeof(int)*1);;
        num_lru2nd_enhanced_faults = (int*)malloc(sizeof(int)*1);
    }
    //formatting
    printf("Ref. File   : %s\n", file_name);
    printf("-------------------------------\n");
    printf("Reference String: \n");
    fd = fopen(file_name, "r");
    read_rtn = read_File(fd);
    if(read_rtn == -1) {
        //file read failed... exit?
    }
    printf("-------------------------------\n");

    printf("####################################################\n");
    printf("#     Frames     Opt.    FIFO    LRU      SC     ESC\n");
    //decide how to print the number of faults
    if(num_frames != 0) { //selected a single # of frames to use
        replacement_rtn = optimal(num_frames);
        if(replacement_rtn != -1) { //algorithm did not fail
            num_opt_faults[0] = replacement_rtn;
            //printf("page faults was: %d\n", num_opt_faults[0]);
        } else {
            printf("ERROR in one of the algorithms and exiting program!\n");
            exit(-1);
        }
        replacement_rtn = fifo(num_frames);
        if(replacement_rtn != -1) { //algorithm did not fail
            num_fifo_faults[0] = replacement_rtn;
            //printf("page faults was: %d\n", *num_fifo_faults);
        } else {
            printf("ERROR in one of the algorithms and exiting program!\n");
            exit(-1);
        }
        replacement_rtn = lru(num_frames);
        if(replacement_rtn != -1) { //algorithm did not fail
            num_lru_faults[0] = replacement_rtn;
            //printf("page faults was: %d\n", *num_fifo_faults);
        } else {
            printf("ERROR in one of the algorithms and exiting program!\n");
            exit(-1);
        }
        replacement_rtn = Lru_sc(num_frames);
        if(replacement_rtn != -1) { //algorithm did not fail
            num_lru2nd_faults[0] = replacement_rtn;
            //printf("page faults was: %d\n", *num_fifo_faults);
        } else {
            printf("ERROR in one of the algorithms and exiting program!\n");
            exit(-1);
        }
        replacement_rtn = Lru_esc(num_frames);
        if(replacement_rtn != -1) { //algorithm did not fail
            num_lru2nd_enhanced_faults[0] = replacement_rtn;
            //printf("page faults was: %d\n", *num_fifo_faults);
        } else {
            printf("ERROR in one of the algorithms and exiting program!\n");
            exit(-1);
        }
        printf("#\t %3d \t %4d \t %4d \t%4d\t%4d \t%4d\n",num_frames, num_opt_faults[0],
               *num_fifo_faults, *num_lru_faults, *num_lru2nd_faults, *num_lru2nd_enhanced_faults);
    } else { //need to use ALL frames... call methods in a loop and store the
        //number of page faults (returned from function?) for each in an array
        
        for( i = 1; i < 8; i++) {
            replacement_rtn = optimal(i);
            
            if(replacement_rtn != -1) {
                num_opt_faults[i] = replacement_rtn;
            }
            //printf("opt return is %d\n", num_opt_faults[i]);
            replacement_rtn = fifo(i);
            if(replacement_rtn != -1) {
                num_fifo_faults[i] = replacement_rtn;
            }
            replacement_rtn = lru(i);
            if(replacement_rtn != -1) {
                num_lru_faults[i] = replacement_rtn;
            }
            replacement_rtn = Lru_sc(i);
            if(replacement_rtn != -1) {
                num_lru2nd_faults[i] = replacement_rtn;
            }
            replacement_rtn = Lru_esc(i);
            if(replacement_rtn != -1) {
                num_lru2nd_enhanced_faults[i] = replacement_rtn;
            }
            printf("#\t %3d \t %4d \t %4d \t%4d\t%4d \t%4d\n",i, num_opt_faults[i],
                   num_fifo_faults[i], num_lru_faults[i], num_lru2nd_faults[i], num_lru2nd_enhanced_faults[i]);
        }//end of for loop
    }
    printf("####################################################\n");
    //free memory
    if(temp_arg != NULL) {
        temp_arg = NULL;
        free(temp_arg);
    }
    if (file_name != NULL) {
        file_name = NULL;
        free(file_name);
    }
    if (num_opt_faults != NULL) {
        num_opt_faults = NULL;
        free(num_opt_faults);
    }
    if(num_fifo_faults != NULL) {
        num_fifo_faults =NULL;
        free(num_fifo_faults);
    }
    if (num_lru_faults != NULL) {
        num_lru_faults = NULL;
        free(num_lru_faults);
    }
    if(num_lru2nd_faults != NULL) {
        num_lru2nd_faults = NULL;
        free(num_lru2nd_faults);
    }
    if (num_lru2nd_enhanced_faults != NULL) {
        num_lru2nd_enhanced_faults = NULL;
        free(num_lru2nd_enhanced_faults);
    }
    fclose(fd);
    fflush(NULL);
    return 0;
}

int optimal(int num_frames){ //should be done.. check corner cases?
    int num_page_faults = 0;
    int i;
    int j;
    frame* frames = (frame*)malloc(sizeof(frame)*num_frames); //array for storing the pages in
    //theframes
    init_frames(&frames, num_frames); //initialize the frames array
    int cur_page; //integer value of the current page
    int frames_checked; //checking for future replacement
    //only ever goes to up (num_frames-1) so there is always one frame with
    //used_again variable set to false for the one being replaced
    int k;
    int f;
    int replaced_a_page;
    for(i = 0; i < num_pages; i++) { //loop thru pages
        cur_page = page_array[i].page_num;
        j = 0;
        frames_checked = 0;
        replaced_a_page = 0; //set to false initially
        while (j < num_frames) { //loop thru frames
            
            if (frames[j].page_num == -1) { //not filled frame
                //printf("page fault due to an empty page when adding %d\n", cur_page);
                num_page_faults++;
                frames[j].page_num = cur_page;
                j = num_frames; //force break out of loop
            } else if (frames[j].page_num == cur_page) { //found the page in a frame
                //break; //?
                frames[j].ref_bit = 1;
                j = num_frames; //force break out of loop
            } else if (j == num_frames-1) { //replace a page -- page fault
                //did not find an empty place & searched thru all frames
                //printf("page fault while looking at %d\n", cur_page);
                num_page_faults++;
                k = i + 1; //position to cycle thru pages remaining
                /*
                 * go thru the rest of the pages to find which page to replace
                 */
                while(k < num_pages && frames_checked < num_frames-1) { //another method?
                    /*
                     * check the frames to see if remaining pages are in a frame
                     * go until you have 1 frame left that is not used in the future
                     * and while there are still frames to check
                     */
                    f = 0; //position to cycle thru frames
                    //cycle thru frames
                    while(f < num_frames) {
                        if(page_array[k].page_num == frames[f].page_num
                           && frames[f].used_again == 0) {
                            //found a future page in a frame
                            frames[f].used_again = 1;
                            frames_checked++;
                            f = num_frames;//stop searching the frames
                        }
                        f++;

                    } //end inner while
                   k++;
                }//end outer while
                for(k = 0; k < num_frames; k++) {
                    if(frames[k].used_again == 0 && replaced_a_page == 0) { //replace the correct frame and reset
                        //the used_again vars
                        frames[k].page_num = page_array[i].page_num;
                        replaced_a_page =1;
                    } else {
                        frames[k].used_again = 0;
                    }
                }
            }
            j++;
        } //end inner while
    }//end outer for
    if (frames != NULL) {
        frames = NULL;
        free(frames);
    }
    //printf("number of page faults is %d\n", num_page_faults);
    return num_page_faults;
}

//FIFO should be done
int fifo(int num_frames) {//num_frames = the number of frames to use, use ALL if num_frames == 0
    //counting vars
    int num_page_faults = 0;
    int cur_replace_pos=0;
    int i, j;
    //declare and initialize frames struct
    frame* frames = (frame*)malloc(sizeof(frame)*num_frames);
    init_frames(&frames, num_frames);
    int cur_page; //current page that we are looking at to put in a frame
    for(i = 0; i < num_pages; i++) {
        cur_page = page_array[i].page_num;
        j = 0;
        while( j < num_frames) { //search frames
            if(frames[j].page_num == -1) { //nothing here yet
                num_page_faults++;
                frames[cur_replace_pos].page_num = cur_page;
                j = num_frames;
                cur_replace_pos++;
            } else if (frames[j].page_num == cur_page) { //found it in a frame
                frames[j].ref_bit = 1;
                j = num_frames; //break out of loop and look at next page
            } else if (j == num_frames-1) { //searched all frames and did not find
                num_page_faults++;
                frames[cur_replace_pos].page_num = cur_page;
                cur_replace_pos++;
            }
            j++;
        } //end of while loop
        if (cur_replace_pos >= num_frames) { //reset the position to replace to first frame
            cur_replace_pos = 0;
        }
    }//end of outer for loop
    if (frames != NULL) {
        frames = NULL;
        free(frames);
    }
    return num_page_faults;
}

int lru(int num_frames){ //finished
    int num_page_faults = 0;
    int cur_page_pos; //position to start searching in the page_array (backwards on page fault)
    frame* frames = (frame*)malloc(sizeof(frame)*num_frames);
    init_frames(&frames, num_frames);
    int i, j, k;
    int cur_page, temp_page;
    int num_recently_used; //how many pages were found in frames
    
    for( i = 0; i < num_pages; i++) {
        cur_page = page_array[i].page_num;
        cur_page_pos = i; //position in page_array to start searching backwards
        j = 0;
        num_recently_used = 0;
        while( j < num_frames) {
            if(frames[j].page_num == -1) { //nothing here yet
                num_page_faults++;
                frames[j].page_num = cur_page;
                frames[j].ref_bit = 1; //modify the reference bit to 1
                j = num_frames;
            } else if (frames[j].page_num == cur_page) { //found it in a frame
                frames[j].ref_bit = 1;
                j = num_frames; //break out of loop and look at next page
            } else if (j == num_frames-1) { //searched all frames and did not find the page
                num_page_faults++;
                k = 0; //search thru the frames to see if a matching page was previously
                //found
                while(cur_page_pos >= 0 && num_recently_used < num_frames-1) { //search backwards
                    //thru page array to find lru position
                    temp_page = page_array[cur_page_pos].page_num; //page number in the
                    //page array that is being looked at to match in a frame
                    for(k = 0; k < num_frames; k++) { //search thru frames till you find
                        //a frame that matches the page num
                        if(frames[k].page_num == temp_page
                           && frames[k].recently_used == 0) { //found a frame that
                            //was recently used and not yet marked
                            frames[k].recently_used = 1;
                            num_recently_used++;
                            k = num_frames; //break out of loop
                        }
                    }
                    cur_page_pos--;
                }
                for( k = 0; k < num_frames; k++) { //replace the page and reset frame vars
                    if (frames[k].recently_used == 0) { //found the one not recently used
                        frames[k].page_num = cur_page; //replace the page and reset vars
                    } else { //reset the other frames vars
                        frames[k].recently_used = 0;
                    }
                }
            } //end of page fault conditional
            j++;
        }
    }
    if (frames != NULL) {
        frames = NULL;
        free(frames);
    }
    return num_page_faults;
}

int Lru_sc(int num_frames) { //finished
    int num_page_faults = 0;
    int i, j, k;
    int cur_page; //page # of the current page looking at to put in a frame
    frame* frames = (frame*)malloc(sizeof(frame)*num_frames);
    init_frames(&frames, num_frames);
    int cur_replace_pos=0; //the position to start looking at in the frame array
    //for the frame that is to be replaced
    int replaced_a_page = 0; //set to false;
    for( i = 0; i < num_pages; i ++) { //search thru page array
        cur_page = page_array[i].page_num;
        j = 0;
        replaced_a_page = 0; //set to false;
        while( j < num_frames){ //search thru frames
            if(frames[j].page_num == -1) { //nothing here yet
                num_page_faults++;
                frames[j].page_num = cur_page;
                frames[j].ref_bit = 1;
                cur_replace_pos = j + 1; // = j + 1?
                j = num_frames;
            } else if (frames[j].page_num == cur_page) { //found it in a frame
                frames[j].ref_bit = 1; //set reference bit to 1
                j = num_frames; //break out of loop and look at next page
            } else if (j == num_frames-1) { //searched all frames and did not find the page
                
                num_page_faults++;
                k = cur_replace_pos; //position to start looking in frame array
                while (replaced_a_page == 0) { //while have not replaced a page.. keep checking
                    //pages that are currently in frames
                    if (frames[k].ref_bit == 0) { //found the page to replace
                        frames[k].page_num = cur_page;
                        frames[k].ref_bit = 1; //set reference bit to 1 for this new page
                        replaced_a_page = 1;
                        cur_replace_pos = k + 1; //move the replacement pos to 1 after
                    } else if (frames[k].ref_bit == 1) {
                        frames[k].ref_bit = 0; //set the reference bit to 0
                    }
                    if (replaced_a_page == 0 && k == num_frames-1) { //went thru all the frames
                        //and did not replace one yet so keep looking from beginning of frames
                        k = 0; //start back at the beginning
                    } else {
                        k++;
                    }
                    //k++;
                }
            }
            j++;
        } //end outer most while loop
        if (cur_replace_pos >= num_frames) { //reset the position to replace to first frame
            cur_replace_pos = 0;
        }
    } //end outer for
    if (frames != NULL) {
        frames = NULL;
        free(frames);
    }
    return num_page_faults;
}

int Lru_esc(int num_frames){ //finished
    int num_page_faults = 0;
    int i,j,k;
    int cur_page;
    int cur_replace_pos=0; //position in the frames to replace
    int num_scans; //tracks which round of scan that is currently on when replacing a page
    //Whether to look for (0,0), (0,1), (0,0), or (0,1)
    frame* frames = (frame*)malloc(sizeof(frame)*num_frames);
    init_frames(&frames, num_frames);
    int replaced_a_page;
    for( i = 0; i < num_pages; i ++) {
        cur_page = page_array[i].page_num;
        num_scans = 0;
        j = 0;
        replaced_a_page = 0;
        while (j < num_frames) { //scan frames
            if(frames[j].page_num == -1) { //nothing here yet
                num_page_faults++;
                frames[j].page_num = cur_page;
                frames[j].ref_bit = 1;
                cur_replace_pos = j + 1; // = j + 1?
                if (page_array[i].access_type == 'W') { //if it was a write access
                    frames[j].mod_bit = 1;
                } else {
                    //frames[j].mod_bit = 0;
                }
                j = num_frames; //break out of loop
            } else if (frames[j].page_num == cur_page) { //found it in a frame
                if (page_array[i].access_type == 'W') { //if it was a write access
                    frames[j].mod_bit = 1;
                } else {
                    //frames[j].mod_bit = 0;
                }
                frames[j].ref_bit = 1; //set reference bit to 1
                j = num_frames; //break out of loop and look at next page
               
            } else if (j == num_frames-1) { //searched all frames and did not find the page
                k = cur_replace_pos; //start checking at cur_replace_pos
                num_scans = 0; //keep track of which scan you are on
                while(replaced_a_page == 0) { //scan thru frames and try to replace
                    
                    if (num_scans == 0) {//look for (0,0)
                        if (frames[k].ref_bit == 0 && frames[k].mod_bit == 0) { //replace
                            //printf("replacing page %d with %d\n", frames[k].page_num, cur_page);
                            frames[k].page_num = cur_page;
                            frames[k].ref_bit = 1; //update page
                            replaced_a_page = 1;
                            cur_replace_pos = k + 1;
                            if (page_array[i].access_type == 'W') { //if it was a write access
                                frames[k].mod_bit = 1;
                            } else {
                                frames[k].mod_bit = 0;
                            }
                        }
                    } else if (num_scans ==1) { //look for (0,1) and set ref bit to 0 if 1
                        if (frames[k].ref_bit == 0 && frames[k].mod_bit == 1) {//replace
                            frames[k].page_num = cur_page;
                            frames[k].ref_bit = 1; //update page
                            replaced_a_page = 1;
                            cur_replace_pos = k + 1;
                            if (page_array[i].access_type == 'W') { //if it was a write access
                                frames[k].mod_bit = 1;
                            } else {
                                frames[k].mod_bit = 0;
                            }
                        } else if (frames[k].ref_bit == 1) { //flip ref bit to 0 for next round
                            frames[k].ref_bit = 0;
                        }
                    } else if (num_scans == 2) { // look for (0,0)

                         if (frames[k].ref_bit == 0 && frames[k].mod_bit == 0) {//replace this frame
                             frames[k].page_num = cur_page;
                             frames[k].ref_bit = 1; //update page
                             replaced_a_page = 1;
                             cur_replace_pos = k + 1;
                             if (page_array[i].access_type == 'W') { //if it was a write access
                                 frames[k].mod_bit = 1;
                             } else {
                                 frames[k].mod_bit = 0;
                             }
                         }
                    } else { //look for (0,1)
                        if (frames[k].ref_bit == 0 && frames[k].mod_bit == 1) {//replace this frame
                            frames[k].page_num = cur_page;
                            frames[k].ref_bit = 1; //update page
                            replaced_a_page = 1;
                            cur_replace_pos = k + 1;
                            if (page_array[i].access_type == 'W') { //if it was a write access
                                frames[k].mod_bit = 1;
                            } else {
                                frames[k].mod_bit = 0;
                            }
                        }
                    }
                    if (replaced_a_page == 0 && k == num_frames-1) { //went thru all the frames
                        //and did not replace one yet so keep looking from beginning of frames
                        k = 0; //start back at the beginning
                    } else {
                        k++;
                    }
                    if( k == cur_replace_pos) {
                        num_scans++;
                    }
                } //end of while scanning thru frames
                num_page_faults++;
            }
            j++;
        } //end outer most while
        if (cur_replace_pos >= num_frames) { //reset replace position to 0 in frames
            cur_replace_pos = 0;
        }
        
    } //end outer most for
    if (frames != NULL) {
        frames = NULL;
        free(frames);
    }
    //printf("num_page_faults is %d\n", num_page_faults);
    return num_page_faults;
}

int read_File(FILE* fd) { //reads file and fills in pages and page_actions arrays
    char *line = NULL;
    int line_count = 0;
    char *fgetsrtn = NULL;

    char* temp_page = NULL;
    char* temp_action = NULL;
    char* ref_string = NULL;
    
    int temp_count = 0;
    int i;
    if (fd != NULL) { //file pointer was not null
        
        line = (char*)malloc(sizeof(char) * 256); //max 256 chars per line
        while( 0 == feof(fd)) { //while not at end of file
            fgetsrtn = fgets(line, 256, fd); // 256 = number of possible chars per line
            if (fgetsrtn == NULL) { //end of file

                ref_string[0] = ' '; //first space added
                for(i=0; i < num_pages; i++) {//build the reference string and print
                    //can move this inside of the while loop/reading of the file
                    strcat(ref_string, pages[i]);
                    strcat(ref_string, ":");
                    strcat(ref_string, &page_array[i].access_type);
                    if(i < num_pages-1){ //if there are still pages left, add a commma
                        strcat(ref_string, ",  ");
                    }
                    temp_count++;
                    if (temp_count == 10) { //print ref string if there have been 10 ref's
                        printf("%s\n ", ref_string);
                        //strcat(ref_string,"\n ");
                        ref_string[0] = '\0';
                        temp_count = 0;
                    }
                }
                if (temp_count < 10 && temp_count != 0) { //print leftover ref string
                    printf("%s\n ", ref_string);
                    
                }
            } else {
                if(line_count == 0) {//reading in first line = number of pages
                    num_pages = atoi(line);
                    if(num_pages < 1) { //if the number of pages was 0.. exit
                        printf("failed: num pages was less than 1\n");
                        break;
                    }
                    //this could cause errors
                    ref_string = (char*)malloc(sizeof(char) * (10*9)); //fit a max of 10 per line * 9 for safety
                    
                    /* the posibility of having 9 chars/digits per reference
                     * allocate space for the pages to be read in into page_array and
                     * the char version of the page number for adding to the reference string
                     */
                    page_array = (page*)malloc(sizeof(page)*num_pages);
                    pages = (char**)malloc(sizeof(char*) * num_pages);
                } else { //past the first line
                    temp_page = strtok(line, " ");
                    temp_action = strtok(NULL, "\n");
                    
                    if(strcmp(temp_action, "r")==0) { //fix formatting for output
                        temp_action[0] = 'R';
                    }
                    if(strcmp(temp_action, "w") == 0){//fix formatting for output
                        temp_action[0] = 'W';
                    }
                    if (temp_action[1] == ' '){ //fix formatting (if there was a space after the acces type)
                        temp_action[1] = '\0';
                    }
                    //add space for page number to the char array "pages"
                    pages[line_count-1] = (char*)malloc(sizeof(temp_page));
                    //printf("temp_page was %s\n", temp_page);
                    //add the page number to the char array "pages"
                    strcat(pages[line_count-1], temp_page);
                    
                    page_array[line_count-1].page_num = atoi(temp_page);
                    page_array[line_count-1].access_type = *temp_action;
                    page_array[line_count-1].ref_bit = 0;
                    page_array[line_count-1].mod_bit =0;

                } //end of if/else
                line_count++;
            }
            
        }//end of while
    } else { //file pointer was null
        //return or exit?
        printf("failed on file pointer\n");
    }
    if(fgetsrtn != NULL) {
        fgetsrtn = NULL;
        free(fgetsrtn);
    }
    if (line != NULL) {
        line = NULL;
        free(line);
    }
    if ( ref_string != NULL) {
        ref_string = NULL;
        free(ref_string);
    }
    if( temp_page != NULL){
        temp_page = NULL;
        free(temp_page);
    }
    if(temp_action != NULL) {
        temp_action = NULL;
        free(temp_action);
    }
    return 0;
}

int reset_array() {
    
    return 0;
}

int init_frames(frame **frames, int num_frames) {
    int i;
    for(i =0; i < num_frames; i++) {
        (*frames)[i].page_num = -1; //initialize to -1 so can differentiate from a 0 page#
        (*frames)[i].used_again = 0; //initialize to false
        (*frames)[i].recently_used = 0; //init to false
        (*frames)[i].ref_bit = 0; //init to false (lru 2nd)
        (*frames)[i].mod_bit = 0; //init to false (lur 2nd enhanced)
    }
    return 0;
}
