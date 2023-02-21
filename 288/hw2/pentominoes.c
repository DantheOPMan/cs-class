#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveShape(int shapeReturn[4][4], int shapeInput[4][4]);
void placeShapeOntoField(int field[10][12], int shape[4][4]);
void clearLine(int field[10][12]);
void rotateShape(int arr[4][4]);
void shiftspaces(int arr[4][4]);
void outputField(int field[10][12]);

int main(int argc, char *argv[]) {
    char c;
    int field[10][12];
    int i, j;
    int b[4][4] = {{0,0,1,0}, {0,1,1,1}, {0,1,0,0}, {0,0,0,0}};
    int d[4][4] = {{0,0,0,1}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}};
    int g[4][4] = {{0,1,1,1}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}};
    int h[4][4] = {{0,0,1,1}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}};
    int m[4][4] = {{0,0,0,1}, {0,0,1,1}, {0,1,1,0}, {0,0,0,0}};
    int n[4][4] = {{0,0,1,0}, {0,1,1,1}, {0,0,1,0}, {0,0,0,0}};
    char rotationText[100] = "";
    int rotations;
    char position;
    int shape[4][4];
    FILE *file;

    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Unable to open file: %s\n", argv[1]);
        return 1;
    }

    /*File is now open and ready to read or write to.*/
    
    for(i=0; i< 10; i++){
        for(j=0; i< 12; j++){
            field[i][j] = 0;
        }  
    }
    

    while ((c = fgetc(file)) != EOF) {
        
        /*skip if space*/
        if(c == ' ' || c == '\n'){
            continue;
        }

        if(c == 'B' || c == 'D' || c == 'G' || c == 'H' || c == 'M' || c == 'N'){
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

            while ((c = fgetc(file)) == ' '){

            }
            
            while((c = fgetc(file)) != ' '){
                strncat(rotationText, &c, 1);
            }
            rotations = (atoi(rotationText)) % 4;
            for(i =0; i < rotations; i++){
                rotateShape(shape);
            }
            shiftspaces(shape);

            while ((c = fgetc(file)) == ' '){

            }
            position = (int)(fgetc(file));


        }
    }

    fclose(file);
    return 0;
}

/*Save shape to shape array*/
void saveShape(int shapeReturn[4][4], int shapeInput[4][4]){
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = i; j < 4; j++) {
            shapeReturn[i][j] = shapeInput[i][j];
        }
    }
}

/*Moves shape down as much as possible*/
void placeShapeOntoField(int field[10][12], int shape[4][4], int position){
    int i,j;
    for (i=0; i<11; i++){
        for(j = position; j < position + 4; j++){
            if(!checkSpace(field, shape, i, position){
                
            }
            if(i==10 || )){

            }
        }
    }
}

int checkSpace(int field[10][12], int shape[4][4], int currentI, int currentJ){
    int i,j;

    for (i=0; i<4; i++){
        for(j = 0; j < 4; j++){
            if(field[currentI+i][currentJ+j] && shape[i][j]){
                return 0;
            }
        }
    }
    return 1;
}


/*Delete line if full*/
void clearLine(int field[10][12]){
    int i,j,k,l;
    for(j = 11; j > 0; j--) {
        for(i = 0; i < 10; i++) {
            if(field[i][j] == 0){
                break;
            }
            if(field[i][j] == 1 && i == 9){
                for (k = j; k > 0; k--) {
                    for (l = 0; l < 10; l++) {
                        field[k][l] = field[k-1][l];
                    }
                }
                j++;
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
    int is_left_column_empty;
    int is_bottom_row_empty;
    do{
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
    }while(!is_left_column_empty || !is_bottom_row_empty);
    
    
}

/*Output field */
void outputField(int field[10][12]){
    int i, j;
    for(i = 0; i < 10; i++) {
        printf("|");
        for(j = 0; j < 12; j++) {
            if(field[i][j]){
                printf("#");
            }else{
                printf(" ");
            }
            
        }
        printf("|\n");
    }
    printf("+-----------+\n");
}