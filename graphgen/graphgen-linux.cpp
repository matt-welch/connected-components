#include <stdio.h>
#include <fstream>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

#define OUTPUT_FILE     "graph.txt"

typedef std::vector<int> EDGE;

static unsigned int g_nVertices(0);
static double g_fProbThreshold(0.5);

static bool checkArg(int argc, char *argv[])
{
    char *pVertices(NULL), *pProb(NULL);

    if (argc != 3)
    {
        return false;
    }

    pVertices = argv[1];
    pProb = argv[2];
    sscanf(pVertices, "%u", &g_nVertices);
    sscanf(pProb, "%lf", &g_fProbThreshold);

    if (g_nVertices <= 1 || g_fProbThreshold <= 0.0 || g_fProbThreshold >= 1.0)
    {
        return false;
    }
    return true;
}

//MSDN
double rangedRand( int range_min, int range_max)
{
    // Generate random numbers in the half-closed interval
    // [range_min, range_max). In other words,
    // range_min <= random number < range_max
    double prob;
    int rand_val;

    rand_val = rand();
    prob = (double)rand_val / (RAND_MAX ) * (double)(range_max - range_min)
            + range_min;
    return prob;
}


unsigned int DumpSymmetricEdges(const EDGE &edge, string &strEdge)
{
    unsigned int i, edgeCount(0);

    for (i=0; i < edge.size(); i++)
    {
        stringstream ss;
        string temp;

        ss << edge[i];
        ss >> temp;
        strEdge += temp + " ";
    }

    return edge.size();
}

void createEdges(ofstream &fOut)
{
    std::vector<EDGE> vEdges;

    vEdges.resize(g_nVertices);

    fOut << g_nVertices << endl;

    unsigned int i, j;
    string strEdge;
    unsigned int edgeCount(0);
    double prob;

    for (i=1; i <= g_nVertices; i++)
    {
        strEdge.clear();
        edgeCount = 0;

        edgeCount = DumpSymmetricEdges(vEdges[i-1], strEdge);
        for (j=i+1; j <= g_nVertices; j++)
        {
           prob = rangedRand(0,1);
           if (prob <= g_fProbThreshold)
           {
               //create an edge between (i,j)
               stringstream ss;
               string temp;

               edgeCount++;
               ss << j;
               ss >> temp;
               strEdge += temp + " ";

               //make the edge symmetric
               vEdges[j-1].push_back(i);
           }
        }

        fOut << edgeCount << " " << strEdge.c_str() << endl;
    }
}

int main(int argc, char *argv[])
{
    if (checkArg(argc, argv) == false)
    {
        fprintf(stderr, "Usage: %s [vertex_num] [probability]\n\n"
            "  vertex_num       The number of vertices. The index of the vertex \n"
            "                   starts from 1.\n"
            "  probability      The probability that an edge exists between two nodes\n\n"
            "Example: %s 10 0.3\n",
            argv[0], argv[0]);
        return 1;
    }

    srand((unsigned int)time(NULL));

    ofstream fOut(OUTPUT_FILE);
    if (fOut.is_open() == false)
    {
        fprintf(stderr, "Opening the file, %s, was not successful\n",
            OUTPUT_FILE);
        return 1;
    }

    createEdges(fOut);

    printf("Done.\nThe graph file is %s\n", OUTPUT_FILE);
    fOut.close();

	return 0;
}

