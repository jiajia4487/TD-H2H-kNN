/*
	Author: Dan He
	Email: d.he@uq.edu.au
	Date: 14/08/2018
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cilk/cilk.h>
#include <sys/time.h>

#include"Graph.h"
#include"Grid.h"
#include"Point.h"
#include"MBR.h"
#include"Model.h"
#include"TwoHop.h"

using namespace std;

clock_t ct;
int main()
{
//	srand(time(0));
	Graph* graph = new Graph();
	Grid* grid = new Grid();
	TwoHop* twoHop = new TwoHop();
	vector<Point> pointList;
	//添加：手动输入近邻查询的个数 K，和查询点 source 
	int source,k,t, NUM;

	
	//调用 twoHopKNN，参数result 
	vector<int> h2hList(k);
	if(DATA == 0 || DATA == 6)
	{
	        cout<<"read finish1!"<<endl;
                NUMPOINT = 32527;
                NUM = 3;
	        pointList = graph->readNodeCoordinate("./node32527.txt", NUMPOINT);
	        cout<<"read finish2!"<<endl;
	}
	else if(DATA == 1 || DATA ==5){
                NUMPOINT = 66581;
                NUM = 6;
                pointList = graph->readNodeCoordinate("./node66581.txt", NUMPOINT);
        }
	else if(DATA == 2 || DATA ==4){
                NUMPOINT = 134064;
                NUM = 13;
                pointList = graph->readNodeCoordinate("./node134064.txt", NUMPOINT);
		//NUMPOINT = 12832;
		//pointList = graph->readNodeCoordinate("./road-BJ-zone1", NUMPOINT);
	}
	else if(DATA == 3){
                NUMPOINT = 264346;
                NUM = 26;
                pointList = graph->readNodeCoordinate("./road-NY", NUMPOINT);
	}
       else if(DATA == 7)
	{
	        cout<<"read finish1!"<<endl;
                NUMPOINT = 207;
                NUM = 2;
	        pointList = graph->readNodeCoordinate("./Odnode207.txt", NUMPOINT);
	        cout<<"read finish2!"<<endl;
	}
	//生成移动对象集合 
	clock_t start1 = clock();
	initGLADkNN(graph, &pointList, grid, twoHop);
	cout << "initGLADkNN time: " << (double)(clock() - start1) / CLOCKS_PER_SEC << endl;
	//调用twoHopKNN，通过网格索引确定候选集的过程 
	ofstream out1;
	string testfile = "./test.txt";
	out1.open(testfile, ios_base::out);

ifstream out("querytest6.txt"); 

	for(int i=0; i<100;i++)
	{
		
     	cout<<endl; 
    	// cout<<"source: ";
    //	cin>>source;
    	
        clock_t start2 = clock();
      	/*cout<<"k: ";
    	cin>>k;
    	cout<<endl; 
    	clock_t start2 = clock();*/
    	double h2ht = 0;
    	int onum = 0;
    	
    	//for(int j=0;j<10000;j++)
    	{
           cout<<"k: ";
	   cin>>k;
           cout<<"source: ";
           cin>>source;
           cout<<"Query time: ";
    	   cin>>t;
         	cout<<"source = "<<source<<endl;
//cout<<"source = "<<source<<endl;
	twoHopKNN(twoHop, graph, grid, &pointList, k, t, source, &h2hList);
        	//h2ht+=h2htime;
//	onum+=osnum;	
        }
    //cout<<"H2Ht: "<<h2ht<<endl;
    cout<<"Onum: "<<computenum<<" "<<pcomputenum<<endl;
   // cout<<"compute: "<<compute<<endl;
    //cout<<"anum: "<<anum<<endl;
    //cout<<"cnum: "<<cnum<<endl;
    cout<<"LBgraph prune num: "<<minynum<<endl;
    cout<<"prune: "<<prune<<" "<<noprune<<endl;
    cout << "twoHopKNN time: " << (double)(clock() - start2) / CLOCKS_PER_SEC << endl;
    computenum = 0;
    pcomputenum = 0;
    compute = 0;
    minynum = 0;
    prune = 0;
    noprune = 0;
   }
	CELLEDGE = grid->colLength;

	vector<int> query(QUERY_SIZE);
	generateQueryListUniform(QUERY_SIZE, &query);
	return 0;
}


