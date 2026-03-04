#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 3840
#define HEIGHT 2160

int main() {
    time_t start, now;
    time(&start);
    time(&now);
    srand(time(NULL));
    char arr[20];
    
    
    
    int count = 1;
    
    while(difftime(now, start) <= 1)
    {
        time(&now);
        sprintf(arr, "%d.pgm", count);
        FILE *fp = fopen(arr, "w");
        fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HEIGHT);
        
        
        for(int i = 0;  i < WIDTH;  i++)
        {
            for(int j = 0; j< HEIGHT; j++)
            {
                
                short int pixel = (rand() % 2) * 255;
                
                fprintf(fp, "%hd %hd %hd ", pixel, pixel, pixel);
                 
            }
            fprintf(fp, "\n");
        }
        fclose(fp);
        count++;
    }
    
    printf("4K Black & White image generated!\n");
    return 0;
}