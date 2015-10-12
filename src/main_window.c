#include <pebble.h>
#include "main_window.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_14;
static GFont s_res_bitham_42_medium_numbers;
static ActionBarLayer *s_actionbarlayer_1;
static TextLayer *s_textlayer_label;
static TextLayer *s_textlayer_selected_dice;
static TextLayer *s_textlayer_die_1;
static TextLayer *s_textlayer_die_2;
static TextLayer *s_textlayer_die_3;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, false);
  #endif
  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_bitham_42_medium_numbers = fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS);
  // s_actionbarlayer_1
  s_actionbarlayer_1 = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer_1, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer_1, GColorBlack);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer_1);
  
  // s_textlayer_label
  s_textlayer_label = text_layer_create(GRect(4, 4, 33, 20));
  text_layer_set_text(s_textlayer_label, "Dice:");
  text_layer_set_font(s_textlayer_label, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_label);
  
  // s_textlayer_selected_dice
  s_textlayer_selected_dice = text_layer_create(GRect(36, 4, 84, 20));
  text_layer_set_text(s_textlayer_selected_dice, "3 * D20");
  text_layer_set_text_alignment(s_textlayer_selected_dice, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_selected_dice);
  
  // s_textlayer_die_1
  s_textlayer_die_1 = text_layer_create(GRect(0, 21, 124, 42));
  text_layer_set_text(s_textlayer_die_1, "20");
  text_layer_set_text_alignment(s_textlayer_die_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_die_1, s_res_bitham_42_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_die_1);
  
  // s_textlayer_die_2
  s_textlayer_die_2 = text_layer_create(GRect(0, 64, 124, 42));
  text_layer_set_text(s_textlayer_die_2, "1");
  text_layer_set_text_alignment(s_textlayer_die_2, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_die_2, s_res_bitham_42_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_die_2);
  
  // s_textlayer_die_3
  s_textlayer_die_3 = text_layer_create(GRect(0, 107, 124, 42));
  text_layer_set_text(s_textlayer_die_3, "10");
  text_layer_set_text_alignment(s_textlayer_die_3, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_die_3, s_res_bitham_42_medium_numbers);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_die_3);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_actionbarlayer_1);
  text_layer_destroy(s_textlayer_label);
  text_layer_destroy(s_textlayer_selected_dice);
  text_layer_destroy(s_textlayer_die_1);
  text_layer_destroy(s_textlayer_die_2);
  text_layer_destroy(s_textlayer_die_3);
}
// END AUTO-GENERATED UI CODE

int die = 6;
enum {D4 = 4, D6 = 6, D8 = 8, D10 = 10, D12 = 12, D20 = 20, D203 = 203};

static void resetDice(void) {
  text_layer_set_text(s_textlayer_die_1, "");
  text_layer_set_text(s_textlayer_die_2, "");
  text_layer_set_text(s_textlayer_die_3, "");
}

static void roll_dice() {
  // The tap rolls dice
  resetDice();
  
  if (die == D203) {
    int dieOne = rand() % 20 + 1;
    int dieTwo = rand() % 20 + 1;
    int dieThree = rand() % 20 + 1;
    static char buf1[] = "DD";
    static char buf2[] = "DD";
    static char buf3[] = "DD";
    snprintf(buf1, sizeof(buf1), "%d", dieOne);
    snprintf(buf2, sizeof(buf2), "%d", dieTwo);
    snprintf(buf3, sizeof(buf3), "%d", dieThree);
    text_layer_set_text(s_textlayer_die_1, buf1);
    text_layer_set_text(s_textlayer_die_2, buf2);
    text_layer_set_text(s_textlayer_die_3, buf3);
  } else {
    int i = rand() % die + 1;
    static char buf[] = "DD";
    snprintf(buf, sizeof(buf), "%d", i);
    text_layer_set_text(s_textlayer_die_1, buf);
  }
}

static void tap_handler(AccelAxisType axis, int32_t direction) {
  roll_dice();
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  roll_dice();
}

static void next_die() {
  switch (die) {
    case D4:
      die = D6;
      break;
    case D6:
      die = D8;
      break;
    case D8:
      die = D10;
      break;
    case D10:
      die = D12;
      break;
    case D12:
      die = D20;
      break;
    case D20:
      die = D203;
      break;
    default:
      die = D4;      
  }
  
  static char buf[] = "DDDDD";
  if (die == D203) {
    snprintf(buf, sizeof(buf), "3 D20");  
  } else {
    snprintf(buf, sizeof(buf), "D%d", die);  
  }
  
  text_layer_set_text(s_textlayer_selected_dice, buf);
  resetDice();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  next_die();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  next_die();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_main_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  
  window_set_click_config_provider(s_window, click_config_provider);
  
  // Subscribe to the accelerometer tap service
  accel_tap_service_subscribe(tap_handler);
  
  die = D203;
  resetDice();
}

void hide_main_window(void) {
  window_stack_remove(s_window, true);
}
