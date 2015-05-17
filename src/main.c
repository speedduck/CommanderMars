#include <pebble.h>

Window *window;
TextLayer *text_layer;
TextLayer *date_layer;
InverterLayer *inverter_layer;
static BitmapLayer *ground;
static BitmapLayer *yorp_left;
static BitmapLayer *yorp_front;
static BitmapLayer *yorp_right;
static GBitmap *bitmap_1;
static GBitmap *bitmap_2;
static GBitmap *bitmap_3;
static GBitmap *bitmap_4;
int a = 0;
int b = 0;
int c = 0;
GRect r1 = {{38, 63}, {16, 21}};
GRect r2 = {{64, 68}, {16, 21}};
GRect r3 = {{90, 63}, {16, 21}};
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
      r3.origin.y -= 3;
      break;
    case 2:
      r3.origin.y -= 2;
      bitmap_layer_set_bitmap(yorp_front, bitmap_4);
      break;
    case 3:
      r3.origin.y -= 2;
      r1.origin.y -= 3;
      break;
    case 4:
      r3.origin.y += 2;
      r1.origin.y -= 2;
      bitmap_layer_set_bitmap(yorp_front, bitmap_2);
    break;
    case 5:
      r3.origin.y += 2;
      r1.origin.y -= 2;
      break;
    case 6:
      r3.origin.y += 3;
      r1.origin.y += 2;
      bitmap_layer_set_bitmap(yorp_front, bitmap_3);
      break;
    case 7:
      r1.origin.y += 2;
    break;
    case 8:
      r1.origin.y += 3;
      break;
  }
  layer_set_frame(bitmap_layer_get_layer(yorp_right), r3);
  layer_set_frame(bitmap_layer_get_layer(yorp_left), r1);
  if(a==8)a=0;
}

static void jump(GRect r, struct BitmapLayer *yorp) {
  b++;
 switch(b){
    case 1:
      r.origin.y -= 3;
      break;
    case 2:
      r.origin.y -= 2;
      break;
    case 3:
      r.origin.y -= 2;
      break;
    case 4:
      r.origin.y += 2;
      break;
    case 5:
      r.origin.y += 2;
      break;
    case 6:
      r.origin.y += 3;
      break;
  }
  layer_set_frame(bitmap_layer_get_layer(yorp), r);
  if(b==6)b=0;
}

static void look(struct BitmapLayer *yorp, const struct GBitmap *bitmap1, const struct GBitmap *bitmap2, const struct GBitmap *bitmap3) {
  c++;
  switch(c){
    case 1:
      bitmap_layer_set_bitmap(yorp, bitmap1);
      break;
    case 2:
      bitmap_layer_set_bitmap(yorp, bitmap2);
      break;
    case 3:
      bitmap_layer_set_bitmap(yorp, bitmap3);
      break;
  }
  if(c==3)c=0;
}

void handle_init(void) {
  // Creates images resource
  bitmap_1 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND_TEMPLATE);
  bitmap_2 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_YL0);
  bitmap_3 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_YF0);
  bitmap_4 = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_YR0);
  
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
  yorp_left = bitmap_layer_create(r1);
  yorp_front = bitmap_layer_create(r2);
  yorp_right = bitmap_layer_create(r3);
  bitmap_layer_set_bitmap(ground, bitmap_1);
  bitmap_layer_set_bitmap(yorp_left, bitmap_2);
  bitmap_layer_set_bitmap(yorp_front, bitmap_3);
  bitmap_layer_set_bitmap(yorp_right, bitmap_4);
  Layer * l = window_get_root_layer(window);
  layer_add_child(l, bitmap_layer_get_layer(ground));
  layer_add_child(l, bitmap_layer_get_layer(yorp_left));
  layer_add_child(l, bitmap_layer_get_layer(yorp_front));
  layer_add_child(l, bitmap_layer_get_layer(yorp_right));
  
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
  gbitmap_destroy(bitmap_2);
  gbitmap_destroy(bitmap_3);
  gbitmap_destroy(bitmap_4);
  bitmap_layer_destroy(ground);
  bitmap_layer_destroy(yorp_left);
  bitmap_layer_destroy(yorp_front);
  bitmap_layer_destroy(yorp_right);
  
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}