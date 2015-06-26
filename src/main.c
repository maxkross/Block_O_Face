/*
*	A watch face made in the style of Ohio State's Block O
*	Block O is intellectual property of The Ohio State University
*	Custom digit design and watch face by Max Kross
* OH- 
*/

#include <pebble.h>

static Window *ohio_main_window;
static BitmapLayer *block_o_layer;
static GBitmap *block_o_bitmap;

#define TOTAL_DISPLAYED_DIGITS 4
#define NUMBER_OF_DIGITS 10
	
const int HOUR_TENS[6] = {
	RESOURCE_ID_0_0_BLACK, RESOURCE_ID_0_0_WHITE, 
	RESOURCE_ID_0_1_BLACK, RESOURCE_ID_0_1_WHITE, 
	RESOURCE_ID_0_2_BLACK, RESOURCE_ID_0_2_WHITE
};

const int HOUR_ONES[20] = {
	RESOURCE_ID_1_0_BLACK, RESOURCE_ID_1_0_WHITE, 
	RESOURCE_ID_1_1_BLACK, RESOURCE_ID_1_1_WHITE, 
	RESOURCE_ID_1_2_BLACK, RESOURCE_ID_1_2_WHITE, 
	RESOURCE_ID_1_3_BLACK, RESOURCE_ID_1_3_WHITE, 
	RESOURCE_ID_1_4_BLACK, RESOURCE_ID_1_4_WHITE, 
	RESOURCE_ID_1_5_BLACK, RESOURCE_ID_1_5_WHITE, 
	RESOURCE_ID_1_6_BLACK, RESOURCE_ID_1_6_WHITE, 
	RESOURCE_ID_1_7_BLACK, RESOURCE_ID_1_7_WHITE, 
	RESOURCE_ID_1_8_BLACK, RESOURCE_ID_1_8_WHITE, 
	RESOURCE_ID_1_9_BLACK, RESOURCE_ID_1_9_WHITE
};

const int MINUTE_TENS[12] = {
	RESOURCE_ID_2_0_BLACK, RESOURCE_ID_2_0_WHITE, 
	RESOURCE_ID_2_1_BLACK, RESOURCE_ID_2_1_WHITE, 
	RESOURCE_ID_2_2_BLACK, RESOURCE_ID_2_2_WHITE, 
	RESOURCE_ID_2_3_BLACK, RESOURCE_ID_2_3_WHITE, 
	RESOURCE_ID_2_4_BLACK, RESOURCE_ID_2_4_WHITE, 
	RESOURCE_ID_2_5_BLACK, RESOURCE_ID_2_5_WHITE, 
};

const int MINUTE_ONES[20] = {
	RESOURCE_ID_3_0_BLACK, RESOURCE_ID_3_0_WHITE, 
	RESOURCE_ID_3_1_BLACK, RESOURCE_ID_3_1_WHITE, 
	RESOURCE_ID_3_2_BLACK, RESOURCE_ID_3_2_WHITE, 
	RESOURCE_ID_3_3_BLACK, RESOURCE_ID_3_3_WHITE, 
	RESOURCE_ID_3_4_BLACK, RESOURCE_ID_3_4_WHITE, 
	RESOURCE_ID_3_5_BLACK, RESOURCE_ID_3_5_WHITE, 
	RESOURCE_ID_3_6_BLACK, RESOURCE_ID_3_6_WHITE, 
	RESOURCE_ID_3_7_BLACK, RESOURCE_ID_3_7_WHITE, 
	RESOURCE_ID_3_8_BLACK, RESOURCE_ID_3_8_WHITE, 
	RESOURCE_ID_3_9_BLACK, RESOURCE_ID_3_9_WHITE
};


	
static GBitmap *digit1_black;
static GBitmap *digit1_white;
static BitmapLayer *digit1_black_layer;
static BitmapLayer *digit1_white_layer;
static GBitmap *digit2_black;
static GBitmap *digit2_white;
static BitmapLayer *digit2_black_layer;
static BitmapLayer *digit2_white_layer;
static GBitmap *digit3_black;
static GBitmap *digit3_white;
static BitmapLayer *digit3_black_layer;
static BitmapLayer *digit3_white_layer;
static GBitmap *digit4_black;
static GBitmap *digit4_white;
static BitmapLayer *digit4_black_layer;
static BitmapLayer *digit4_white_layer;

