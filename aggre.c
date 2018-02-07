/*
Target: 2018-02-06_temp.log 2018-02-07_temp.log ... 2018-02-13_temp.log
Dest  : 2018-02-06_2018-02-13_temp.log
Usage: ./argv[0] 2018-02-06 2018-02-07
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LATER_HALF_OF_FNAME "_temp.log"
#define TEMP_ARRAY_ROW 1440

// delete char from string
int delete_char(char string[], char key);
// generate date after n days
void gen_date(char *dst, char *src, int days);
// get point of null character in string
int get_null_char(const char string[]);

int main(int argc, char *argv[])
{
    int nod;  // number of days
    int h, m;
    int idx;
    double temp;
    double temp_array[TEMP_ARRAY_ROW] = {0};
    char date_begin[12] = {'\0'};
    char date_end[12] = {'\0'};
    char dir[256] = {'\0'};
    char src_name[256] = {'\0'};
    char dst_name[256] = {'\0'};
    FILE *fp;
  
    // check arguments
    if (argc != 4) {
      fprintf(stderr, "usage: ./batch dir begin end\n");
      return 1;
    }
    
    // check dir tail and substitute
    idx = get_null_char(argv[1]);
    if (argv[1][idx-1] != '/') {
        strcpy(dir, argv[1]);
        dir[idx] = '/';
    } else {
        strcpy(dir, argv[1]);
    }
    
    // debug
    /*
    for (int i = 0; i < 4; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    */
    
    strncpy(date_begin, argv[2], sizeof(date_begin));
    strncpy(date_end, argv[3], sizeof(date_end));
    // printf("date_begin[] = %s\n", date_begin);
    // printf("date_end[] = %s\n", date_end);
    
  
    delete_char(date_begin, '-');
    delete_char(date_end, '-');
    // printf("date_begin[] = %s\n", date_begin);
    // printf("date_end[] = %s\n", date_end);
  
    // get number of files to process
    nod = atoi(date_end) - atoi(date_begin);
    // printf("nod = %d\n", nod);
    
    // aggregate data
    for (int i = 0; i < nod; i++) {
        strcpy(src_name, dir);
        // printf("src_name[] = %s\n", src_name);
        gen_date(src_name, argv[2], i);  
        // printf("It is %s from %s to %d\n", src_name, argv[2], i);
        strncat(src_name, LATER_HALF_OF_FNAME, sizeof(LATER_HALF_OF_FNAME));
        // printf("src_name = %s\n", src_name);
        
        if ((fp = fopen(src_name, "r")) == NULL) {
            perror("fopen");
            return 1;
        } else {
            while ((fscanf(fp, "%d:%d %lf", &h, &m, &temp)) == 3) {
                // printf("%02d:%02d %f\n", h, m, temp);
                idx = h * 60 + m;
                temp_array[idx] += temp;
            }
        }
    }
    fclose(fp);
    
    // Generate the name of the file to be output
    strcpy(dst_name, dir);
    strncat(dst_name, argv[2], 10);
    // printf("get_null_char = %d\n", get_null_char(dst_name));
    dst_name[get_null_char(dst_name)] = '_';
    strncat(dst_name, argv[3], 10);
    // printf("dst_name[] = %s\n", dst_name);
    // strncat(dst_name, LATER_HALF_OF_FNAME, sizeof(LATER_HALF_OF_FNAME));
    // printf("dst_name[] = %s\n", dst_name);
    
    
    // Output
    if ((fp = fopen(dst_name, "w")) == NULL) {
        perror("fopen(dst_name)");
        return 1;
    } else {
        for (size_t i = 0; i < TEMP_ARRAY_ROW; i++) {
            if (i <= 59) {
                h = 0; m = i;
            } else {
                h = i / 60; m = i % 60;
            }
            fprintf(fp,"%02d:%02d %f\n", h, m, temp_array[i] / nod);
        }
    }
    
    printf("%s was successflly saved.\n", dst_name);
    return 0;
}

int get_null_char(const char string[])
{
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }
    return i;
}

void gen_date(char *dst, char *src, int days)
{
    int y, m, d;
    char temp[32] = {'\0'};
    sscanf(src, "%d-%d-%d", &y, &m, &d);
    struct tm tm = { 0, 0, 0, d, m-1, y-1900 };
    time_t time = mktime(&tm) + 24 * 60 * 60 * days;
    struct tm *ltime = localtime(&time);
    sprintf(temp, "%d-%02d-%02d", ltime->tm_year+1900, ltime->tm_mon+1, ltime->tm_mday);
    strcat(dst, temp);
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
