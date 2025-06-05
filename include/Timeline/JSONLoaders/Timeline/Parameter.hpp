#pragma once


#include <lib/nlohmann/json.hpp>
#include <Timeline/Parameter.hpp>


namespace Timeline
{
  void to_json(nlohmann::json& j, const Parameter& object);
  void from_json(const nlohmann::json& j, Parameter& object);
}


