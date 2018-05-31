#ifndef KMEANS_H
#define KMEANS_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

ifstream infile;
ofstream outfile;

double x[1000], y[1000], assignedto[1000];
double centroidx[10], centroidy[10];
double oldcentroidx[10], oldcentroidy[10];
int k = 2;				// k = number of centroids
int centroidcount[10];
int dataCount = 0;

double calculateDistance(double x, double y, double x1, double y1);
void assignCentroid(double x, double y, int point);
void calculateNewCentroid();

void k_means();

#endif // KMEANS_H
