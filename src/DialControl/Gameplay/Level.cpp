

#include <DialControl/Gameplay/Level.hpp>




namespace DialControl
{
namespace Gameplay
{


Level::Level()
   : AllegroFlare::Levels::Base(DialControl::Gameplay::Level::TYPE)
   , title("[unset-title]")
{
}


Level::~Level()
{
}


void Level::set_title(std::string title)
{
   this->title = title;
}


std::string Level::get_title() const
{
   return title;
}




} // namespace Gameplay
} // namespace DialControl


