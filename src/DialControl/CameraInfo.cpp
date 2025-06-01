

#include <DialControl/CameraInfo.hpp>




namespace DialControl
{


CameraInfo::CameraInfo()
   : name("[unset-name]")
   , camera({})
   , position_tracks_a_target(false)
   , object_being_tracked(nullptr)
{
}


CameraInfo::~CameraInfo()
{
}




} // namespace DialControl