static unsigned short get_display_hour(unsigned short hour) {
  if (clock_is_24h_style()) {
    return hour;
  }

  unsigned short display_hour = hour % 12;

  // Converts "0" to "12"
  return display_hour ? display_hour : 12;

}

static void unload_digit_image_from_slot(int slot_number) {
  
		switch(slot_number){
			case 0:
				layer_remove_from_parent(bitmap_layer_get_layer(digit1_white_layer));
				bitmap_layer_destroy(digit1_white_layer);
				gbitmap_destroy(digit1_white);
				layer_remove_from_parent(bitmap_layer_get_layer(digit1_black_layer));
				bitmap_layer_destroy(digit1_black_layer);
				gbitmap_destroy(digit1_black);
				break;
			case 1:
				layer_remove_from_parent(bitmap_layer_get_layer(digit2_white_layer));
				bitmap_layer_destroy(digit2_white_layer);
				gbitmap_destroy(digit2_white);
				layer_remove_from_parent(bitmap_layer_get_layer(digit2_black_layer));
				bitmap_layer_destroy(digit2_black_layer);
				gbitmap_destroy(digit2_black);
				break;
			case 2:
				layer_remove_from_parent(bitmap_layer_get_layer(digit3_white_layer));
				bitmap_layer_destroy(digit3_white_layer);
				gbitmap_destroy(digit3_white);
				layer_remove_from_parent(bitmap_layer_get_layer(digit3_black_layer));
				bitmap_layer_destroy(digit3_black_layer);
				gbitmap_destroy(digit3_black);
				break;
			case 3:
				layer_remove_from_parent(bitmap_layer_get_layer(digit4_white_layer));
				bitmap_layer_destroy(digit4_white_layer);
				gbitmap_destroy(digit4_white);
				layer_remove_from_parent(bitmap_layer_get_layer(digit4_black_layer));
				bitmap_layer_destroy(digit4_black_layer);
				gbitmap_destroy(digit4_black);
				break;
			default:
				break;
		}
}

