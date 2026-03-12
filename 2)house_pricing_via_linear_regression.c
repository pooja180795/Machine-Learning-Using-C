#include <stdio.h>
#include<math.h>

// Function prototype for training linear regression model
void train_model(float x[], float y[], int m);

int main()
{
    int m = 50;   // Number of training examples

    // Input feature values (independent variable)
    float x[] = {
        20 ,30 ,40 ,50 ,100, 105, 110, 107, 112, 120,
        125,130, 140, 150, 155, 165, 175, 185, 190, 200, 
        205, 215, 225, 227, 230, 250, 270, 275, 290, 300, 
        400, 415, 417, 435, 445, 450, 475, 480, 490, 500, 
        600, 602, 607, 615, 625, 630, 635, 640, 645, 650
    };

    // Output target values (dependent variable)
    float y[] = {
        18, 28, 38, 52, 105, 112, 120, 115, 125, 135,
        145, 155, 165, 175, 182, 198, 210, 225, 235, 250,
        265, 280, 295, 300, 310, 340, 365, 375, 395, 410,
        520, 540, 545, 570, 590, 600, 630, 640, 655, 670,
        780, 790, 805, 820, 840, 855, 870, 885, 900, 920
    };

    // Normalize data to range approximately [0,1]
    // This improves gradient descent stability and convergence speed
    for(int i = 0; i < m; i++)
    {
        x[i] /= 650;   // divide by maximum x value
        y[i] /= 920;   // divide by maximum y value
    }

    // Train linear regression model using gradient descent
    train_model(x, y, m);

    return 0;
}

void train_model(float x[], float y[], int m)
{
    // Initialize parameters:
    // w = slope, b = intercept
    float w = 1, b = 0; 
    float prev_cost = 1000;  
    float tolerance = 0.000001;

    // Array to store predictions for each training example
    float y_hat[m];

    float learning_rate = 0.01;   // Step size for gradient descent

    // Perform 500 iterations of gradient descent
    for(int k = 1; k <= 500; k++)
    {
        float cost_fun = 0;      // Cost (Mean Squared Error)
        float dj_by_dw = 0;      // Gradient w.r.t w
        float dj_by_db = 0;      // Gradient w.r.t b

        // Loop over all training examples
        for(int i = 0; i < m; i++)
        {
            // Linear regression hypothesis function
            // y_hat = w*x + b
            y_hat[i] = w * x[i] + b;

            // Accumulate squared error
            cost_fun += (y_hat[i] - y[i]) * (y_hat[i] - y[i]);

            // Compute partial derivatives
            dj_by_dw += (y_hat[i] - y[i]) * x[i];
            dj_by_db += (y_hat[i] - y[i]);
        }

        // Compute Mean Squared Error cost
        cost_fun = cost_fun / (2 * m);

        // Average gradients
        dj_by_db /= m;
        dj_by_dw /= m;

        // Update parameters using gradient descent rule
        w = w - (learning_rate * dj_by_dw);
        b = b - (learning_rate * dj_by_db);

        // Print iteration number and cost value
        printf("%d %f\n", k, cost_fun);
        if (fabs(prev_cost - cost_fun) < tolerance)
{
    printf("Training converged at iteration %d\n", k);
    break;
}

prev_cost = cost_fun;
    }

    // Open gnuplot process for plotting results
    FILE *gp = popen("gnuplot -persistent", "w");

    // Set x-axis range for normalized data
    fprintf(gp, "set xrange [0:1]\n");

    // Plot training data points and learned regression line
    fprintf(gp,
            "plot '-' with points title 'Data', "
            "%f*x + %f with lines title 'Regression'\n",
            w, b);

    // Send training data points to gnuplot
    for (int i = 0; i < m; i++) {
        fprintf(gp, "%f %f\n", x[i], y[i]);
    }

    // End of inline data for gnuplot
    fprintf(gp, "e\n");

    // Close gnuplot process
    pclose(gp);
}