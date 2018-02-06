/*
Target: 2018-02-06_temp.log 2018-02-07_temp.log ... 2018-02-13_temp.log
Dest  : 2018-02-06_2018-02-13_temp.log
Usage: ./argv[0] 2018-02-06 2018-02-07

 - devide argv[1] to two date.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LATER_HALF_OF_FNAME "_temp.log"

// delete char from string
int delete_char(char string[], char key);
// generate date after n days
void gen_date(char *dst, char *src, int days);

int main(int argc, char *argv[])
{
    int nod;  // number of days
    double temp_array[1440] = {0};
    char date_begin[12];
    char date_end[12];
    char fname[32];
    FILE *fp;
  
    // check arguments
    if (argc != 3) {
      fprintf(stderr, "usage: ./batch begin end\n");
      return 1;
    }
    
    strncpy(date_begin, argv[1], sizeof(date_begin));
    strncpy(date_end, argv[2], sizeof(date_end));
    printf("date_begin[] = %s\n", date_begin);
    printf("date_end[] = %s\n", date_end);
    
  
    delete_char(date_begin, '-');
    delete_char(date_end, '-');
    printf("date_begin[] = %s\n", date_begin);
    printf("date_end[] = %s\n", date_end);
  
    nod = atoi(date_end) - atoi(date_begin);
    printf("nod = %d\n", nod);
    
    
    for (int i = 0; i < nod; i++) {
        gen_date(fname, argv[1], i);  
        printf("It is %s from %s to %d\n", fname, argv[1], i);
        strncat(fname, LATER_HALF_OF_FNAME, sizeof(LATER_HALF_OF_FNAME));
        printf("fname = %s\n", fname);
        
    }
    
}

void gen_date(char *dst, char *src, int days)
{
    int y, m, d;
    sscanf(src, "%d-%d-%d", &y, &m, &d);
    struct tm tm = { 0, 0, 0, d, m-1, y-1900 };
    time_t time = mktime(&tm) + 24 * 60 * 60 * days;
    struct tm *ltime = localtime(&time);
    sprintf(dst, "%d-%02d-%02d", ltime->tm_year+1900, ltime->tm_mon+1, ltime->tm_mday);
}

int delete_char(char string[], char key)
{
    int i = 0;
    // loop to null character
    while (string[i] != '\0') {
      // when underscore is found
      if (string[i] == '-') {
        int j = i;
        while (string[j] != '\0') {
          string[j] = string[j+1];
          j++;
        }
      }
      i++;
    }
    return 0;
}

/*
// serach character from character string.
int search_char(char string[], char key)
{
    int idx = 0;
    while (string[idx] != '\0') {
      printf("string[%d] = %c\n", idx, string[idx]);
      if (string[idx] == key) return idx;
    }
    return -1;
}

int split_arg(char arg[], char b[], char e[])
{
  int i = 0;
  
  while (arg[i] != '\0') {
    if (arg[i] == '_') {
    }
    i++;
  }
}
*/
