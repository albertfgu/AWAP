#include <cstdio>
#include <iostream>
#include <sstream>
#include "game.h"
#include <unistd.h>

/*
  game.cpp - Responsible for generating moves to give to client.py
  Moves via stdout in the form of "# # # #" (block index, # rotations, x, y)
  Important function is find_move, which should contain the main AI.
*/


/* Returns a Move, defined in game.h as
   struct Move{
     int index;
     int rotations;
     int x;
     int y;
   }
 */

const int INF = 1<<30;

Move Game::find_move()
{
  int best_score = -INF;
  Move best_move = {0, 0, 0, 0};
  for (int x = 0; x < dimension; x++) {
    for (int y = 0; y < dimension; y++) {
      for (int rot = 0; rot < 4; rot++) {
        for (int i = 0; i < blocks.size(); i++) {
          block b = blocks[my_number][i];
          block bb = rotate_block(b, rot);
          if (can_place(bb, Point(x, y))) {
              int new_score = score_move(bb, Point(x, y));
            if (new_score > best_score) {
                Move new_move = {i, rot, x, y};
                best_move = new_move;
                best_score = new_score;
            }
          }
        }
      }
    }
  }

  num_turns++;

  if (best_score == -INF)
      sleep(5000);

  return best_move;
}

bool Game::my_turn()
{
  return turn == my_number;
}


void Game::interpret_data(args args)
{
  my_number = args.my_number;
  dimension = args.dimension;
  turn = args.turn;
  blocks = args.blocks;
  grid = args.grid;
  bonus_squares = args.bonus_squares;
}



bool Game::can_place(block b, Point p)
{
  bool onAbsCorner = false;
  bool onRelCorner = false;
  int N = dimension - 1;

  Point corners[4] = { Point(0,0), Point(N, 0), Point(0, N), Point(N, N) };
  Point corner = corners[my_number];
  for(int i = 0; i < b.size(); i++){
    Point q = b[i].add(p);
    int x = q.x;
    int y = q.y;
    if (x > N || x < 0 || y < 0 || y > N || grid[x][y] >= 0
        || grid[x][y] == -2
        || (x > 0 && grid[x-1][y] == my_number)
        || (y > 0 && grid[x][y-1] == my_number)
        || (x < N && grid[x+1][y] == my_number)
        || (y < N && grid[x][y+1] == my_number)) {
      return false;
    }

    onAbsCorner = onAbsCorner || q.eq(corner);
    onRelCorner = onRelCorner
      || (x > 0 && y > 0 && grid[x-1][y-1] == my_number)
      || (x < N && y > 0 && grid[x+1][y-1] == my_number)
      || (x > 0 && y < N && grid[x-1][y+1] == my_number)
      || (x < N && y < N && grid[x+1][y+1] == my_number);
  }

  return grid[corner.x][corner.y] < 0 ? onAbsCorner : onRelCorner;
}


block Game::rotate_block(block b, int num_rotations)
{
  block newBlock;
  for(int i = 0; i < b.size(); i++){
    newBlock.push_back(b[i].rotate(num_rotations));
  }
  return newBlock;
}

void Game::mark(vector<vector<bool> > & marked, int player, int x, int y) {
    const int dist = 4;
    for (int i = -dist; i <= dist; i++) {
        for (int j = -dist; j <= dist; j++) {
            if (0 <= i && i < dimension
                    && 0 <= j && j < dimension) {
                if (grid[i][j] == -1) marked[i][j] = true;
            }
        }
    }
}


//Currently returns 0, you might want to modify this yourself!
int Game::score_move(block b, Point p)
{
  int blockSize = b.size();
  int bonus_points = 1;
  int N = dimension;
  int dist = 10*N;

  for(int i = 0; i < blockSize; i++){
    Point s = b[i].add(p);
    for(int j = 0; j < bonus_squares.size(); j++){
      if(s.eq(bonus_squares[j])){
        bonus_points = 3;
      }
      //area_enclosed = max(area_enclosed, -1 * (s.distance(Point(N/2, N/2))));
    }
      dist = min(dist, s.distance(Point(N/2, N/2)));
  }

  // Archit's space heuristic
  vector<vector<bool> > marked(N, vector<bool>(N, false));
  int score[4];
  for (int p = 0; p < 4; p++) {
      for (int i = 0; i < N; i++) {
          for (int j = 0; j < N; j++) {
              if (grid[i][j] == p)
                  mark(marked, p, i, j);
          }
      }
      score[p] = 0;
      for (int i = 0; i < N; i++) {
          for (int j = 0; j < N; j++) {
              score[p] += (marked[i][j] ? 1 : 0);
          }
      }
  }

  int piece_score = bonus_points * blockSize;

  int space_score = 4*score[my_number] - (score[0] + score[1] + score[2] + score[3]);

  int final_score;
  if (num_turns <= 4) {
      //final_score = space_score - 4*dist;
      final_score = -dist;
  }
  else if (num_turns <= 8) {
      final_score = 2*space_score - dist + piece_score;
  }
  else {
      final_score = blockSize * piece_score;
  }

  return final_score;
          

  //return bonus_points * blockSize * blockSize - dist;
  //return bonus_points * blockSize;

}

string Game::toString(Move m)
{
  stringstream ss;
  ss << m.index << " " << m.rotations << " " << m.x << " " << m.y;
  return ss.str();
}

void Game::debug(string s)
{
  std::cout << "DEBUG " << s << "\n";
}
