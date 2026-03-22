#include <math.h>

double sigmoid(double z)
{
    return 1.0 / (1.0 + exp(-z));
}

double dot_product(double *weights, double *features, int n)
{
    double sum = 0;

    for(int i = 0; i < n; i++)
    {
        sum += weights[i] * features[i];
    }

    return sum;
}

double predict(double *weights, double *features, int n, double bias)
{
    double z = dot_product(weights, features, n) + bias;
    return sigmoid(z);
}   

void train(double X[][3], int y[], double *weights,
           double *bias, int samples, int features,
           double lr, int epochs)
{
    for(int e = 0; e < epochs; e++)
    {
        for(int i = 0; i < samples; i++)
        {
            double prediction = predict(weights, X[i], features, *bias);

            double error = prediction - y[i];

            for(int j = 0; j < features; j++)
            {
                weights[j] -= lr * error * X[i][j];
            }

            *bias -= lr * error;
        }
    }
}