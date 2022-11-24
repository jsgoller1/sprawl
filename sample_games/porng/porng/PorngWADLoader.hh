#pragma once

#include <memory>

#include "Ball.hh"
#include "Net.hh"
#include "Paddle.hh"
#include "PorngWorld.hh"
#include "WADLoader.hh"

class PorngWADLoader : public WADLoader {
 public:
  PorngWADLoader(const FilePath& wadPath);
  ~PorngWADLoader() override;
  std::shared_ptr<PorngWorld> loadPorngWorld() const;

 private:
  void loadBall(PorngWorld& world, const nlohmann::json& jsonBody) const;
  void loadNet(PorngWorld& world, const nlohmann::json& jsonBody) const;
  void loadPaddle(PorngWorld& world, const nlohmann::json& jsonBody) const;
};
