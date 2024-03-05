#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h> 
#include "Status.h"

Boolean debug = FALSE;

int ReadData(FILE* fp, char* format, ...) {
    int* i;     
    float* f;   
    char* ch;   
    char* s;    
    int n;      
    int len;    
    int k;      
    int tmp;    
    va_list ap; 
    int count = 0;
    
    len = strlen(format);
    va_start(ap, format);
    for(k = 1; k <= len; k = k + 2) {
        while((tmp = getc(fp)) != EOF) {
            if((tmp >= 0 && tmp <= 127)) {
                ungetc(tmp, fp);
                break;
            }
        }
        if(tmp == EOF) {
            break;
        }
        if(format[k] == 'c') {
            ch = va_arg(ap, char*);
            
            count += fscanf(fp, "%c", ch);
        }
        if(format[k] == 'd') {
            i = va_arg(ap, int*);
            
            while((tmp = getc(fp)) != EOF) {
                if((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+') {
                    ungetc(tmp, fp);
                    break;
                }
            }
            
            if(tmp != EOF) {
                count += fscanf(fp, "%d", i);
            }
        }
        
        if(format[k] == 'f') {
            f = va_arg(ap, float*);
            
            while((tmp = getc(fp)) != EOF) {
                if((tmp >= '0' && tmp <= '9') || tmp == '-' || tmp == '+' || tmp == '.') {
                    ungetc(tmp, fp);
                    break;
                }
            }
            
            if(tmp != EOF) {
                count += fscanf(fp, "%f", f);
            }
        }
        
        if(format[k] == 's') {
            s = va_arg(ap, char*);
            
            n = 0;
            
            while((tmp = getc(fp)) != EOF && (!isprint(tmp) || tmp == ' ')) {
            }
            
            if(!feof(fp)) {
                ungetc(tmp, fp);
                
                while((tmp = getc(fp)) != EOF) {
                    if(isprint(tmp) && tmp != ' ') {
                        s[n++] = tmp;
                    } else {
                        ungetc(tmp, fp);
                        break;
                    }
                }
                
                count++;
            }
            
            s[n] = '\0';
        }
    }
    
    va_end(ap);
    
    return count;
}

void PressEnterToContinue(Boolean debug) {
    fflush(stdin);

    if(debug) {
        printf("\nPress Enter to Continue...");
        getchar();
    } else {
        printf("\n");
    }
    fflush(stdin);
}

void Wait(long time) {
    double i;
    
    if(time<0) {
        time = -time;
    }
    
    for(i = 0.01; i <= 100000.0 * time; i += 0.01) {
        
    }
}

void skipBlank(FILE* fp) {
    int ch;
    
    if(fp == NULL) {
        return;
    }
    
    while((ch = getc(fp)) != EOF) {
        if(ch >= 0 && ch <= 127) {
            if(ch != '\r' && ch != '\n' && ch != ' ' && ch != '\t' && ch != '\f') {
                ungetc(ch, fp);
                break; 
            }
        }
    }
}
