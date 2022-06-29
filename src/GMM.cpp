#include "wl.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

// Input Parameters
#define NUM_CLUSTERS 8
#define WIDTH 800
#define HEIGHT 540

double color[8];
double mu[NUM_CLUSTERS + 1], var[NUM_CLUSTERS + 1], weight[NUM_CLUSTERS + 1];
double prob[WIDTH + 1][HEIGHT + 1][NUM_CLUSTERS + 1];
int cluster[WIDTH + 1][HEIGHT + 1];
CharImage Input("Golf.raw", WIDTH, HEIGHT); 


// Computes the probability density function at point x of the Normal Distribution
double Gaussian(double x, double m, double var, double weight)
{
	return weight / (sqrt(var) * sqrt(2.0 * M_PI)) * exp(-(pow((x - m), 2)/ (2.0 * var)));
}


// Verify do not exist duplicated gaussian distribution
bool IsDuplicated(double target_mu, double target_var, int index) {
  bool dup_mu, dup_var;
  bool dup = false;

  for (int i = 0; i < index; i++) {
    dup_mu = false;
    dup_var = false;

    if (target_mu == mu[i]) {
      dup_mu = true;
    }

    if (target_var == var[i]) {
      dup_var = true;
    }
    
    if (dup_mu && dup_var) {
      dup = true;
      break;
    }
  }

  return dup;
}


// Randomly initialize each Gaussian Parameters
// mean - 0 ~ 255, var - 0 ~ 99
void InitGaussian() {
  for (int i = 0; i < NUM_CLUSTERS; i++) {
    double init_mu, init_var;
    double init_weight = ((double) 1 / (double) NUM_CLUSTERS);
    while (true) {
      init_mu = (double) (rand() % 2560) / (double) 10;
      init_var = (double) (rand() % 100);
      if (!IsDuplicated(init_mu, init_var, i)) {
        break;
      }
    }

    mu[i] = init_mu;
    var[i] = init_var;
    weight[i] = init_weight;
  }
}

// Expectation step - Update each probability by normalized gaussian probability
void UpdateProb() {
  for (int i = 0; i < NUM_CLUSTERS; i++) {
    for (int x = 0; x < WIDTH; x++) {
      for (int y = 0; y < HEIGHT; y++) {
        prob[x][y][i] = Gaussian(Input.pixel(x, y), mu[i], var[i], weight[i]);
      }
    }
  }

  // Normalize -> so that the sum of probabilities of each pixel is 1.
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      double sum_prob = 0;
      for (int i = 0; i < NUM_CLUSTERS; i++)
        sum_prob += prob[x][y][i];

      for (int i = 0; i < NUM_CLUSTERS; i++)
        prob[x][y][i] /= sum_prob;
    }
  }
}


// Maximization step - Update each gaussian parameters by probabilities
void UpdateGaussian() {
  double updated_weight, updated_mu, updated_var;

  for (int i = 0; i < NUM_CLUSTERS; i++) {
    updated_weight = 0;
    updated_mu = 0;
    updated_var = 0;

    for (int x = 0; x < WIDTH; x++) {
      for (int y = 0; y < HEIGHT; y++) {
        updated_weight += prob[x][y][i];
        updated_mu += (double) Input.pixel(x, y) * prob[x][y][i];
        updated_var += (double) pow((double) Input.pixel(x, y) - mu[i], 2) * prob[x][y][i];
      }
    }

    weight[i] = updated_weight / (double) (WIDTH * HEIGHT);
    mu[i] = updated_mu / updated_weight;
    var[i] = updated_var / updated_weight;
  }
}


// Hard Clustering by probability - Pixel by pixel argmax with respect to probability
int FindCluster(int x, int y) {
  double max_prob = 0;
  int arg_max;

  for (int i = 0; i < NUM_CLUSTERS; i++) {
     if (prob[x][y][i] > max_prob) {
       max_prob = prob[x][y][i];
       arg_max = i;
     }
  }

  return arg_max + 1;
}


// Hard Clustering by probability - Assigin cluster that has the highest probability
bool AssignCluster() {
  int highest_prob_cluster;
  bool same = true;

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      highest_prob_cluster = FindCluster(x, y);
      if (!(cluster[x][y] == highest_prob_cluster))
        same = false;
      cluster[x][y] = highest_prob_cluster;
    }
  }

  return same;
}

// Color the input image to averge gray level of corresponding cluster
void Coloring() {
  for (int i = 0; i < NUM_CLUSTERS; i++) {
    int sum_cluster = 0, size_cluster = 0;
    double mean_cluster;

    for (int x = 0; x < WIDTH; x++) {
      for (int y = 0; y < HEIGHT; y++) {
        if (cluster[x][y] == i + 1) {
          sum_cluster += Input.pixel(x, y);
          size_cluster++;
        }
      }
    }
    
    mean_cluster = (double) ((double) sum_cluster / (double) size_cluster);
    color[i] = mean_cluster;
  }
}


// Print Gaussian Parameters (for debugging)
void PrintGaussian() {
  for (int i = 0; i < NUM_CLUSTERS; i++) {
    printf("Gaussian %d: %f x (%f, %f) ", i + 1, weight[i], mu[i], var[i]);
  }
  printf("\n");
}


// Print Strided Cluster (for debugging)
void PrintCluster() {
  for (int x = 0; x < WIDTH; x++) {
    if (x % 10)
      continue;
    for (int y = 0; y < HEIGHT; y++) {
      if (y % 10)
        continue;
      printf("%d ", cluster[x][y]);
    }
    printf("\n");
  }
  printf("**************************  EOF  **************************\n");
}


int main(){
  int dx, dy;
  bool same = false;

  // Seed for Random Initialization
  srand(time(0));

  // 1. Randomly Initialize Gaussian Parameters
  InitGaussian();

  // Iteration for 50 or until the clusting result is converged -> stop.
  for (int k = 0; k < 50; k++) {
    PrintGaussian();
    // 1. Expectation step - Update each probability by normalized gaussian probability
    UpdateProb();
    // Assigned each pixel to corressponding cluster (highest probability)
    same = AssignCluster();
    printf("Converged: %d\n", same);
    // Converged condition - Hard Clustering (by probability) result is exactly same with previous step
    if(same)
      break;
    // 2. Maximization step - Update each gaussian parameters by probabilities
    UpdateGaussian();
  }

  // The final converged parameters, mean, and variance of each Gaussian parameters.
  for (int i = 0; i < NUM_CLUSTERS; i++) {
    printf("*********************** Gaussian %d ***********************\n", i + 1);
    printf("Mixing probability: %f\n", weight[i]);
    printf("Mean: %f\n", mu[i]);
    printf("Variance: %f\n", var[i]);
  }

  // Color the input image to averge gray level of corresponding cluster
  Coloring();

  // Assign cluster color pixel by pixel
  for(dx=0; dx<WIDTH; dx++) for(dy=0; dy<HEIGHT; dy++)
	  Input.pixel(dx, dy) = (int) color[cluster[dx][dy] - 1];

  // Save as {IMAGE_NAME}_{Algorithm}_{# of clusters}.raw
  Input.Save("Golf_em_8.raw");

  return 0;
}