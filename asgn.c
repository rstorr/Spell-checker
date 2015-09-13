/*asgn.c*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "mylib.h"
#include "rbt.h"
#include <time.h>
#include "flexarray.h"
#include "container.h"
#include "htable.h"

void print_key(char *s) {
    printf("%s", s);
}
/*The main method 
@param argc - an integer that acts as a count of terminal inputs.
@param **argv - points to the position in the terminal input that is
being executed.
Includes the help file which explains the program operands*/
int main(int argc, char **argv) {
   const char *optstring = "rs:pih";
   container_t type = FLEX_ARRAY;
   int table_size = 3877;
   
   int print_hash = 0;
   int print_info = 0;
   
   clock_t start_time, end_time;
   
   double fill_time = 0.0;
   double search_time = 0.0;
   int unknown_words = 0;
   char option;
   htable h = NULL;
   char word[256];
   FILE *optstream;
   /*Enters while loop and gets the input from the 
   terminal and cases will respond accordingly*/
   while ((option = getopt(argc, argv, optstring)) != EOF){
       switch (option) {
        case 's':
            table_size = atoi(optarg);
        case 'p':
            print_hash = 1;
            break;
        case 'i':
            print_info = 1;
            break;
        case 'h':
            fprintf(stderr, "\n");
            fprintf(stderr, "For each of the below commands an action \n");
            fprintf(stderr, "is performed in the program. Enter these\n");
            fprintf(stderr, "\n");
            fprintf(stderr, "\n");
            fprintf(stderr, "-r: \n ");
            fprintf(stderr, "When entered this causes the hash table to use a red-black-tree \n");
            fprintf(stderr, "as the container type.\n");
            fprintf(stderr, "\n");
            fprintf(stderr, "-s:'table-size':\n");
            fprintf(stderr, "'table-size' will be an integer that represents the \n");
            fprintf(stderr, "size of the hash table.\n");
            fprintf(stderr, "\n");
            fprintf(stderr, "-p:\n");
            fprintf(stderr, "This will print out the hash table to the standard screen\n");
            fprintf(stderr, "\n");
            fprintf(stderr, "-i:\n");
            fprintf(stderr, "This will return information to the standard error output \n");
            fprintf(stderr, "\n");
            fprintf(stderr, "-h:\n");
            fprintf(stderr, "This will print a help message to standard error output\n");
            fprintf(stderr, "(stderr) with information required to use the program effectively.\n");
            fprintf(stderr, "\n");

            return EXIT_SUCCESS;
         case 'r':
            type = RED_BLACK_TREE;
            break;
            /*if no recognisable input is entered into the command line*/
        default:
            fprintf(stderr, "ERROR: Refer to -h");
            return EXIT_FAILURE;
       }
   }
   /*new htable using table_size and type as parameters*/
    h = htable_new(table_size, type);

   if(optind < argc){
       start_time = clock();
       
       optstream = fopen(argv[optind], "r");
       while(getword(word, sizeof word, optstream)!=EOF){
           htable_insert(h, word);
       }
       
       end_time = clock();
       fill_time = (end_time - start_time)/(double)CLOCKS_PER_SEC;
       
       fclose(optstream);
   }
   /*enter the while loop and searches for words that don't match*/
   start_time = clock();
   strcpy(word, "");
   while(getword(word, sizeof word, stdin) != EOF){
       int word_exists = htable_search(h, word);
       if (word_exists == 0){
           fprintf(stdout, "%s\n", word);
           unknown_words++;
       }
   }
   end_time = clock();
   
   if(strcmp(word,"") == 0){
       search_time = 0.0;
   }else{
       search_time = (end_time - start_time)/(double)CLOCKS_PER_SEC;
   }
   
   if (print_info == 1){
       fprintf(stderr, "Fill time: %f\nSearch time: %f\nUnknown words: %d\n",
       fill_time, search_time, unknown_words);
   }
   
   if (print_hash == 1){
       htable_print(h);
       htable_free(h);
       return 1;
   }
   
   
   htable_free(h);
   
   return 1;
}