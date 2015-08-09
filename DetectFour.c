#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findSquares(char* lines, int x, int y, int lineSize, int lineCount){
	int i;
	int count = 0;
	for (i = x+1; i < lineSize; i++){
		char c = *(lines + y*lineSize + i);
		char c5 = *(lines + (y+1)*lineSize + i);
		if (c == '+' && y < lineCount-1 && c5 == '|'){
			int j;
			for (j = y+1; j < lineCount; j++){
				char c2 = *(lines + j*lineSize + x);
				char c3 = *(lines + j*lineSize + i);
				if ( (c2 == '|' && c3 == ' ') || (c2 == ' ' && c3 == '|') || (c2 == ' ' && c3 == ' ') ){
					break;
				}
				if (c2 == '+' && c3 == '+'){
					count++;
				}
			}
		}
	}
	return count;
}

int main(){
	int lineSize = 256;
	int lineCount = 0;
	char buffer[lineSize];
	char* lines = (char*)malloc(1);
    while (fgets(buffer, lineSize, stdin) != NULL){
        if (*(buffer+strlen(buffer)-1) == '\n'){
            *(buffer+strlen(buffer)-1) = '\0';
        }
        lineCount++;
        lines = (char*)realloc(lines, lineSize*lineCount*sizeof(char));
    	strcpy(lines + (lineCount-1)*lineSize, buffer);
    }

    int i;
    int squareCount = 0;
    for (i = 0; i < lineCount; i++){
    	int j;
    	if (i >= lineCount-1){
    		continue;
    	}
    	for (j = 0; j < lineSize-1; j++){
    		char c = *(lines + i*lineSize + j);
    		char nextC = *(lines + i*lineSize + j + 1);
    		if (c == '+' && nextC == '-'){
    			squareCount += findSquares(lines, j, i, lineSize, lineCount);
    		}
    	}
    }

    printf("%d\n", squareCount);

	return 0;
}