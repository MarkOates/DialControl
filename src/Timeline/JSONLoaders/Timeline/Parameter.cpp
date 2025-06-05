

#include <Timeline/JSONLoaders/Timeline/Parameter.hpp>
#include <Timeline/JSONLoaders/Timeline/Keyframe.hpp>


namespace Timeline
{


void to_json(nlohmann::json& j, const Parameter& v)
{
   j = nlohmann::json{
      { "name", v.name },
      { "initial_value", v.initial_value },
      { "keyframes", v.keyframes },
      { "has_min_value", v.has_min_value },
      { "has_max_value", v.has_max_value },
      { "min_value", v.min_value },
      { "max_value", v.max_value },
   };
}

void from_json(const nlohmann::json& j, Parameter& v)
{
   j.at("name").get_to(v.name);
   j.at("initial_value").get_to(v.initial_value);
   j.at("keyframes").get_to(v.keyframes);
   j.at("has_min_value").get_to(v.has_min_value);
   j.at("has_max_value").get_to(v.has_max_value);
   j.at("min_value").get_to(v.min_value);
   j.at("max_value").get_to(v.max_value);
}


} // namespace Timeline



