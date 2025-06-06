#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <Timeline/Parameter.hpp>
#include <Timeline/ParameterView.hpp>
#include <allegro5/allegro.h>
#include <lib/nlohmann/json.hpp>
#include <string>
#include <vector>


namespace Timeline
{
   class MotionStudio
   {
   private:
      std::vector<Timeline::Parameter> parameters;
      std::vector<Timeline::ParameterView> parameter_views;
      int parameter_view_idx;
      bool wrap_parameter_view_idx_change;
      AllegroFlare::Placement2D timeline_placement;
      float playback_speed;
      float playhead;
      float playhead_max;
      float playhead_movement_fine;
      float playhead_movement_macro;
      bool playing;
      float timeline_start_position;
      float timeline_time_scale;
      bool timeline_overlay_visible;

   protected:


   public:
      MotionStudio();
      ~MotionStudio();

      void set_parameters(std::vector<Timeline::Parameter> parameters);
      void set_parameter_views(std::vector<Timeline::ParameterView> parameter_views);
      void set_parameter_view_idx(int parameter_view_idx);
      void set_wrap_parameter_view_idx_change(bool wrap_parameter_view_idx_change);
      void set_timeline_placement(AllegroFlare::Placement2D timeline_placement);
      void set_playback_speed(float playback_speed);
      void set_playhead(float playhead);
      void set_playhead_max(float playhead_max);
      void set_playhead_movement_fine(float playhead_movement_fine);
      void set_playhead_movement_macro(float playhead_movement_macro);
      void set_playing(bool playing);
      void set_timeline_start_position(float timeline_start_position);
      void set_timeline_time_scale(float timeline_time_scale);
      std::vector<Timeline::Parameter> get_parameters() const;
      std::vector<Timeline::ParameterView> get_parameter_views() const;
      int get_parameter_view_idx() const;
      bool get_wrap_parameter_view_idx_change() const;
      AllegroFlare::Placement2D get_timeline_placement() const;
      float get_playback_speed() const;
      float get_playhead() const;
      float get_playhead_max() const;
      float get_playhead_movement_fine() const;
      float get_playhead_movement_macro() const;
      bool get_playing() const;
      float get_timeline_start_position() const;
      float get_timeline_time_scale() const;
      std::vector<Timeline::Parameter> &get_parameters_ref();
      std::vector<Timeline::ParameterView> &get_parameter_views_ref();
      int &get_parameter_view_idx_ref();
      bool &get_wrap_parameter_view_idx_change_ref();
      AllegroFlare::Placement2D &get_timeline_placement_ref();
      float &get_playback_speed_ref();
      float &get_playhead_ref();
      float &get_playhead_max_ref();
      float &get_playhead_movement_fine_ref();
      float &get_playhead_movement_macro_ref();
      bool &get_playing_ref();
      void render();
      void toggle_timeline_visibility();
      void move_timeline_start_position(float delta=0.0f);
      void modify_timeline_time_scale(float delta=0.0f);
      void toggle_playback();
      void update_playback();
      void set_playhead_position(float playhead_position=0.0f);
      void move_playhead(float delta=0.0f);
      void move_keyframe_value(float delta=0.0f);
      void move_keyframe_time(float delta=0.0f);
      void next_keyframe();
      void previous_keyframe();
      void add_keyframe();
      void remove_keyframe();
      void next_parameter_view();
      void previous_parameter_view();
      void on_key_down(ALLEGRO_EVENT* event=nullptr);
      std::vector<Timeline::ParameterView> build_parameter_views_for_parameters(AllegroFlare::FontBin* font_bin=nullptr, std::vector<Timeline::Parameter>* p=nullptr, float height=Timeline::ParameterView::DEFAULT_HEIGHT);
      std::string build_json_dump();
      nlohmann::json build_json();
      void load_json(std::string json_string="[unset-json_string]");
   };
}



