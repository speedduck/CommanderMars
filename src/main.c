#include <pebble.h>

Window *window;
TextLayer *text_layer;
TextLayer *date_layer;
InverterLayer *inverter_layer;
static BitmapLayer *ground;
static GBitmap *bitmap_1;
static GBitmap *bitmap_2;
static GBitmap *bitmap_3;
static GBitmap *bitmap_4;
static GBitmap *bitmap_5;
static GBitmap *bitmap_6;
static GBitmap *bitmap_7;
static GBitmap *bitmap_8;
static GBitmap *bitmap_9;
int a = 0;

void handle_timechanges(struct tm *tick_time, TimeUnits units_changed) {
  static char time_buffer[10];
  static char date_buffer[10];
  
  strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", tick_time);
  text_layer_set_text(text_layer, time_buffer);
  
  strftime(date_buffer, sizeof(date_buffer), "%b %e", tick_time);
  text_layer_set_text(date_layer, date_buffer);
  a++;
  switch(a){
    case 1:
      bitmap_layer_set_bitmap(ground, bitmap_1);
      break;
    case 2:
      bitmap_layer_set_bitmap(ground, bitmap_2);
      break;
    case 3:
      bitmap_layer_set_bitmap(ground, bitmap_3);
      break;
    case 4:
      bitmap_layer_set_bitmap(ground, bitmap_4);
      break;
    case 5:
      bitmap_layer_set_bitmap(ground, bitmap_5);
      break;
    case 6:
      bitmap_layer_set_bitmap(ground, bitmap_6);
      break;
    case 7:
      bitmap_layer_set_bitmap(ground, bitmap_7);
      break;
    case 8:
      bitmap_layer_set_bitmap(ground, bitmap_8);
      break;
    case 9:
      bitmap_layer_set_bitmap(ground, bitmap_9);
      break;
  }
  if(a==9)a=0;
}

void handle_init(void) {
  // Creates images resource
  bitmap_1 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND1);
  bitmap_2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND2);
  bitmap_3 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND3);
  bitmap_4 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND4);
  bitmap_5 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND5);
  bitmap_6 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND6);
  bitmap_7 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND7);
  bitmap_8 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND8);
  bitmap_9 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND9);
  
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
  ground = bitmap_layer_create(GRect(0, 56, 144, 56));
  bitmap_layer_set_bitmap(ground, bitmap_1);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(ground));
  
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
  gbitmap_destroy(bitmap_1);
  bitmap_layer_destroy(ground);
  
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}