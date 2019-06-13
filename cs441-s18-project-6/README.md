# CS441/541 Project 6

## Author(s): Nick Williams




## Date: 4/12/18




## Description: Page Replacement Algorithms
Simulation of page replacement algorithms, those algorithms being: optimal, First in first out, least recently used, 
least recently used second chance and least recently used enhanced second chance 



## How to build the software
Navigate to the program's directory and compile from the command line/terminal by typing "make"



## How to use the software
start the program by typing "./pagefault *test file's path"
if the "-f" option is inputted, a number must be included after that is between 1 and 7 inclusive



## How the software was tested
(1) opt-test1 (tested with 7 frames = 10 page faults and 2 frames = 14 page faults) : tests replacement of pages at the end 
    of the page_array(pages being referenced) where there is only one or a few pages left to check (forces the first position not referenced in the frames array to be replaced)
(2)fifo-test1 (tested with 5 frames =  8 page faults - but should work for 4+ frames) test where first few are misses without filling
all the frames then a few hits then introduce misses to make sure the correc frames were replaced
    also tests double digit page numbers being read in
(3) lru-test1 (tested with 3 frames = 17 page faults): testing hitting before all frames are filled & having many page faults in a row
(4) lru-esc1 (tested with 3 frames = 7 page faults): testing for high proportion of page faults and page hits that are also
writes over previously read pages - changing reference and modify bits frequently
(5) lru-esc2 (tested with 4 frames = 7 page faults): testing replacing few faults where pages access types are initially reads
+ sequential hits cause reference/modify bits to be updated from 0 to 1
    Different ordering and replacements than the first test for lru-esc


## Test Suite
cs441-s18-project-6/tests


## Known bugs and problem areas
Test files with a space after the letter or access type will result in the reference string not being printed out
-- same thing happens when there is no extra space at the last line at end of file to detect the EOF
Autolab only sometimes (very rarely) thinks it is detecting a wrong value in the reference string when really the output
is exactly the same (there is just a difference in how the spaces are stored in the reference string)

