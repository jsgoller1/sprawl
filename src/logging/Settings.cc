#include "Logging.hh"

static bool showTime = true;
void Logging::setShowTime(const bool& setting) { showTime = setting; }
bool Logging::getShowTime() { return showTime; }

static bool showLogLevel = true;
void Logging::setShowLogLevel(const bool& setting) { showLogLevel = setting; }
bool Logging::getShowLogLevel() { return showLogLevel; }

static bool showSubsystemName = true;
void Logging::setShowSubsystemName(const bool& setting) { showSubsystemName = setting; }
bool Logging::getShowSubsystemName() { return showSubsystemName; }

static bool showEntityName = true;
void Logging::setShowEntityName(const bool& setting) { showEntityName = setting; }
bool Logging::getShowEntityName() { return showEntityName; }

static bool showFile = true;
void Logging::setShowFile(const bool& setting) { showFile = setting; }
bool Logging::getShowFile() { return showFile; }

static bool showFuncName = true;
void Logging::setShowFuncName(const bool& setting) { showFuncName = setting; }
bool Logging::getShowFuncName() { return showFuncName; }

static bool useColor = true;
void Logging::setColorUse(const bool& setting) { useColor = setting; }
bool Logging::getColorUse() { return useColor; }
