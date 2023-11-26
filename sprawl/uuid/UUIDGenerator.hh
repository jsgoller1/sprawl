#pragma once
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <boost/uuid/uuid_generators.hpp>
#pragma clang diagnostic pop

#include <string>

#include "Singleton.hh"
#include "Types.hh"

class UUIDGenerator : public Singleton<UUIDGenerator> {
 public:
  UUID generate();

 private:
  friend Singleton<UUIDGenerator>;

  UUIDGenerator() = default;
  UUIDGenerator(const UUIDGenerator&) = delete;
  UUIDGenerator& operator=(const UUIDGenerator&) = delete;
  UUIDGenerator(UUIDGenerator&&) = delete;
  UUIDGenerator& operator=(UUIDGenerator&&) = delete;

  boost::uuids::random_generator generator;
};
