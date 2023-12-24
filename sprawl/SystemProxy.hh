#pragma once

#include "Singleton.hh"

class SystemProxy : public Singleton<SystemProxy> {
 public:
  void quit();
  bool getQuit() const;

 private:
  friend Singleton<SystemProxy>;

  bool _quit = false;

  SystemProxy();
  SystemProxy(const SystemProxy&) = delete;
  SystemProxy& operator=(const SystemProxy&) = delete;
};
