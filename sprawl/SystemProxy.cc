#include "SystemProxy.hh"

SystemProxy::SystemProxy() = default;

void SystemProxy::quit() { this->_quit = true; }
bool SystemProxy::getQuit() const { return this->_quit; }
