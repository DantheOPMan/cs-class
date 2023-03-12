#include <stdio.h>
#include <stdlib.h>

struct Element {
    int value;
    int row;
    int column;
    struct Element *rowElement;
    struct Element *columnElement;
};

struct Header {
    int index;
    struct Header *header;
    struct Element *element;
};

struct Matrix {
    struct Header *headRowHeader;
    struct Header *headColumnHeader;
    int rows;
    int columns;
    int fillValue;
};

struct Matrix MTRX_alloc(char *filename, int fillValue);
void MTRX_free(struct Matrix* m);
int MTRX_getElement(struct Matrix *m, int row, int column);
void MTRX_write(struct Matrix *m, char *filename);
struct Matrix MTRX_add(struct Matrix *a, struct Matrix *b, int fillValue);
struct Matrix MTRX_multiply(struct Matrix *a, struct Matrix *b, int fillValue);
struct Matrix MTRX_transpose(struct Matrix *m);
int insertHeaderColumn(struct Matrix *a, struct Header *input);
void appendHeaderRow(struct Matrix *a, struct Header *input);
void appendElementToEnd(struct Header *headerRow, struct Header *headerCol, int val, int row, int col);
void Header_free_col(struct Matrix *m);
void Header_free_row(struct Matrix *m);
void Element_free_row(struct Header *a);

int main() {
    struct Matrix a, t, l, s;
    a = MTRX_alloc("matrixA.txt", 0);
    t = MTRX_transpose(&a);
    l = MTRX_add(&a,&a,0);
    s = MTRX_multiply(&t, &l,0);
    MTRX_write(&t, "matrixT.txt");
    MTRX_write(&l, "matrixL.txt");
    MTRX_write(&s, "matrixS.txt");
    MTRX_free(&t);
    MTRX_free(&a);
    MTRX_free(&l);
    MTRX_free(&s);
    return 0;
}

void MTRX_free(struct Matrix* m){
    while(m->headRowHeader!= NULL){
        Header_free_row(m);
    }
    while(m->headColumnHeader!= NULL){
        Header_free_col(m);
    }
}
void Header_free_col(struct Matrix *m){
    struct Header *p = m->headColumnHeader;
    m->headColumnHeader = p->header;
    free(p);
}
void Header_free_row(struct Matrix *m){
    struct Header *p = m->headRowHeader;
    while(p->element != NULL){
        Element_free_row(p);
    }
    m->headRowHeader = p->header;
    free(p);
}
void Element_free_row(struct Header *a){
    struct Element *p = a->element;
    a->element = p->rowElement;
    free(p);
}

struct Matrix MTRX_multiply(struct Matrix *a, struct Matrix *b, int fillValue){
    struct Matrix y;
    int m,n,p; 

    int val;
    int count = 1;
    struct Header *curRowInput;
    struct Header *colInput;

    /*a->columns == b->rows;*/

    y.rows = a->rows;
    y.columns = b->columns; /*might have to reverse rows and columns*/
    y.fillValue = fillValue;
    y.headRowHeader = NULL;
    y.headColumnHeader = NULL;

    for(m=1;m<=y.rows; m++){
        count = 1;
        for(p=1; p<= y.columns; p++){
            val = 0;
            for(n=1; n<=a->columns; n++){
                val += MTRX_getElement(a, m,n) * MTRX_getElement(b, n,p);
            }
            if(val!=fillValue){
                if(count){
                    curRowInput = malloc(sizeof(struct Header));
                    curRowInput->index = m;
                    curRowInput->header = NULL;
                    curRowInput->element = NULL;
                    appendHeaderRow(&y, curRowInput);
                    count = 0;
                }
                colInput = malloc(sizeof(struct Header));
                colInput->index = p;
                colInput->header = NULL;
                colInput->element = NULL;
                insertHeaderColumn(&y,colInput);
                appendElementToEnd(curRowInput, colInput,val,m,p);
            }
        }
    }
    return y;
}

struct Matrix MTRX_transpose(struct Matrix *m){
    struct Matrix y;
    int i, j;
    int val;
    int count = 1;
    struct Header *curRowInput;
    struct Header *colInput;

    y.rows = m->columns;
    y.columns = m->rows;
    y.fillValue = m->fillValue;
    y.headRowHeader = NULL;
    y.headColumnHeader = NULL;
    
    for(i=1; i<= y.rows;i++){
        count = 1;
        for(j=1; j<=y.columns;j++){
            val = MTRX_getElement(m, j,i);
            if(val!=y.fillValue){
                if(count){
                    curRowInput = malloc(sizeof(struct Header));
                    curRowInput->index = i;
                    curRowInput->header = NULL;
                    curRowInput->element = NULL;
                    appendHeaderRow(&y, curRowInput);
                    count = 0;
                }
                colInput = malloc(sizeof(struct Header));
                colInput->index = j;
                colInput->header = NULL;
                colInput->element = NULL;
                insertHeaderColumn(&y,colInput);
                appendElementToEnd(curRowInput, colInput,val,i,j);
            }
        }        
    }
    return y;
}

