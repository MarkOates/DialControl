#pragma once


#include <lib/nlohmann/json.hpp>
#include <Timeline/Keyframe.hpp>


namespace Timeline
{
  void to_json(nlohmann::json& j, const Keyframe& object);
  void from_json(const nlohmann::json& j, Keyframe& object);
}


