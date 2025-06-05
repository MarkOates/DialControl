

#include <Timeline/ParameterView.hpp>

#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Timeline
{


ParameterView::ParameterView(AllegroFlare::FontBin* font_bin, std::string label, Timeline::Parameter* track, float width, float height, float x_scale, float time_scale, float start_x, int selection_cursor_x)
   : font_bin(font_bin)
   , label(label)
   , track(track)
   , width(width)
   , height(height)
   , x_scale(x_scale)
   , time_scale(time_scale)
   , start_x(start_x)
   , selection_cursor_x(selection_cursor_x)
   , icon_font_size(-12)
   , hidden(false)
   , focused(false)
   , focused_keyframe_idx(0)
{
}


ParameterView::~ParameterView()
{
}


void ParameterView::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void ParameterView::set_label(std::string label)
{
   this->label = label;
}


void ParameterView::set_track(Timeline::Parameter* track)
{
   this->track = track;
}


void ParameterView::set_width(float width)
{
   this->width = width;
}


void ParameterView::set_height(float height)
{
   this->height = height;
}


void ParameterView::set_x_scale(float x_scale)
{
   this->x_scale = x_scale;
}


void ParameterView::set_time_scale(float time_scale)
{
   this->time_scale = time_scale;
}


void ParameterView::set_start_x(float start_x)
{
   this->start_x = start_x;
}


void ParameterView::set_selection_cursor_x(int selection_cursor_x)
{
   this->selection_cursor_x = selection_cursor_x;
}


void ParameterView::set_icon_font_size(int icon_font_size)
{
   this->icon_font_size = icon_font_size;
}


AllegroFlare::FontBin* ParameterView::get_font_bin() const
{
   return font_bin;
}


std::string ParameterView::get_label() const
{
   return label;
}


Timeline::Parameter* ParameterView::get_track() const
{
   return track;
}


float ParameterView::get_width() const
{
   return width;
}


float ParameterView::get_height() const
{
   return height;
}


float ParameterView::get_x_scale() const
{
   return x_scale;
}


float ParameterView::get_time_scale() const
{
   return time_scale;
}


float ParameterView::get_start_x() const
{
   return start_x;
}


int ParameterView::get_selection_cursor_x() const
{
   return selection_cursor_x;
}


int ParameterView::get_icon_font_size() const
{
   return icon_font_size;
}


void ParameterView::set_as_focused()
{
   focused = true;
   return;
}

void ParameterView::set_as_unfocused()
{
   focused = false;
   return;
}

void ParameterView::add_keyframe(float time, float value, std::function<float(float)> interpolator_func)
{
   if (!track) return;
   //track->add_keyframe_matching_previous_value_or_initial_value(time, value, 
   track->add_keyframe(time, value, interpolator_func);
   return;
}

bool ParameterView::remove_keyframe_at_index(std::size_t index)
{
   if (!track) return false;

   bool removed = track->remove_keyframe_at_index(index);
   if (!removed) return false;

   int num_keyframes_now = static_cast<int>(track->keyframes.size());

   if (num_keyframes_now == 0)
   {
       focused_keyframe_idx = 0;
   }
   else
   {
       std::size_t previously_focused_szt = static_cast<std::size_t>(focused_keyframe_idx);

       if (previously_focused_szt == index) {
           if (static_cast<std::size_t>(focused_keyframe_idx) >= num_keyframes_now) {
               focused_keyframe_idx = num_keyframes_now - 1;
           }
       } else if (previously_focused_szt > index) {
           focused_keyframe_idx--;
       }

       if (focused_keyframe_idx < 0) {
          focused_keyframe_idx = 0;
       }
   }

   for (int i = 0; i < num_keyframes_now; ++i) {
       track->keyframes[i].set_focused(i == focused_keyframe_idx);
   }

   return true;
}

bool ParameterView::remove_keyframe_at_focused_keyframe_idx()
{
   return remove_keyframe_at_index(focused_keyframe_idx);
}

void ParameterView::move_keyframe_value(float delta)
{
   if (!track) return;

   auto &keyframes = track->keyframes;
   int num_keyframes = static_cast<int>(keyframes.size());
   if (focused_keyframe_idx < 0 || focused_keyframe_idx >= num_keyframes) return;

   Timeline::Keyframe &keyframe = keyframes[focused_keyframe_idx];

   float value = keyframe.value;
   value += delta;

   // Clamp value between min and max (if they are in use)
   if (track->has_max_value && value > track->max_value) value = track->max_value;
   if (track->has_min_value && value < track->min_value) value = track->min_value;

   keyframe.value = value;
}

void ParameterView::move_keyframe_time(float delta, float keyframe_max_time)
{
   if (!track) return;

   auto &keyframes = track->keyframes;
   int num_keyframes = static_cast<int>(keyframes.size());
   if (focused_keyframe_idx < 0 || focused_keyframe_idx >= num_keyframes) return;


   Timeline::Keyframe &keyframe = keyframes[focused_keyframe_idx];
   float new_time = keyframe.time + delta;

   // Determine lower and upper bounds
   float lower_bound = 0.0f;
   float upper_bound = keyframe_max_time;

   if (focused_keyframe_idx > 0)
   {
      lower_bound = keyframes[focused_keyframe_idx - 1].time;
   }

   if (focused_keyframe_idx < num_keyframes - 1)
   {
      upper_bound = keyframes[focused_keyframe_idx + 1].time;
   }

   // Clamp new_time between the bounds
   if (new_time < lower_bound) new_time = lower_bound;
   if (new_time > upper_bound) new_time = upper_bound;

   keyframe.time = new_time;
}

void ParameterView::next_keyframe(bool wrap)
{
   if (!track) return;

   auto &keyframes = track->keyframes;
   int num_keyframes = static_cast<int>(keyframes.size());
   if (num_keyframes == 0) return;

   // Clamp current idx to valid range
   if (focused_keyframe_idx < 0 || focused_keyframe_idx >= num_keyframes)
   {
      focused_keyframe_idx = 0;
      keyframes[focused_keyframe_idx].set_focused(true);
      return;
   }

   // Unfocus current
   keyframes[focused_keyframe_idx].set_focused(false);

   // Advance
   focused_keyframe_idx++;

   if (focused_keyframe_idx >= num_keyframes)
   {
      if (wrap)
      {
         focused_keyframe_idx = 0;
      }
      else
      {
         focused_keyframe_idx = num_keyframes - 1;
      }
   }

   keyframes[focused_keyframe_idx].set_focused(true);
   return;
}

void ParameterView::previous_keyframe(bool wrap)
{
   if (!track) return;

   auto &keyframes = track->keyframes;
   int num_keyframes = static_cast<int>(keyframes.size());
   if (num_keyframes == 0) return;

   // Clamp current idx
   if (focused_keyframe_idx < 0 || focused_keyframe_idx >= num_keyframes)
   {
      focused_keyframe_idx = 0;
      keyframes[focused_keyframe_idx].set_focused(true);
      return;
   }

   // Unfocus current
   keyframes[focused_keyframe_idx].set_focused(false);

   // Decrement
   focused_keyframe_idx--;

   if (focused_keyframe_idx < 0)
   {
      if (wrap)
      {
         focused_keyframe_idx = num_keyframes - 1;
      }
      else
      {
         focused_keyframe_idx = 0;
      }
   }

   keyframes[focused_keyframe_idx].set_focused(true);
   return;
}

void ParameterView::render()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Timeline::ParameterView::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::ParameterView::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Timeline::ParameterView::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::ParameterView::render]: error: guard \"font_bin\" not met");
   }
   if (!(track))
   {
      std::stringstream error_message;
      error_message << "[Timeline::ParameterView::render]: error: guard \"track\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::ParameterView::render]: error: guard \"track\" not met");
   }
   ALLEGRO_COLOR UNFOCUSED_BACKFILL_COLOR = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR FOCUSED_BACKFILL_COLOR = ALLEGRO_COLOR{0.3, 0.275, 0.21, 1.0};
   ALLEGRO_COLOR backfill_color = focused ? FOCUSED_BACKFILL_COLOR : UNFOCUSED_BACKFILL_COLOR;
   ALLEGRO_COLOR line_color = ALLEGRO_COLOR{0.1, 0.1, 0.1, 0.1};
   ALLEGRO_FONT *track_label_font = obtain_track_label_font();
   int track_label_font_line_height = al_get_font_line_height(track_label_font);
   float y_scale = height;
   float y_label_offset = 0;
   float x_label_offset = -100;
   ALLEGRO_COLOR w = ALLEGRO_COLOR{1, 1, 1, 1};

   al_draw_filled_rectangle(0, 0, width, height, backfill_color);

   float track_label_y_alignment_offset = (int)(height / 2.0 - track_label_font_line_height / 2.0);
   al_draw_text(
       track_label_font,
       w,
       0 + x_label_offset,
       0 + y_label_offset + track_label_y_alignment_offset,
       ALLEGRO_ALIGN_LEFT,
       label.c_str()
   );

   bool track_has_no_bounds = !track->has_max_value || !track->has_min_value;
   for (auto &keyframe : track->keyframes)
   {
       float keyframe_x = (keyframe.time * x_scale * time_scale) - start_x * x_scale * time_scale;
       float capped_normalized_y = keyframe.value;
       float keyframe_y = capped_normalized_y * y_scale;

       if (keyframe_x > width) break;
       if (keyframe_x < 0) continue;

       if (track_has_no_bounds) keyframe_y = height * 0.5;

       al_draw_line(keyframe_x, 0, keyframe_x, 0 + height, line_color, 1.0);

       if (keyframe.focused)
       {
           draw_selected_node_icon(keyframe_x, keyframe_y);
       }
       else
       {
           draw_node_icon(keyframe_x, keyframe_y);
       }
   }

   return;
}

