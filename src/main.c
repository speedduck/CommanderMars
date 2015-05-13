#include <pebble.h>

Window *window;
TextLayer *text_layer;
TextLayer *date_layer;
InverterLayer *inverter_layer;
static BitmapLayer *yorp;
static BitmapLayer *yorp_2;
static BitmapLayer *yorp_3;
static BitmapLayer *ground;
static GBitmap *s_example_bitmap;
static GBitmap *s_example_bitmap_2;
static GBitmap *s_example_bitmap_3;
static GBitmap *s_example_bitmap_4;

void handle_timechanges(struct tm *tick_time, TimeUnits units_changed) {
  static char time_buffer[10];
  static char date_buffer[10];
  
  strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", tick_time);
  text_layer_set_text(text_layer, time_buffer);
  
  strftime(date_buffer, sizeof(date_buffer), "%b %e", tick_time);
  text_layer_set_text(date_layer, date_buffer);
}

void handle_init(void) {
  // Creates images resource
  s_example_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_YL0);
  s_example_bitmap_2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_YR0);
  s_example_bitmap_3 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_YF0);
  s_example_bitmap_4 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND);
  
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, "Hello World!");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
  
  date_layer = text_layer_create(GRect(0, 112, 144, 56));
  text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
  text_layer_set_font(date_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(date_layer));
  
  inverter_layer = inverter_layer_create(GRect(0, 112, 144, 56));
  layer_add_child(window_get_root_layer(window), inverter_layer_get_layer(inverter_layer));
  
  // Draws ground
  ground = bitmap_layer_create(GRect(16, 21, 112, 122));
  bitmap_layer_set_bitmap(ground, s_example_bitmap_4);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(ground));
  
  // Draws yorp
  yorp = bitmap_layer_create(GRect(16, 21, 58, 90));
  bitmap_layer_set_bitmap(yorp, s_example_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(yorp));
  // Draws yorp_2
  yorp_2 = bitmap_layer_create(GRect(16, 21, 166, 90));
  bitmap_layer_set_bitmap(yorp_2, s_example_bitmap_2);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(yorp_2));
  // Draws yorp_3
  yorp_3 = bitmap_layer_create(GRect(16, 21, 112, 100));
  bitmap_layer_set_bitmap(yorp_3, s_example_bitmap_3);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(yorp_3));
  
  time_t now = time(NULL);
  handle_timechanges(localtime(&now), SECOND_UNIT);
  
  tick_timer_service_subscribe(SECOND_UNIT, handle_timechanges);
    
	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Hello World from the applogs!");
}

void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(text_layer);
	text_layer_destroy(date_layer);
  inverter_layer_destroy(inverter_layer);
  gbitmap_destroy(s_example_bitmap);
  gbitmap_destroy(s_example_bitmap_2);
  gbitmap_destroy(s_example_bitmap_3);
  gbitmap_destroy(s_example_bitmap_4);
  bitmap_layer_destroy(yorp);
  bitmap_layer_destroy(yorp_2);
  bitmap_layer_destroy(yorp_3);
  bitmap_layer_destroy(ground);
  
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}