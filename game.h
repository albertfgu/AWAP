#ifndef GAME
#define GAME

#include <vector>
#include "point.h"

using namespace std;

typedef vector<Point> block;

struct Move{
  int index;
  int rotations;
  int x;
  int y;

  //Move(int i, int r, int xx, int yy) : index(i), rotations(r), x(xx), y(yy) {}

};

struct args{
  vector<vector<block> > blocks;
  string url;
  vector<vector<int> > grid;
  vector<Point> bonus_squares;
  int my_number;
  int dimension;
  int turn;
  bool has_error;
  string error;
};

class Game{
 public:
  Game() {
      num_turns = 0;

      /*
      Point b1[] = {Point(0, 0), Point(1, 0), Point(2, 0), Point(3, 0), Point(1, 1)}; // line with a tumor
      BLOCKS.push_back(vector<Point>(b1, b1 + 5));

      Point b2[] = {Point(0, 0), Point(-1, 0), Point(0, -1), Point(1, 0), Point(0, 1)}; // plus sign
      BLOCKS.push_back(vector<Point>(b2, b2 + 5));

      Point b3[] = {Point(0, 0), Point(1, 0), Point(1, 1), Point(1, 2), Point(2, 1)}; // weird dual-elbow 
      BLOCKS.push_back(vector<Point>(b3, b3 + 5));
      Point b4[] = {Point(0, 0), Point(1, 0), Point(0, 1), Point(0, 2), Point(1, 2)}; // corner capper
      BLOCKS.push_back(vector<Point>(b4, b4 + 5));
      Point b5[] = {Point(0, 0), Point(1, 0), Point(1, 1), Point(2, 1), Point(2, 2)}, // staircase 
      BLOCKS.push_back(vector<Point>(b5, b5 + 5));
      Point b6[] = {Point(0, 0), Point(1, 0), Point(0, 1), Point(1, 1), Point(0, 2)}, // chair
      BLOCKS.push_back(vector<Point>(b6, b6 + 5));
      Point b7[] = {Point(0, 0), Point(1, 0), Point(2, 0), Point(3, 0), Point(4, 0)}, // big line
      BLOCKS.push_back(vector<Point>(b7, b7 + 5));
      Point b8[] = {Point(0, 0), Point(0, 1), Point(1, 1), Point(2, 1), Point(2, 2)}, // Z shape
      BLOCKS.push_back(vector<Point>(b8, b8 + 5));
      Point b9[] = {Point(0, 0), Point(1, 0), Point(1, 1), Point(2, 1), Point(3, 1)}, // elongated S
      BLOCKS.push_back(vector<Point>(b9, b9 + 5));
      Point b10[] = {Point(0, 0), Point(1, 0), Point(2, 0), Point(0, 1), Point(0, 2)}, // corner piece
      BLOCKS.push_back(vector<Point>(b10, b10 + 5));
      Point b11[] = {Point(0, 0), Point(1, 0), Point(2, 0), Point(1, 1), Point(1, 2)}, // big T
      BLOCKS.push_back(vector<Point>(b11, b11 + 5));
      Point b12[] = {Point(0, 0), Point(1, 0), Point(2, 0), Point(3, 0), Point(0, 1)}, // big L
      BLOCKS.push_back(vector<Point>(b12, b12 + 5));
      Point b13[] = {Point(0, 0), Point(1, 0), Point(1, 1), Point(2, 1)}} // tetris S
      BLOCKS.push_back(vector<Point>(b13, b13 + 4));
      Point b14[] = {Point(0, 0), Point(0, 1), Point(1, 0), Point(0, 2)}; // little L
      BLOCKS.push_back(vector<Point>(b14, b14 + 4));
      Point b15[] = {Point(0, 0), Point(1, 0), Point(2, 0), Point(3, 0)}; // little line
      BLOCKS.push_back(vector<Point>(b15, b15 + 4));
      Point b16[] = {Point(0, 0), Point(1, 0), Point(2, 0), Point(1, 1)}; // little T
      BLOCKS.push_back(vector<Point>(b16, b16 + 4));
      Point b17[] = {Point(0, 0), Point(0, 1), Point(1, 0), Point(1, 1)}; // square
      BLOCKS.push_back(vector<Point>(b17, b17 + 4));
      Point b18[] = {Point(0, 0), Point(0, 1), Point(0, 2)}; // tiny line
      BLOCKS.push_back(vector<Point>(b18, b18 + 3));
      Point b19[] = {Point(0, 0), Point(0, 1), Point(1, 0)}; // elbow
      BLOCKS.push_back(vector<Point>(b19, b19 + 3));
      Point b20[] = {Point(0, 0), Point(0, 1)}; // double
      BLOCKS.push_back(vector<Point>(b20, b20 + 2));
      Point b21[] = {Point(0, 0)}; // single
      BLOCKS.push_back(vector<Point>(b21, b21 + 1));
      */
  };


  vector<vector<block> > blocks;
  vector<vector<int> > grid;
  vector<Point> bonus_squares;
  int my_number;
  int dimension;
  int turn;



  Move find_move();
  bool my_turn();
  void interpret_data(args args);

 private:
  int area_enclosed;
  bool can_place(block b, Point p);
  block rotate_block(block b, int num_rotations);
  int score_move(block b, Point p);

  string toString(Move m);
  void debug(string s);

  vector<block> BLOCKS;

  int num_turns;

  void mark(vector<vector<bool> > & marked, int player, int x, int y);
  void unmark(vector<vector<bool> > & marked, int player, int x, int y);


};
#endif /* GAME */
