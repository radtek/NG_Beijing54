/*
* The author of this software is Steven Fortune.  Copyright (c) 1994 by AT&T
* Bell Laboratories.
* Permission to use, copy, modify, and distribute this software for any
* purpose without fee is hereby granted, provided that this entire notice
* is included in all copies of any software which is or includes a copy
* or modification of this software and in all copies of the supporting
* documentation for such software.
* THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
* WARRANTY.  IN PARTICULAR, NEITHER THE AUTHORS NOR AT&T MAKE ANY
* REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
* OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
*/

/*
* This code was originally written by Stephan Fortune in C code.  I, Shane O'Sullivan,
* have since modified it, encapsulating it in a C++ class and, fixing memory leaks and
* adding accessors to the Voronoi Edges.
* Permission to use, copy, modify, and distribute this software for any
* purpose without fee is hereby granted, provided that this entire notice
* is included in all copies of any software which is or includes a copy
* or modification of this software and in all copies of the supporting
* documentation for such software.
* THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
* WARRANTY.  IN PARTICULAR, NEITHER THE AUTHORS NOR AT&T MAKE ANY
* REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
* OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
*/

#ifndef VORONOI_DIAGRAM_GENERATOR
#define VORONOI_DIAGRAM_GENERATOR

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "CNGPreDefine.h"


#define DELETED -2

#define le 0
#define re 1

using namespace std;




class VoronoiDiagramGenerator
{
public:
	VoronoiDiagramGenerator();
	~VoronoiDiagramGenerator();

	bool generateVoronoi(vector<NGPOINT>& values,double minX, double maxX, double minY, double maxY, double minDist=0);

	void resetIterator()
	{
		iteratorEdges = allEdges;
	}

	bool GetNext(double& x1, double& y1, double& x2, double& y2,int& leftIndex,int& rightIndex)
	{
		if(iteratorEdges == 0)
			return false;

		x1 = iteratorEdges->x1;
		x2 = iteratorEdges->x2;
		y1 = iteratorEdges->y1;
		y2 = iteratorEdges->y2;

		leftIndex = iteratorEdges->leftIndex;
		rightIndex=iteratorEdges->rightIndex;
		iteratorEdges = iteratorEdges->next;

		return true;
	}

	bool GetNext(NGPOINT& begin,NGPOINT& end, int& leftIndex,int& rightIndex){
		if(iteratorEdges == 0)
			return false;
		begin.x = iteratorEdges->x1;
		begin.y = iteratorEdges->y1;
		end.x = iteratorEdges->x2;
		end.y = iteratorEdges->y2;
		leftIndex = iteratorEdges->leftIndex;
		rightIndex = iteratorEdges->rightIndex;
		iteratorEdges = iteratorEdges->next;
		return true;
	}
	int GetEdgeNum(){return  edgeNum;}


private:
	void cleanup();
	void cleanupEdges();
	char *getfree(struct Freelist *fl);
	struct	Halfedge *PQfind();
	int PQempty();



	struct	Halfedge **ELhash;
	struct	Halfedge *HEcreate(), *ELleft(), *ELright(), *ELleftbnd();
	struct	Halfedge *HEcreate(struct Edge *e,int pm);


	struct NGPOINT PQ_min();
	struct Halfedge *PQextractmin();
	void freeinit(struct Freelist *fl,int size);
	void makefree(struct Freenode *curr,struct Freelist *fl);
	void geominit();
	void plotinit();
	bool voronoi(int triangulate);
	void ref(struct Site *v);
	void deref(struct Site *v);
	void endpoint(struct Edge *e,int lr,struct Site * s);

	void ELdelete(struct Halfedge *he);
	struct Halfedge *ELleftbnd(struct NGPOINT *p);
	struct Halfedge *ELright(struct Halfedge *he);
	void makevertex(struct Site *v);
	void out_triple(struct Site *s1, struct Site *s2,struct Site * s3);

	void PQinsert(struct Halfedge *he,struct Site * v, float offset);
	void PQdelete(struct Halfedge *he);
	bool ELinitialize();
	void ELinsert(struct	Halfedge *lb, struct Halfedge *newHe);
	struct Halfedge * ELgethash(int b);
	struct Halfedge *ELleft(struct Halfedge *he);
	struct Site *leftreg(struct Halfedge *he);
	void out_site(struct Site *s);
	bool PQinitialize();
	int PQbucket(struct Halfedge *he);
	void clip_line(struct Edge *e);
	char *myalloc(unsigned n);
	int right_of(struct Halfedge *el,struct NGPOINT *p);

	struct Site *rightreg(struct Halfedge *he);
	struct Edge *bisect(struct	Site *s1,struct	Site *s2);
	float dist(struct Site *s,struct Site *t);
	struct Site *intersect(struct Halfedge *el1, struct Halfedge *el2, struct NGPOINT *p=0);

	void out_bisector(struct Edge *e);
	void out_ep(struct Edge *e);
	void out_vertex(struct Site *v);
	struct Site *nextone();

	void pushGraphEdge(double x1, double y1, double x2, double y2,int leftIndex,int rightIndex);

	void openpl();
	void line(double x1, double y1, double x2, double y2,int leftIndex,int rightIndex);
	void circle(double x, double y, double radius);
	void range(double minX, double minY, double maxX, double maxY);


	struct  Freelist	hfl;
	struct	Halfedge *ELleftend, *ELrightend;
	int 	ELhashsize;

	int		triangulate, sorted, plot, debug;
	double	xmin, xmax, ymin, ymax, deltax, deltay;

	struct	Site	*sites;
	int		nsites;
	int		siteidx;
	int		sqrt_nsites;
	int		nvertices;
	int       edgeNum;
	struct 	Freelist sfl;
	struct	Site	*bottomsite;

	int		nedges;
	struct	Freelist efl;
	int		PQhashsize;
	struct	Halfedge *PQhash;
	int		PQcount;
	int		PQmin;

	int		ntry, totalsearch;
	double	pxmin, pxmax, pymin, pymax, cradius;
	int		total_alloc;

	double borderMinX, borderMaxX, borderMinY, borderMaxY;

	FreeNodeArrayList* allMemoryList;
	FreeNodeArrayList* currentMemoryBlock;

	GraphEdge* allEdges;
	GraphEdge* iteratorEdges;

	double minDistanceBetweenSites;

};

int scomp(const void *p1,const void *p2);


#endif


