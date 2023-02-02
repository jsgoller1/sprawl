#pragma once

class ScoreProxy {
 public:
  ScoreProxy(int* const gameScore);
  void addScore(const int addedAmount);

 private:
  int* const _gameScore;
};
