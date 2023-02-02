#include "ScoreProxy.hh"

ScoreProxy::ScoreProxy(int* const gameScore) : _gameScore(gameScore) {}
void ScoreProxy::addScore(const int addedAmount) { (*this->_gameScore) += addedAmount; }
