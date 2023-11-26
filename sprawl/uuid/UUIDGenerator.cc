#include "UUIDGenerator.hh"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#pragma clang diagnostic pop

#include <string>

UUID UUIDGenerator::generate() { return boost::uuids::to_string(this->generator()); }
