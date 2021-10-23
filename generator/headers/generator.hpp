#ifndef GENERATOR_H
#define GENERATOR_H

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int int64_t

#define uppercase_alphabets "ABCDEFGDHIJKLMNOPQRSTUVWXYZ"
#define lowercase_alphabets "abcdefghijklmnopqrstuvwxyz"
#define digits "0123456789"
#define brackets "(){}[]"

int rnd(int l = 0, int r = 1e9);

vector<int> generateVector(int n = 5, int l = 1, int r = 10);

vector<int> generateUniqueVector(int n = 5, int l = 1, int r = 10);

string generateString(int n = 5, const string &chars = lowercase_alphabets);

void shuffleEdges(vector<pair<int, int>> &edges, bool undir = true);

// exp: 1 - 4 - 3 - 5 - 2
vector<pair<int, int>> generateRopeGraph(int n = 5, bool undir = true);

vector<pair<int, int>> generateStarGraph(int n = 5, bool undir = true);

// undirected graph with no self loops
vector<pair<int, int>> generateUndirectedGraph(int n = 5);

// directed graph with no self loops
vector<pair<int, int>> generateDirectedGraph(int n = 5);

vector<pair<int, int>> generateTree(int n = 5);

// tree + some random edges
vector<pair<int, int>> generateConnectedGraph(int n = 5);

#undef endl
#undef int

#endif
