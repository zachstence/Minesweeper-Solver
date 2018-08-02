#include <vector>
#include <set>
#include <utility>
#include <ctype.h>
#include <iostream>

using std::vector;
using std::set;
using std::pair;
using std::cout;
using std::endl;

///////////////// MAKE PMV LATER OR MOVE TO PROTECTED IN BASE CLASS?

const char HIDDEN = '*';

using CellSet = set<pair<int, int>>;

CellSet getHiddenAdj(vector<vector<char>> board, int r, int c) {
  CellSet hiddenAdj;
  for (int rOffset = -1; rOffset <= 1; rOffset++) {
    for (int cOffset = -1; cOffset <= 1; cOffset++) {
      int adjR = r + rOffset;
      int adjC = c + cOffset;
      // skip if off board
      if (adjR < 0 || adjR > board.size() - 1 || adjC < 0
          || adjC > board[0].size() - 1 || board[adjR][adjC] != HIDDEN)
        continue;
      else {
        hiddenAdj.insert({adjR, adjC});
      }
    }
  }
  return hiddenAdj;
}

CellSet findBombs(vector<vector<char>> board) {
  CellSet bombSet;
  for (int r = 0; r < board.size(); r++) {
    for (int c = 0; c < board[0].size(); c++) {
      char cell = board[r][c];

      if (isdigit(cell)) {
        int cellNum = cell - '0';
        CellSet hiddenAdj = getHiddenAdj(board, r, c);
        if (cellNum == hiddenAdj.size()) {
          bombSet.insert(hiddenAdj.begin(), hiddenAdj.end());
        }
      }
    }
  }
  return bombSet;
}