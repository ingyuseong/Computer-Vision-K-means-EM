#include "wl.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

// Input Parameters
#define MAX 1005
#define NUM_CLUSTERS 2
#define WIDTH 720
#define HEIGHT 560

int centroid[8];
float color[8];
int cluster[MAX][MAX];
CharImage Input("KU.raw", WIDTH, HEIGHT); 


// Make sure there is no duplicated centroid -> strictly keep the number of clusters
bool IsDuplicated(int target, int index) {
  bool dup = false;
  for (int i = 0; i < index; i++) {
    if (target == centroid[i]) {
      dup = true;
      break;
    }
  }

  return dup;
}


// Randomly initialize each centroid
void InitCentroid() {
  for (int i = 0; i < NUM_CLUSTERS; i++) {
    int init_centroid;
    while (true) {
      init_centroid = rand() % 256;
      if (!IsDuplicated(init_centroid, i)) {
        break;
      }
    }

    centroid[i] = init_centroid;
  }
}


// Find the closest cluster
int FindCluster(int target) {
  int distance, min_cluster, min_distance = MAX;

  for (int i = 0; i < NUM_CLUSTERS; i++) {
    distance = abs(target - centroid[i]);

    if (distance < min_distance) {
      min_distance = distance;
      min_cluster = i + 1;
    }
  }

  return min_cluster;
}


// Assign the closest cluster to each pixel 
bool AssignCluster() {
  int closest_cluster;
  bool same = true;

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      closest_cluster = FindCluster(Input.pixel(x, y));
      if (!(cluster[x][y] == closest_cluster))
        same = false;
      cluster[x][y] = closest_cluster;
    }
  }

  return same;
}


// Calculate cost: L1 norm
float CalcCost() {
  float total_sum = 0, total_size = 0;
  float total_mean;

  for (int i = 0; i < NUM_CLUSTERS; i++) {
    int sum_norm = 0, size_cluster = 0;
    for (int x = 0; x < WIDTH; x++) {
      for (int y = 0; y < HEIGHT; y++) {
        if (cluster[x][y] == i + 1) {
          sum_norm += abs(centroid[i] - Input.pixel(x, y));
          size_cluster++;
        }
      }
    }
    total_sum += sum_norm;
    total_size += size_cluster;
  }

  total_mean = (float) total_sum / (float) total_size;
  return total_mean;
}


// Find Next Centroid that minimize the L1 norm cost - Median(approximated by nearest mean value)
int FindNextCentroid(int target_cluster) {
  float mean_cluster, distance;
  float min_distance = (float) MAX;
  int next_centroid = centroid[target_cluster - 1];
  int sum_cluster = 0, size_cluster = 0;

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      if (cluster[x][y] == target_cluster) {
        sum_cluster += Input.pixel(x, y);
        size_cluster++;
      }
    }
  }

  mean_cluster = (float) ((float) sum_cluster / (float) size_cluster);

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      if (cluster[x][y] == target_cluster) {
        distance = abs(Input.pixel(x, y) - mean_cluster);
        if (distance < min_distance) {
          min_distance = distance;
          next_centroid = Input.pixel(x, y);
        }
      }
    }
  }

  return next_centroid;
}


// Update centroid to the value that minimize the cost function
void UpdateCentroid() {
  int next_centroid;

  for (int i = 0; i < NUM_CLUSTERS; i++) {
    next_centroid = FindNextCentroid(i + 1);
    centroid[i] = next_centroid;
  }
}


// Print Centroid (for debugging)
void PrintCentroid() {
  for (int i = 0; i < NUM_CLUSTERS; i++) {
    printf("%d ", centroid[i]);
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


// Color the input image to averge gray level of corresponding cluster
void Coloring() {
  for (int i = 0; i < NUM_CLUSTERS; i++) {
    int sum_cluster = 0, size_cluster = 0;
    float mean_cluster;

    for (int x = 0; x < WIDTH; x++) {
      for (int y = 0; y < HEIGHT; y++) {
        if (cluster[x][y] == i + 1) {
          sum_cluster += Input.pixel(x, y);
          size_cluster++;
        }
      }
    }
    
    mean_cluster = (float) ((float) sum_cluster / (float) size_cluster);
    color[i] = mean_cluster;
  }
}

int main(){
  int dx, dy;
  bool same = false;

  // Seed for Random Initialization
  srand(time(0));

  // 1. Randomly Initialize Centroid
  InitCentroid();

  // Iteration for 50 or until the clusting result is converged -> stop.
  for (int k = 0; k < 50; k++) {
    // 2. Assigned each pixel to corressponding cluster (nearest centroid)
    same = AssignCluster();
    printf("Converged: %d\n", same);
    printf("Cost: %f\n", CalcCost());
    // Converged condition - Clustering result is exactly same with previous step
    if (same)
      break;
    // 3. Update centroid
    UpdateCentroid();
  }

  // Color the input image to averge gray level of corresponding cluster
  Coloring();

  // Assign cluster color pixel by pixel
  for(dx=0; dx<WIDTH; dx++) for(dy=0; dy<HEIGHT; dy++)
	  Input.pixel(dx, dy) = color[cluster[dx][dy] - 1];

  // Save as {IMAGE_NAME}_{Algorithm}_{# of clusters}.raw
  Input.Save("KU_kmeans_2.raw");

  return 0;
}