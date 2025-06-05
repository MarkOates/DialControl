#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Timeline/Parameter.hpp>
#include <allegro5/allegro.h>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>


namespace Timeline
{
   class ParameterView
   {
   public:
      static constexpr float DEFAULT_HEIGHT = 32.0f;

   private:
      AllegroFlare::FontBin* font_bin;
      std::string label;
      Timeline::Parameter* track;
      float width;
      float height;
      float x_scale;
      float time_scale;
      float start_x;
      int selection_cursor_x;
      int icon_font_size;
      void draw_selected_node_icon(float x=0.0f, float y=0.0f);
      void draw_node_icon(float x=0.0f, float y=0.0f);
      void draw_centered_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=0xf005, int flags=0);
      ALLEGRO_FONT* obtain_icon_font();
      ALLEGRO_FONT* obtain_bigger_icon_font();
      ALLEGRO_FONT* obtain_track_label_font();
      ALLEGRO_FONT* obtain_track_values_font();

   protected:


   public:
      bool hidden;
      bool focused;
      int focused_keyframe_idx;
      ParameterView(AllegroFlare::FontBin* font_bin=nullptr, std::string label="Unlabeled Parameter", Timeline::Parameter* track=nullptr, float width=1200.0f, float height=DEFAULT_HEIGHT, float x_scale=100.0f, float time_scale=1.0f, float start_x=0.0f, int selection_cursor_x=-1);
      ~ParameterView();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void set_label(std::string label);
      void set_track(Timeline::Parameter* track);
      void set_width(float width);
      void set_height(float height);
      void set_x_scale(float x_scale);
      void set_time_scale(float time_scale);
      void set_start_x(float start_x);
      void set_selection_cursor_x(int selection_cursor_x);
      void set_icon_font_size(int icon_font_size);
      AllegroFlare::FontBin* get_font_bin() const;
      std::string get_label() const;
      Timeline::Parameter* get_track() const;
      float get_width() const;
      float get_height() const;
      float get_x_scale() const;
      float get_time_scale() const;
      float get_start_x() const;
      int get_selection_cursor_x() const;
      int get_icon_font_size() const;
      void set_as_focused();
      void set_as_unfocused();
      void add_keyframe(float time=0.0f, float value=0.0f, std::function<float(float)> interpolator_func={});
      bool remove_keyframe_at_index(std::size_t index=0);
      bool remove_keyframe_at_focused_keyframe_idx();
      void move_keyframe_value(float delta=0.0f);
      void move_keyframe_time(float delta=0.0f, float keyframe_max_time=120.0f);
      void next_keyframe(bool wrap=false);
      void previous_keyframe(bool wrap=false);
      void render();
   };
}