struct Matrix MTRX_add(struct Matrix *a, struct Matrix *b, int fillValue){
    struct Matrix y;
    int i,j;
    int val;
    int count = 1;
    struct Header *curRowInput;
    struct Header *colInput;

    y.rows = a->rows;
    y.columns = a->columns;
    y.fillValue = fillValue;
    y.headRowHeader = NULL;
    y.headColumnHeader = NULL;
    
    for(i=1; i<= y.rows;i++){
        count = 1;
        for(j=1; j<=y.columns;j++){
            val = MTRX_getElement(a, i,j) + MTRX_getElement(b, i,j);
            if(val!=fillValue){
                if(count){
                    curRowInput = malloc(sizeof(struct Header));
                    curRowInput->index = i;
                    curRowInput->header = NULL;
                    curRowInput->element = NULL;
                    appendHeaderRow(&y, curRowInput);
                    count = 0;
                }
                colInput = malloc(sizeof(struct Header));
                colInput->index = j;
                colInput->header = NULL;
                colInput->element = NULL;
                insertHeaderColumn(&y,colInput);
                appendElementToEnd(curRowInput, colInput,val,i,j);
            }
        }        
    }
    return y;
}

int MTRX_getElement(struct Matrix *m, int row, int column){
    struct Header *i;
    struct Element *p;
    
    for(i=m->headRowHeader; i != NULL; i = i->header){
        if(row == i->index){
            for(p=i->element; p != NULL; p=p->rowElement){
                if(p->column == column){
                    return p->value;
                }else if(p->column > column){
                    break;
                }
            }
            break;
        }
    }
    return m->fillValue;
}

struct Matrix MTRX_alloc(char *filename, int fillValue){
    FILE* fp = fopen(filename, "r");
    struct Matrix a;
    
    struct Header *curRowInput;
    struct Header *colInput;
    
    int c;
    int i = 1;
    int j = 1;
    int count = 1;
    /*initialize matrix*/
    a.rows = 0;
    a.columns = 0;
    a.fillValue = fillValue;
    a.headRowHeader = NULL;
    a.headColumnHeader = NULL;

    /*Read input file and save to array*/
    while((c = fgetc(fp)) != EOF){
        if(c == '\n'){
            count =1;
            i++;
            a.columns = j-1;
            j = 1;
        }else if(c != ' '){
            ungetc(c, fp);
            fscanf(fp, "%d", &c);
            if(c == fillValue){
                j++;
            }else if(c!=fillValue){
                if(count){
                    curRowInput = malloc(sizeof(struct Header));
                    curRowInput->index = i;
                    curRowInput->header = NULL;
                    curRowInput->element = NULL;
                    appendHeaderRow(&a, curRowInput);
                    count = 0;
                }
                colInput = malloc(sizeof(struct Header));
                colInput->index = j;
                colInput->header = NULL;
                colInput->element = NULL;
                insertHeaderColumn(&a,colInput);
                appendElementToEnd(curRowInput, colInput,c,i,j);
                j++;
            }
        }
    }
    a.rows = i-1;
    return a;
}

/*insert the header when the next header is greater than it. return 1 if inserted, return 0 if the header already exists*/
int insertHeaderColumn(struct Matrix *a, struct Header *input){
    struct Header *p;
    if(a->headColumnHeader == NULL){
        a->headColumnHeader = input;
    }else{
        for (p = a->headColumnHeader; p->header != NULL; p = p->header){
            if(p->header->index == input ->index){
                free(input);
                input = p;
                return 0;
            }
            if(p->header->index > input->index){
                input->header = p->header;
                p->header = input;
                return 1;
            }
        }
        p->header = input;
    }
    return 1;

}

/* append the header to the end of the headers */
void appendHeaderRow(struct Matrix *a, struct Header *input) {
    struct Header *p;
    if(a->headRowHeader == NULL){
        a->headRowHeader = input;
    }else{
        for (p = a->headRowHeader; p->header != NULL; p = p->header){}
        p->header = input;
    }
}

/* append the element to the end of the elements in the header */
void appendElementToEnd(struct Header *headerRow, struct Header *headerCol, int val, int row, int col) {
    struct Element *p;
    struct Element *input = malloc(sizeof(struct Element));
    input->value = val;
    input->row = row;
    input->column = col;
    input->rowElement = NULL;
    input->columnElement = NULL;
    if(headerRow->element == NULL){
        headerRow->element = input;
    }else{
        for (p = headerRow->element; p->rowElement != NULL; p = p->rowElement) {}
        p->rowElement = input;
    }
    if(headerCol->element == NULL){
        headerCol->element = input;
    }else{
        for (p = headerCol->element; p->columnElement != NULL; p = p->columnElement) {}
        p->columnElement = input;
    }
}

void MTRX_write(struct Matrix *m, char *filename){
    FILE *file = fopen(filename, "w");
    int i, j;
    for(i=1; i <= m ->rows; i++){
        for(j=1; j <= m->columns;j++){
            if(j==m->columns){
                fprintf(file, "%d", MTRX_getElement(m, i, j));
            }else{
                fprintf(file, "%d ", MTRX_getElement(m, i, j));
            }
        } 
        fprintf(file, "%c", '\n');
    }
    fclose(file);
}