static void load_digit_image_into_slot(int slot_number, int digit_value) {
  /*
   * Loads the digit image from the application's resources and
   * displays it on-screen in the correct location.
   *
	 */

	
	switch(slot_number){
		case 0:
			digit1_white = gbitmap_create_with_resource(HOUR_TENS[(digit_value*2)+1]);
			digit1_white_layer = bitmap_layer_create(GRect(5,64,28,63));
			bitmap_layer_set_bitmap(digit1_white_layer,digit1_white);
			bitmap_layer_set_compositing_mode(digit1_white_layer, GCompOpOr);
			layer_add_child(bitmap_layer_get_layer(block_o_layer), bitmap_layer_get_layer(digit1_white_layer));
			digit1_black = gbitmap_create_with_resource(HOUR_TENS[(digit_value*2)]);
			digit1_black_layer = bitmap_layer_create(GRect(5,64,28,63));
			bitmap_layer_set_bitmap(digit1_black_layer,digit1_black);
			bitmap_layer_set_compositing_mode(digit1_black_layer, GCompOpClear);
			layer_add_child(bitmap_layer_get_layer(block_o_layer), bitmap_layer_get_layer(digit1_black_layer));
			break;
		case 1:
			digit2_white = gbitmap_create_with_resource(HOUR_ONES[(digit_value*2)+1]);
			digit2_white_layer = bitmap_layer_create(GRect(36,55,25,58));
			bitmap_layer_set_bitmap(digit2_white_layer,digit2_white);
			bitmap_layer_set_compositing_mode(digit2_white_layer, GCompOpOr);
			layer_add_child(bitmap_layer_get_layer(block_o_layer), bitmap_layer_get_layer(digit2_white_layer));
			digit2_black = gbitmap_create_with_resource(HOUR_ONES[(digit_value*2)]);
			digit2_black_layer = bitmap_layer_create(GRect(36,55,25,58));
			bitmap_layer_set_bitmap(digit2_black_layer,digit2_black);
			bitmap_layer_set_compositing_mode(digit2_black_layer, GCompOpClear);
			layer_add_child(bitmap_layer_get_layer(block_o_layer), bitmap_layer_get_layer(digit2_black_layer));
			break;
		case 2:
			digit3_white = gbitmap_create_with_resource(MINUTE_TENS[(digit_value*2)+1]);
			digit3_white_layer = bitmap_layer_create(GRect(80,55,35,58));
			bitmap_layer_set_bitmap(digit3_white_layer,digit3_white);
			bitmap_layer_set_compositing_mode(digit3_white_layer, GCompOpOr);
			layer_add_child(bitmap_layer_get_layer(block_o_layer), bitmap_layer_get_layer(digit3_white_layer));
			digit3_black = gbitmap_create_with_resource(MINUTE_TENS[(digit_value*2)]);
			digit3_black_layer = bitmap_layer_create(GRect(80,55,35,58));
			bitmap_layer_set_bitmap(digit3_black_layer,digit3_black);
			bitmap_layer_set_compositing_mode(digit3_black_layer, GCompOpClear);
			layer_add_child(bitmap_layer_get_layer(block_o_layer), bitmap_layer_get_layer(digit3_black_layer));
			break;
		case 3:
			digit4_white = gbitmap_create_with_resource(MINUTE_ONES[(digit_value*2)+1]);
			digit4_white_layer = bitmap_layer_create(GRect(113,64,28,63));
			bitmap_layer_set_bitmap(digit4_white_layer,digit4_white);
			bitmap_layer_set_compositing_mode(digit4_white_layer, GCompOpOr);
			layer_add_child(bitmap_layer_get_layer(block_o_layer), bitmap_layer_get_layer(digit4_white_layer));
			digit4_black = gbitmap_create_with_resource(MINUTE_ONES[(digit_value*2)]);
			digit4_black_layer = bitmap_layer_create(GRect(113,64,28,63));
			bitmap_layer_set_bitmap(digit4_black_layer,digit4_black);
			bitmap_layer_set_compositing_mode(digit4_black_layer, GCompOpClear);
			layer_add_child(bitmap_layer_get_layer(block_o_layer), bitmap_layer_get_layer(digit4_black_layer));
			break;
		default:
			break;			
	}
}

static void display_value(unsigned short value, unsigned short row_number) {
  value = value % 100; // Maximum of two digits per row.

  // Slot Order is: 0 | 1 | 2 | 3
  // (We process the slots in reverse order because that makes
  // extracting the digits from the value easier.)
  for (int column_number = 1; column_number >= 0; column_number--) {
    int slot_number = (row_number * 2) + column_number;
    unload_digit_image_from_slot(slot_number);
		load_digit_image_into_slot(slot_number, value % 10);
    value = value / 10;
  }
}

static void display_time(struct tm *tick_time) {
  display_value(get_display_hour(tick_time->tm_hour), 0);
  display_value(tick_time->tm_min, 1);
}

static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
  display_time(tick_time);
}


static void main_window_load(Window *window) {
	time_t now = time(NULL);
  struct tm *tick_time = localtime(&now);
	block_o_bitmap = gbitmap_create_with_resource(RESOURCE_ID_block_o_background);
	block_o_layer = bitmap_layer_create(GRect(0,0,144,168));
	bitmap_layer_set_bitmap(block_o_layer, block_o_bitmap);
	layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(block_o_layer));
  display_time(tick_time);

  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
	
}

static void main_window_unload(Window *window){
	for(int k = 0;k <  TOTAL_DISPLAYED_DIGITS; k++){
		unload_digit_image_from_slot(k);
	}
	layer_remove_from_parent(bitmap_layer_get_layer(block_o_layer));
	gbitmap_destroy(block_o_bitmap);
	bitmap_layer_destroy(block_o_layer);
}
	
	
static void init(void) {
  ohio_main_window = window_create();
	window_set_window_handlers(ohio_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  window_stack_push(ohio_main_window, true);
}

static void deinit(void) {
  window_destroy(ohio_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
