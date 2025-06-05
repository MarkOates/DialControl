

#include <Timeline/JSONLoaders/Timeline/Keyframe.hpp>


namespace Timeline
{


void to_json(nlohmann::json& j, const Keyframe& v)
{
   j = nlohmann::json{
      { "time", v.time },
      { "value", v.value },
      //{ "interpolator_func", v.interpolator_func },
      { "focused", v.focused },
   };
}

void from_json(const nlohmann::json& j, Keyframe& v)
{
   j.at("time").get_to(v.time);
   j.at("value").get_to(v.value);
   j.at("focused").get_to(v.focused);
}


} // namespace Timeline