void ParameterView::draw_selected_node_icon(float x, float y)
{
   ALLEGRO_FONT *bigger_icon_font = obtain_bigger_icon_font();
   ALLEGRO_FONT *icon_font = obtain_icon_font();
   int32_t diamond = 0xf219;
   ALLEGRO_COLOR bigger_color = AllegroFlare::Color::DeepSkyBlue;
   ALLEGRO_COLOR color = AllegroFlare::Color::Eigengrau;
   draw_centered_unicode_character(bigger_icon_font, bigger_color, x, y, diamond, 0);
   draw_centered_unicode_character(icon_font, color, x, y, diamond, 0);
   return;
}

void ParameterView::draw_node_icon(float x, float y)
{
   ALLEGRO_FONT *icon_font = obtain_icon_font();
   int32_t diamond = 0xf219;
   ALLEGRO_COLOR color = AllegroFlare::Color::DeepSkyBlue;
   draw_centered_unicode_character(icon_font, color, x, y, diamond, 0);
   return;
}

void ParameterView::draw_centered_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int x, int y, uint32_t icon, int flags)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   float width = al_get_ustr_width(font, ustr);
   float height = al_get_font_line_height(font);
   al_draw_ustr(font, color, x-width*0.5, y-height*0.5, flags, ustr);
   return;
}

ALLEGRO_FONT* ParameterView::obtain_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Timeline::ParameterView::obtain_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::ParameterView::obtain_icon_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream ss;
   ss << "fa-solid-900.ttf " << icon_font_size;
   return font_bin->auto_get(ss.str());
}

ALLEGRO_FONT* ParameterView::obtain_bigger_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Timeline::ParameterView::obtain_bigger_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::ParameterView::obtain_bigger_icon_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream ss;
   ss << "fa-solid-900.ttf " << icon_font_size - 8;
   return font_bin->auto_get(ss.str());
}

ALLEGRO_FONT* ParameterView::obtain_track_label_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Timeline::ParameterView::obtain_track_label_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::ParameterView::obtain_track_label_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -20");
}

ALLEGRO_FONT* ParameterView::obtain_track_values_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Timeline::ParameterView::obtain_track_values_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Timeline::ParameterView::obtain_track_values_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -20");
}


} // namespace Timeline


