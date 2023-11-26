#pragma once

template <typename T>
class Singleton {
  /*
   * Reusable template class for Singleton behavior.
   */

 public:
  static T& instance() {
    static T instance;
    return instance;
  }

 protected:
  Singleton() = default;

 private:
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
};
