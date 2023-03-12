#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveShape(int shapeReturn[4][4], int shapeInput[4][4]);
void placeShapeOntoField(int field[12][10], int shape[4][4], int position);
int checkSpace(int field[12][10], int shape[4][4], int currentI, int currentJ);
void clearLine(int field[12][10]);
void rotateShape(int arr[4][4]);
void shiftspaces(int arr[4][4]);
void outputField(int field[12][10]);

int main(int argc, char *argv[]) {
    char c;
    int field[12][10];
    int i, j;
    int b[4][4] = {{0,0,0,0}, {0,1,1,0}, {1,1,0,0}, {0,1,0,0}};
    int d[4][4] = {{0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {1,1,0,0}};
    int g[4][4] = {{0,0,0,0}, {1,1,0,0}, {1,1,0,0}, {1,0,0,0}};
    int h[4][4] = {{0,1,0,0}, {0,1,0,0}, {1,1,0,0}, {1,0,0,0}};
    int m[4][4] = {{0,0,0,0}, {0,0,1,0}, {0,1,1,0}, {1,1,0,0}};
    int n[4][4] = {{0,0,0,0}, {0,1,0,0}, {1,1,1,0}, {0,1,0,0}};
    char rotationText[100] = "";
    int rotations;
    char position;
    int shape[4][4];
    int caseNum;
    FILE *file;

    if (argc != 2) {
        return 1;
    }
    
    file = fopen(argv[1], "r");
       
    for(i=0; i < 12; i++){
        for(j=0; j < 10; j++){
            field[i][j] = 0;
        }  
        
    }
    caseNum = 0;
    while ((c = fgetc(file)) != EOF) {
        
        switch (caseNum) {
            case 0:
                if(c == ' ' || c == '\n'){
                    break;
                }
                if(c == 'B' || c == 'D' || c == 'G' || c == 'H' || c == 'M' || c == 'N'){
                    ungetc(c,file);
                    caseNum = 1;
                }
                if(c == 'r' ||  c == 'R'){
                    caseNum = 2;
                }
                if(c == 'c' ||  c == 'C'){
                    ungetc(c,file);
                    caseNum = 3;
                }
                
                continue;
                break;
            case 1:
                if(c == 'B'){
                    saveShape(shape,b);
                }else if(c == 'D'){
                    saveShape(shape,d);
                }else if(c == 'G'){
                    saveShape(shape,g);
                }else if(c == 'H'){
                    saveShape(shape,h);
                }else if(c == 'M'){
                    saveShape(shape,m);
                }else if(c == 'N'){
                    saveShape(shape,n);
                }
                c = fgetc(file);
                caseNum = 0;
                break;
            case 2:
                if(c != ' '){
                    strncat(rotationText, &c, 1);
                    break;
                }
                rotations = (atoi(rotationText)) % 4;
                for(i =0; i < rotations; i++){
                    rotateShape(shape);
                }
                shiftspaces(shape);
                
                caseNum = 0;
                rotationText[0] = '\0';
                continue;
                break;
            case 3:
                position = (int)(c=fgetc(file)) - (int)'0';
                placeShapeOntoField(field, shape, position);
                clearLine(field);
                caseNum = 0;
                break;
        }
        
    }
    outputField(field);
    fclose(file);
    return 0;
}

/*Save shape to shape array*/
void saveShape(int shapeReturn[4][4], int shapeInput[4][4]){
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            shapeReturn[i][j] = shapeInput[i][j];
        }
    }
}

/*Moves shape down as much as possible*/
void placeShapeOntoField(int field[12][10], int shape[4][4], int position){
    int i, k,l;    
    int check;
    for (i=0; i<12; i++){
        check = checkSpace(field, shape, i, position);
        if(check != -1){
            for(k=0; k < 4; k++){
                for(l = 0; l < 4; l++){
                    if(shape[k][l] == 1){
                        if(check-(4-k) < 0){
                            /*exit(1);*/
                        }
                        field[check+k][position + l] = shape[k][l];
                    }
                }
            }
            break;
        }
    }
}

/*Checks if the object is allowed in that spot*/
int checkSpace(int field[12][10], int shape[4][4], int currentI, int currentJ){
    int i,j;
    for (i=0; i< 4; i++){
        for(j=0; j<4; j++){
            if(field[currentI+i][currentJ+j] == 1 && shape[i][j] == 1){
                return currentI -1;
            }
        }
    }
    if(currentI + 3 == 11){
        return currentI;
    }
    
    return -1;
}


/*Delete line if full*/
void clearLine(int field[12][10]){
    int i,j,k,l;
    for(i = 11; i >= 0; i--) {
        for(j = 0; j < 10; j++) {
            if(field[i][j] == 0){
                break;
            }
            if(j == 9){
                for (k = i; k >= 0; k--) {
                    for (l = 0; l < 10; l++) {
                        if(k==0){
                            field[k][l] = 0;
                        }else{
                            field[k][l] = field[k-1][l];
                        }   
                    }
                }
            }
        }  
    }
}

/*Rotate shape 90 degrees*/
void rotateShape(int arr[4][4]){
    int temp;
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = i; j < 4; j++) {
            temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            temp = arr[i][j];
            arr[i][j] = arr[i][3-j];
            arr[i][3-j] = temp;
        }
    }
}

/*Shift shape so that it's left and down most*/
void shiftspaces(int arr[4][4]) {
    int i, j;
    int is_left_column_empty = 1;
    int is_bottom_row_empty = 1;
    while(is_left_column_empty || is_bottom_row_empty){
        is_left_column_empty = 1;
        is_bottom_row_empty = 1;
        for (i = 0; i < 4; i++) {
            if (arr[i][0] != 0) {
                is_left_column_empty = 0;
                break;
            }
        }

        if (is_left_column_empty) {
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 3; j++) {
                    arr[i][j] = arr[i][j+1];
                }
                arr[i][3] = 0;
            }
        }

        for (j = 0; j < 4; j++) {
            if (arr[3][j] != 0) {
                is_bottom_row_empty = 0;
                break;
            }
        }

        if (is_bottom_row_empty) {
            for (j = 0; j < 4; j++) {
                for (i = 3; i > 0; i--) {
                    arr[i][j] = arr[i-1][j];
                }
                arr[0][j] = 0;
            }
        }
    }
    
    
}

/*Output field */
void outputField(int field[12][10]){
    int i, j;
    for(i = 0; i < 12; i++) {
        printf("|");
        for(j = 0; j < 10; j++) {
            if(field[i][j]){
                printf("#");
            }else{
                printf(" ");
            }
            
        }
        printf("|\n");
    }
    printf("+----------+\n");
}