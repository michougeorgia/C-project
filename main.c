#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool inOpenInterval(int *a, int lo, int hi)
{
    return *a > lo && *a < hi;
}

int** readFile(FILE* input, int* r)
{
    int** data = 0;

    int col = 0, t;
    while(fscanf(input, "%d", &t) != EOF)
    {
        if(!inOpenInterval(&t, 0, 50)){
            printf("Wrong Input!\n");
            return 0;
        }

        if(col == 0)
        {
            data = (int**) realloc(data, (*r + 1) * sizeof(*data));
            data[*r] = (int*) malloc(7 * sizeof(int));
            (*r)++;
        }

        data[*r - 1][col] = t;

        col = (col + 1) % 7;
    }

    return data;
}


int* metric0(int** data, int r, int c)
{
    int* f = (int*) calloc(50, sizeof(int));

    f[0] = -1;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            f[data[i][j]]++;
        }
    }

    return f;
}


int* metric1(int** data, int r, int c)
{
    int* d = (int*) malloc(50 * sizeof(int));

    d[0] = -1;
    for(int i = 1; i < 50; i++) d[i] = r;

    for(int i = r - 1; i >= 0; i--)
    {
        for(int j = 0; j < c; j++)
        {
            d[data[i][j]] = i;
        }
    }

    return d;
}

int* metric2(int** data, int r, int c)
{
    int* res = (int*) malloc(50 * sizeof(int));
    int *f = metric0(data, r, c);
    int *d = metric1(data, r, c);

    for(int i = 0; i < 50; i++) res[i] = f[i] + d[i];

    return res;
}

float* metric3(int** data, int r, int c)
{
    float *res = (float*) malloc(50 * sizeof(float));
    int *f = metric0(data, r, c);
    int *d = metric1(data, r, c);

    float mn;

    for(int i = 1; i < 50; i++) {
        res[i] = ((f[i] == 0) ? 0.0 : (float) d[i] - (float) r / f[i]);

        if(i == 1) mn = res[i];
        else {
            if(mn > res[i])
                mn = res[i];
        }
    }
    res[0] = mn - 1.0;

    return res;
}

void sortInt(int* a, int* idx)
{
    int temp;
    for(int i = 0; i < 49; i++)
    {

        for(int j = 49; j > i; j--)
        {
            if(a[j] > a[j - 1])
            {
                temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;

                temp = idx[j];
                idx[j] = idx[j - 1];
                idx[j - 1] = temp;
            }
            if(a[j] == a[j - 1] && idx[j] < idx[j - 1])
            {
                temp = idx[j];
                idx[j] = idx[j - 1];
                idx[j - 1] = temp;
            }
        }
    }
}

void sortFloat(float* a, int* idx)
{
    int tempi;
    float tempf;
    for(int i = 0; i < 49; i++)
    {

        for(int j = 49; j > i; j--)
        {
            if(a[j] > a[j - 1])
            {
                tempf = a[j];
                a[j] = a[j - 1];
                a[j - 1] = tempf;

                tempi = idx[j];
                idx[j] = idx[j - 1];
                idx[j - 1] = tempi;
            }
            if(a[j] == a[j - 1] && idx[j] < idx[j - 1])
            {
                tempi = idx[j];
                idx[j] = idx[j - 1];
                idx[j - 1] = tempi;
            }
        }
    }
}

int main()
{
    int numbers, metric;
    scanf("%d %d", &numbers, &metric);

    if(!inOpenInterval(&numbers, 0, 50) || !inOpenInterval(&metric, -1, 4)) {
        printf("Wrong Input!\n");
        return 0;
    }

    char file[100];
    scanf("%s", file);

    FILE* input = fopen(file, "r");

    if(!input){
        printf("File Error!", file);
        return 0;
    }

    int r = 0, c = 7;
    int **data = readFile(input, &r);

    if(!data)
    {
        return 0;
    }

    int idx[50];
    for(int i = 0; i < 50; i++)
        idx[i] = i;

    if(metric == 0){
        int *res = metric0(data, r, c);
        sortInt(res, idx);
        for(int i = 0; i < numbers; i++){
            printf("%d ", idx[i]);
        }
    } else if (metric == 1) {
        int *res = metric1(data, r, c);
        sortInt(res, idx);
        for(int i = 0; i < numbers; i++){
            printf("%d ", idx[i]);
        }
    } else if (metric == 2) {
        int *res = metric2(data, r, c);
        sortInt(res, idx);
        for(int i = 0; i < numbers; i++){
            printf("%d ", idx[i]);
        }
    } else {
        float *res = metric3(data, r, c);
        sortFloat(res, idx);
        for(int i = 0; i < numbers; i++){
            printf("%d ", idx[i]);
        }
    }

    puts("");

    return 0;
}
