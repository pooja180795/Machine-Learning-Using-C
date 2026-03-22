#include <stdio.h>
void train(double X[][3], int y[], double *weights,
           double *bias, int samples, int features,
           double lr, int epochs);
double predict(double *weights, double *features, int n, double bias);
double dot_product(double *weights, double *features, int n);
int main() 
{
    int samples = 4;
    int features = 3;

    double X[4][3] = {
        {1,0,1},
        {0,1,0},
        {1,1,1},
        {0,0,1}
    };

    int y[4] = {1,0,1,0};

    double weights[3] = {0,0,0};
    double bias = 0;

    train(X, y, weights, &bias, samples, features, 0.01, 1000);

    double email[3] = {1,1,1};

    double result = predict(weights, email, features, bias);

    //printf("Spam probability: %f\n", result);
    printf("%f", bias);

    if(result >= 0.5)
        printf("Spam\n");
    else
        printf("Not Spam\n");

    return 0;
}