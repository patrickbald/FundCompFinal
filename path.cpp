/*
 * Patrick Bald
 * Fundamentals of Computing Fall 2019
 * Final Project
 * 12/12/19
 *
 * A c++, visual implementation of Dijkstra's shortest path algorithm
 *
 */

#include <iostream>
#include "board.h"

using namespace std;

#include "gfx2.h"

void getCoordinates(int&, int&, int&, int&, Board &);
void start(int&, int&, int&, int&, Board &);
void dispInstructions();
void dispScore(int);

int main(){

	bool loop = true;
	char c;
	int distance;
	int startX, startY, endX, endY;

	gfx_open(wd, ht, "Dijkstra's");
	
	cout << " ------------------------------- " << endl;
	cout << "    Welcome to shortest path!    " << endl;
	cout << " ------------------------------- " << endl;

	dispInstructions();
	
	while(loop) {
		c = gfx_wait();
		gfx_clear();
		if(c == ' '){
			Board board;
			board.populate();
			start(startX, startY, endX, endY, board);
			pair<int, int> start = make_pair(startX, startY);
			pair<int, int> end = make_pair(endX, endY);
			distance = board.findPath(start, end); // map < iPair, iPair >
			dispScore(distance);
			cout << "The shortest distance from (" << startX << " , " << startY << ")";
			cout << " to "<< "( " << endX << " , " << endY << " )  is: " << distance << endl;
		} else if(c == 'q')
			break;
	}
	
	return 0;
}

void getCoordinates(int & startX, int & startY, int & endX, int & endY, Board & board){
	char c;

	board.dispWeights();

	c = gfx_wait();
	startX = c - '0';
	c = gfx_wait();
	startY = c - '0';
	gfx_color(0, 255, 0);
	gfx_fill_rectangle(startC + 50*startX - offset, startR + 50*startY - offset, l, l);
	c = gfx_wait();
	endX = c - '0';
	c = gfx_wait();
	endY = c - '0';
	
}

void start(int & startX, int & startY, int & endX, int & endY, Board & board){
	gfx_color(100, 0, 255);
	for(int c = 0; c < BOARDSIZE; c++){
		for(int r = 0; r < BOARDSIZE; r++){
			gfx_fill_rectangle(startC + 50*c - offset, startR + 50*r - offset, l, l);
			gfx_flush();
		}
	}
	
	gfx_color(255, 255, 255);		
	dispInstructions();

	getCoordinates(startX, startY, endX, endY, board);
	gfx_color(255, 0, 0);
	gfx_fill_rectangle(startC + 50*endX - offset, startR + 50*endY - offset, l, l);
	gfx_flush();
}

void dispInstructions(){
	
	gfx_text(250, 100, "Visual representation of Dijkstra's algorithm");
	gfx_text(220, 120, "Press space to build board initially and after every run");
	gfx_text(180, 140, "After building board, enter 4 integers for shortest path coordinates");
	gfx_text(350, 160, "Press Q to exit");
}

void dispScore(int distance){

	char buffer[16];
	sprintf(buffer, "%d", distance);
	gfx_color(255, 255, 255);
	gfx_text(240, 630, "The shortest path from start to finish is: ");
	gfx_text(520, 630, buffer);

}
