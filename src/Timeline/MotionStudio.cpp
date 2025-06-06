

#include <Timeline/MotionStudio.hpp>

#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <Timeline/JSONLoaders/Timeline/Parameter.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace Timeline
{


MotionStudio::MotionStudio()
   : parameters({})
   , parameter_views({})
   , parameter_view_idx(0)
   , wrap_parameter_view_idx_change(true)
   , timeline_placement({})
   , playback_speed(1.0f / 60.0f)
   , playhead(0.0f)
   , playhead_max(120.0f)
   , playhead_movement_fine(1.0 / 60)
   , playhead_movement_macro(1.0 / 60 * 30)
   , playing(false)
   , timeline_start_position(0.0)
   , timeline_time_scale(1.0)
   , timeline_overlay_visible(true)
{
}


MotionStudio::~MotionStudio()
{
}


void MotionStudio::set_parameters(std::vector<Timeline::Parameter> parameters)
{
   this->parameters = parameters;
}


void MotionStudio::set_parameter_views(std::vector<Timeline::ParameterView> parameter_views)
{
   this->parameter_views = parameter_views;
}


void MotionStudio::set_parameter_view_idx(int parameter_view_idx)
{
   this->parameter_view_idx = parameter_view_idx;
}


void MotionStudio::set_wrap_parameter_view_idx_change(bool wrap_parameter_view_idx_change)
{
   this->wrap_parameter_view_idx_change = wrap_parameter_view_idx_change;
}


void MotionStudio::set_timeline_placement(AllegroFlare::Placement2D timeline_placement)
{
   this->timeline_placement = timeline_placement;
}


void MotionStudio::set_playback_speed(float playback_speed)
{
   this->playback_speed = playback_speed;
}


void MotionStudio::set_playhead(float playhead)
{
   this->playhead = playhead;
}


void MotionStudio::set_playhead_max(float playhead_max)
{
   this->playhead_max = playhead_max;
}


void MotionStudio::set_playhead_movement_fine(float playhead_movement_fine)
{
   this->playhead_movement_fine = playhead_movement_fine;
}


void MotionStudio::set_playhead_movement_macro(float playhead_movement_macro)
{
   this->playhead_movement_macro = playhead_movement_macro;
}


void MotionStudio::set_playing(bool playing)
{
   this->playing = playing;
}


void MotionStudio::set_timeline_start_position(float timeline_start_position)
{
   this->timeline_start_position = timeline_start_position;
}


void MotionStudio::set_timeline_time_scale(float timeline_time_scale)
{
   this->timeline_time_scale = timeline_time_scale;
}


std::vector<Timeline::Parameter> MotionStudio::get_parameters() const
{
   return parameters;
}


std::vector<Timeline::ParameterView> MotionStudio::get_parameter_views() const
{
   return parameter_views;
}


int MotionStudio::get_parameter_view_idx() const
{
   return parameter_view_idx;
}


bool MotionStudio::get_wrap_parameter_view_idx_change() const
{
   return wrap_parameter_view_idx_change;
}


AllegroFlare::Placement2D MotionStudio::get_timeline_placement() const
{
   return timeline_placement;
}


float MotionStudio::get_playback_speed() const
{
   return playback_speed;
}


float MotionStudio::get_playhead() const
{
   return playhead;
}


float MotionStudio::get_playhead_max() const
{
   return playhead_max;
}


float MotionStudio::get_playhead_movement_fine() const
{
   return playhead_movement_fine;
}


float MotionStudio::get_playhead_movement_macro() const
{
   return playhead_movement_macro;
}


bool MotionStudio::get_playing() const
{
   return playing;
}


float MotionStudio::get_timeline_start_position() const
{
   return timeline_start_position;
}


float MotionStudio::get_timeline_time_scale() const
{
   return timeline_time_scale;
}


std::vector<Timeline::Parameter> &MotionStudio::get_parameters_ref()
{
   return parameters;
}


std::vector<Timeline::ParameterView> &MotionStudio::get_parameter_views_ref()
{
   return parameter_views;
}


int &MotionStudio::get_parameter_view_idx_ref()
{
   return parameter_view_idx;
}


bool &MotionStudio::get_wrap_parameter_view_idx_change_ref()
{
   return wrap_parameter_view_idx_change;
}


AllegroFlare::Placement2D &MotionStudio::get_timeline_placement_ref()
{
   return timeline_placement;
}


float &MotionStudio::get_playback_speed_ref()
{
   return playback_speed;
}


float &MotionStudio::get_playhead_ref()
{
   return playhead;
}


float &MotionStudio::get_playhead_max_ref()
{
   return playhead_max;
}


float &MotionStudio::get_playhead_movement_fine_ref()
{
   return playhead_movement_fine;
}


float &MotionStudio::get_playhead_movement_macro_ref()
{
   return playhead_movement_macro;
}


bool &MotionStudio::get_playing_ref()
{
   return playing;
}


void MotionStudio::render()
{
   if (timeline_overlay_visible)
   {
      timeline_placement.start_transform();
      float x_scale = 100;

      // Draw the timelines
      float total_height = 0;
      float width = 1200.0;
      AllegroFlare::Placement2D placement;
      ALLEGRO_COLOR pinline_color{0, 0, 0, 0.35};
      for (auto &parameter_view : parameter_views)
      {
         // Update render
         parameter_view.set_x_scale(x_scale); // TODO: Figure out how to quantify pixels per second
         parameter_view.set_time_scale(timeline_time_scale);
         parameter_view.set_start_x(timeline_start_position);

         placement.start_transform();
         al_draw_line(0, 0, width, 0, pinline_color, 1.0);
         parameter_view.render();
         placement.restore_transform();
         placement.position.y += parameter_view.get_height();
      }
      al_draw_line(0, 0, width, 0, pinline_color, 1.0);
      total_height = placement.position.y;

      // Draw the playhead
      float playhead_spacial_pos = playhead * x_scale * timeline_time_scale
                                 - timeline_start_position * timeline_time_scale * x_scale;
      al_draw_line(playhead_spacial_pos, -10, playhead_spacial_pos, total_height+10, ALLEGRO_COLOR{1, 1, 1, 1}, 1.0);
     
      timeline_placement.restore_transform();
   }
   return;
}

void MotionStudio::toggle_timeline_visibility()
{
   if (timeline_overlay_visible) timeline_overlay_visible = false;
   else timeline_overlay_visible = true;
   return;
}

void MotionStudio::move_timeline_start_position(float delta)
{
   float new_position = timeline_start_position + delta;

   if (new_position < 0.0f)
      new_position = 0.0f;
   else if (new_position > playhead_max)
      new_position = playhead_max;

   set_timeline_start_position(new_position);
   return;
}

void MotionStudio::modify_timeline_time_scale(float delta)
{
   float new_position = timeline_time_scale + delta;

   if (new_position < 0.0f)
      new_position = 0.125f;
   else if (new_position > playhead_max)
      new_position = playhead_max;

   set_timeline_time_scale(new_position);
   return;
}

void MotionStudio::toggle_playback()
{
   if (playing) playing = false;
   else playing = true;
}

void MotionStudio::update_playback()
{
   // TODO: pass in time duration (do later)
   if (playing) playhead += 1.0 * playback_speed;

   for (auto &parameter : parameters)
   {
      //if (parameter.name == "spin")
      //{
         parameter.assign_to_time(playhead); // DEVELOPMENT
      //}
      //parameter.assign_to_time(playhead);
   }
   return;
}

void MotionStudio::set_playhead_position(float playhead_position)
{
   playhead = playhead_position;
   return;
}

void MotionStudio::move_playhead(float delta)
{
   float new_position = playhead + delta;

   if (new_position < 0.0f)
      new_position = 0.0f;
   else if (new_position > playhead_max)
      new_position = playhead_max;

   set_playhead_position(new_position);
   return;
}

void MotionStudio::move_keyframe_value(float delta)
{
   parameter_views[parameter_view_idx].move_keyframe_value(delta);
   return;
}

void MotionStudio::move_keyframe_time(float delta)
{
   parameter_views[parameter_view_idx].move_keyframe_time(delta);
   return;
}

void MotionStudio::next_keyframe()
{
   parameter_views[parameter_view_idx].next_keyframe();
   return;
}

void MotionStudio::previous_keyframe()
{
   parameter_views[parameter_view_idx].previous_keyframe();
   return;
}

void MotionStudio::add_keyframe()
{
   parameter_views[parameter_view_idx].add_keyframe(playhead, 0.0, {});
   return;
}

void MotionStudio::remove_keyframe()
{
   parameter_views[parameter_view_idx].remove_keyframe_at_focused_keyframe_idx();
   return;
}

void MotionStudio::next_parameter_view()
{
   int total = static_cast<int>(parameter_views.size());
   if (total == 0)
      return;

   int start_idx = parameter_view_idx;

   parameter_views[parameter_view_idx].set_as_unfocused();

   do
   {
      parameter_view_idx++;
      if (parameter_view_idx >= total)
      {
         if (wrap_parameter_view_idx_change)
            parameter_view_idx = 0;
         else
         {
            parameter_view_idx = total - 1;
            break;
         }
      }
   }
   while (parameter_views[parameter_view_idx].hidden && parameter_view_idx != start_idx);

   parameter_views[parameter_view_idx].set_as_focused();
   return;
}

void MotionStudio::previous_parameter_view()
{
   int total = static_cast<int>(parameter_views.size());
   if (total == 0)
      return;

   int start_idx = parameter_view_idx;

   parameter_views[parameter_view_idx].set_as_unfocused();

   do
   {
      parameter_view_idx--;
      if (parameter_view_idx < 0)
      {
         if (wrap_parameter_view_idx_change)
            parameter_view_idx = total - 1;
         else
         {
            parameter_view_idx = 0;
            break;
         }
      }
   }
   while (parameter_views[parameter_view_idx].hidden && parameter_view_idx != start_idx);

   parameter_views[parameter_view_idx].set_as_focused();
   return;
}

void MotionStudio::on_key_down(ALLEGRO_EVENT* event)
{
   bool shift = event->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
   bool ctrl = event->keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
   bool alt = event->keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
   bool command = event->keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;

   constexpr auto SHIFT = AllegroFlare::KeyboardCommandMapper::SHIFT;
   constexpr auto CTRL = AllegroFlare::KeyboardCommandMapper::CTRL;
   constexpr auto COMMAND = AllegroFlare::KeyboardCommandMapper::COMMAND;
   constexpr auto OPTION = AllegroFlare::KeyboardCommandMapper::OPTION;

   AllegroFlare::KeyboardCommandMapper mapper;

   // Define mappings
   mapper.set_mapping(ALLEGRO_KEY_SPACE, 0, { "toggle_playback" });
   mapper.set_mapping(ALLEGRO_KEY_N, SHIFT, { "next_parameter_view" });
   mapper.set_mapping(ALLEGRO_KEY_P, SHIFT, { "previous_parameter_view" });
   mapper.set_mapping(ALLEGRO_KEY_1, COMMAND, { "move_playhead_fine_left" });
   mapper.set_mapping(ALLEGRO_KEY_2, COMMAND, { "move_playhead_fine_right" });
   mapper.set_mapping(ALLEGRO_KEY_3, COMMAND, { "move_playhead_macro_left" });
   mapper.set_mapping(ALLEGRO_KEY_4, COMMAND, { "move_playhead_macro_right" });
   mapper.set_mapping(ALLEGRO_KEY_5, COMMAND, { "move_keyframe_time_back" });
   mapper.set_mapping(ALLEGRO_KEY_6, COMMAND, { "move_keyframe_time_forward" });
   mapper.set_mapping(ALLEGRO_KEY_7, COMMAND, { "move_keyframe_value_up" });
   mapper.set_mapping(ALLEGRO_KEY_8, COMMAND, { "move_keyframe_value_down" });
   mapper.set_mapping(ALLEGRO_KEY_A, 0, { "add_keyframe" });
   mapper.set_mapping(ALLEGRO_KEY_N, 0, { "next_keyframe" });
   mapper.set_mapping(ALLEGRO_KEY_P, 0, { "previous_keyframe" });
   mapper.set_mapping(ALLEGRO_KEY_X, 0, { "remove_keyframe" });
   mapper.set_mapping(ALLEGRO_KEY_H, 0, { "toggle_timeline_visibility" });
   mapper.set_mapping(ALLEGRO_KEY_X, 0, { "dump_json_to_cout" });
   mapper.set_mapping(ALLEGRO_KEY_PAD_4, 0, { "move_timeline_start_position_forward" });
   mapper.set_mapping(ALLEGRO_KEY_PAD_6, 0, { "move_timeline_start_position_backward" });
   mapper.set_mapping(ALLEGRO_KEY_PAD_8, 0, { "increase_timeline_time_scale" });
   mapper.set_mapping(ALLEGRO_KEY_PAD_2, 0, { "decrease_timeline_time_scale" });


   // Obtain commands from the current key input
   std::vector<std::string> commands = mapper.get_mapping(event->keyboard.keycode, shift, ctrl, alt, command);


   // Find commands and execute the correlated program logic
   for (auto &command : commands)
   {
      if (command.empty()) continue;

      else if (command == "toggle_playback") toggle_playback();

      else if (command == "next_parameter_view") next_parameter_view();
      else if (command == "previous_parameter_view") previous_parameter_view();

      else if (command == "move_playhead_fine_left") move_playhead(-playhead_movement_fine);
      else if (command == "move_playhead_fine_right") move_playhead(playhead_movement_fine);
      else if (command == "move_playhead_macro_left") move_playhead(-playhead_movement_macro);
      else if (command == "move_playhead_macro_right") move_playhead(playhead_movement_macro);
      else if (command == "move_keyframe_value_up") move_keyframe_value(0.1);
      else if (command == "move_keyframe_value_down") move_keyframe_value(-0.1);
      else if (command == "move_keyframe_time_back") move_keyframe_time(-0.1);
      else if (command == "move_keyframe_time_forward") move_keyframe_time(0.1);

      else if (command == "next_keyframe") next_keyframe();
      else if (command == "add_keyframe") add_keyframe();
      else if (command == "remove_keyframe") remove_keyframe();
      else if (command == "previous_keyframe") previous_keyframe();
      else if (command == "toggle_timeline_visibility") toggle_timeline_visibility();
      else if (command == "dump_json_to_cout") std::cout << build_json_dump() << std::endl;
      else if (command == "move_timeline_start_position_forward") move_timeline_start_position(0.25);
      else if (command == "move_timeline_start_position_backward") move_timeline_start_position(-0.25);
      else if (command == "increase_timeline_time_scale") modify_timeline_time_scale(0.06125);
      else if (command == "decrease_timeline_time_scale") modify_timeline_time_scale(-0.06125);
      //else if (command == "increase_timeline_scale") move_timeline_start_position(0.25);
      //else if (command == "decrease_timeline_scale") move_timeline_start_position(-0.25);
   //mapper.set_mapping(ALLEGRO_KEY_PAD_8, 0, { "increase_timeline_time_scale" });
   //mapper.set_mapping(ALLEGRO_KEY_PAD_2, 0, { "decrease_timeline_time_scale" });

      else
      {
         throw std::runtime_error("missinasdnh89sdh89fhsg");
      }
   }





   /*
   mapper.set_mapping(ALLEGRO_KEY_W, 0, { "position_z_minus" });
   mapper.set_mapping(ALLEGRO_KEY_S, 0, { "position_z_plus" });
   mapper.set_mapping(ALLEGRO_KEY_A, 0, { "position_x_minus" });
   mapper.set_mapping(ALLEGRO_KEY_D, 0, { "position_x_plus" });
   mapper.set_mapping(ALLEGRO_KEY_C, 0, { "position_y_minus" });
   mapper.set_mapping(ALLEGRO_KEY_E, 0, { "position_y_plus" });

   mapper.set_mapping(ALLEGRO_KEY_UP, 0, { "up" });
   mapper.set_mapping(ALLEGRO_KEY_DOWN, 0, { "down" });
   mapper.set_mapping(ALLEGRO_KEY_LEFT, 0, { "left" });
   mapper.set_mapping(ALLEGRO_KEY_RIGHT, 0, { "right" });

   mapper.set_mapping(ALLEGRO_KEY_1, COMMAND, { "dial_1_left" });
   mapper.set_mapping(ALLEGRO_KEY_2, COMMAND, { "dial_1_right" });
   mapper.set_mapping(ALLEGRO_KEY_3, COMMAND, { "dial_2_left" });
   mapper.set_mapping(ALLEGRO_KEY_4, COMMAND, { "dial_2_right" });
   mapper.set_mapping(ALLEGRO_KEY_5, COMMAND, { "dial_3_left" });
   mapper.set_mapping(ALLEGRO_KEY_6, COMMAND, { "dial_3_right" });
   mapper.set_mapping(ALLEGRO_KEY_7, COMMAND, { "dial_4_left" });
   mapper.set_mapping(ALLEGRO_KEY_8, COMMAND, { "dial_4_right" });


   float dial_increment = 1.0 / 32;


   std::vector<std::string> commands = mapper.get_mapping(event->keyboard.keycode, shift, ctrl, alt, command);


   for (auto &command : commands)
   {
      if (command.empty()) continue;

      else if (command == "position_x_plus") current_camera->position.x += 0.25;
      else if (command == "position_x_minus") current_camera->position.x -= 0.25;
      else if (command == "position_y_plus") current_camera->position.y += 0.25;
      else if (command == "position_y_minus") current_camera->position.y -= 0.25;
      else if (command == "position_z_plus") current_camera->position.z += 0.25;
      else if (command == "position_z_minus") current_camera->position.z -= 0.25;

      else if (command == "right") current_camera->stepout.x += 0.25;
      else if (command == "left") current_camera->stepout.x -= 0.25;
      else if (command == "up") current_camera->stepout.y += 0.25;
      else if (command == "down") current_camera->stepout.y -= 0.25;

      else if (command == "dial_1_left") current_camera->spin -= dial_increment;
      else if (command == "dial_1_right") current_camera->spin += dial_increment;
      else if (command == "dial_2_left") current_camera->tilt -= dial_increment;
      else if (command == "dial_2_right") current_camera->tilt += dial_increment;
      else if (command == "dial_3_left") current_camera->zoom -= 0.125;
      else if (command == "dial_3_right") current_camera->zoom += 0.125;
      else if (command == "dial_4_left") current_camera->stepout.z -= 1.0;
      else if (command == "dial_4_right") current_camera->stepout.z += 1.0;

      else
      {
         throw std::runtime_error("missinasdnh89sdh89fhsg");
      }
   }
   */

   return;
}

std::vector<Timeline::ParameterView> MotionStudio::build_parameter_views_for_parameters(AllegroFlare::FontBin* font_bin, std::vector<Timeline::Parameter>* p, float height)
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Timeline::MotionStudio::build_parameter_views_for_parameters]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::MotionStudio::build_parameter_views_for_parameters]: error: guard \"font_bin\" not met");
   }
   std::vector<Timeline::ParameterView> result;
   int x = 400;
   int y = 100;
   //int yd = 100;
   int i = 0;
   //float height = Timeline::ParameterView::DEFAULT_HEIGHT;
   //int yd = height;
   for (auto &pp : *p)
   {
      result.push_back(Timeline::ParameterView(font_bin, pp.name, &pp)); // HERE
      result.back().set_height(height);
      i++;
   }
   return result;
}

std::string MotionStudio::build_json_dump()
{
   nlohmann::json j;
   j["parameters"] = parameters;
   return j.dump(2);
}

nlohmann::json MotionStudio::build_json()
{
   nlohmann::json j;
   j["parameters"] = parameters;
   return j;
}

void MotionStudio::load_json(std::string json_string)
{
   nlohmann::json j = nlohmann::json::parse(json_string); // TODO: Consider moving this into a TRY block (later)

   if (j.contains("parameters") && j["parameters"].is_array())
   {
      // Set all the cameras to the camera values in the JSON array
      parameters = j["parameters"].get<std::vector<Timeline::Parameter>>();

      // Output some debugging info
      bool output_debug_info = false;
      if (output_debug_info)
      {
         std::cout << "- " << std::endl;
         for (int i=0; i<parameters.size(); i++)
         {
            std::cout << " parameter " << i << ": " << std::endl;
            std::cout << "       name: \"" << parameters[i].name << "\"" << std::endl;
         }
      }

      // Refresh the interface
      // TODO: HERE
   }
   else
   {
      throw std::runtime_error("Expected key \"parameters\" with an array value in JSON");
   }

   return;
}


} // namespace Timeline


