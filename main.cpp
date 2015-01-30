#include<allegro.h>
#include<alpng.h>
#include<time.h>
#include<windows.h>
#include<string>
#include<cstring>

//SFfadsfkghldfj;
BITMAP* buffer;
BITMAP* keen1;
BITMAP* keen2;
BITMAP* keen3;
BITMAP* keen4;
BITMAP* keen5;
BITMAP* keen6;
BITMAP* cursor;

// Fonts
FONT* f1;
FONT* f2;
FONT* f3;
FONT* f4;
FONT* f5;
FONT* slabo;


using namespace std;

bool close_button_pressed;

// FPS System
volatile int ticks = 0;
const int updates_per_second = 60;
volatile int game_time = 0;

int fps;
int frames_done;
int old_time;

char* keen_1=".\\keen1\\KEEN1.EXE -fullscreen";
char* dosbox_dir="C:\\Program Files (x86)\\DOSBox-0.74\\DOSBox.exe";

void ticker(){
  ticks++;
}
END_OF_FUNCTION(ticker)

void game_time_ticker(){
  game_time++;
}
END_OF_FUNCTION(ticker)

void close_button_handler(void){
  close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

// Random number generator. Use int random(highest,lowest);
int random(int newLowest, int newHighest)
{
  int lowest = newLowest, highest = newHighest;
  int range = (highest - lowest) + 1;
  int randomNumber = lowest+int(range*rand()/(RAND_MAX + 1.0));
  return randomNumber;
}


//A function to streamline error reporting in file loading
void abort_on_error(const char *message){
	 set_window_title("Error!");
	 if (screen != NULL){
	    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	 }
	 allegro_message("%s.\n %s\n", message, allegro_error);
	 exit(-1);
}

//Check to see if an area is hovered
bool location_hovered(int min_x,int max_x,int min_y,int max_y){
    if(mouse_x>min_x && mouse_x<max_x && mouse_y>min_y && mouse_y<max_y)
        return true;
    else return false;
}

//Check to see if an area is clicked
bool location_clicked(int min_x,int max_x,int min_y,int max_y){
    if(mouse_x>min_x && mouse_x<max_x && mouse_y>min_y && mouse_y<max_y && mouse_b & 1)
        return true;
    else return false;
}

void update(){

   if(key[KEY_F])ShellExecute(NULL, "open", dosbox_dir, keen_1, NULL, SW_SHOWDEFAULT);



}

void draw(){


    rectfill(buffer,0,0,700,710,makecol(255,255,255));
    draw_sprite(buffer,keen1,20,50);
    draw_sprite(buffer,keen3,20,270);
    draw_sprite(buffer,keen5,20,490);
    draw_sprite(buffer,keen2,360,50);
    draw_sprite(buffer,keen4,360,270);
    draw_sprite(buffer,keen6,360,490);
    if(location_hovered(20,340,50,250))
     textout_centre_ex( buffer, slabo, "Launch Keen 1 \"Marooned on Mars\"", SCREEN_W/2, 10, makecol(0,0,0), -1);
    if(location_hovered(20,340,270,470))
     textout_centre_ex( buffer, slabo, "Launch Keen 3 \"Keen Must Die!\"", SCREEN_W/2, 10, makecol(0,0,0), -1);
    if(location_hovered(20,340,490,690))
     textout_centre_ex( buffer, slabo, "Launch Keen 5 \"The Armageddon Machine\"", SCREEN_W/2, 10, makecol(0,0,0), -1);
    if(location_hovered(360,680,50,250))
     textout_centre_ex( buffer, slabo, "Launch Keen 2 \"The Earth Explodes\"", SCREEN_W/2, 10, makecol(0,0,0), -1);
    if(location_hovered(360,680,270,470))
     textout_centre_ex( buffer, slabo, "Launch Keen 4 \"Goodbye Galaxy\"", SCREEN_W/2, 10, makecol(0,0,0), -1);
    if(location_hovered(360,680,490,690))
     textout_centre_ex( buffer, slabo, "Launch Keen 6 \"Aliens Ate My Babysitter\"", SCREEN_W/2, 10, makecol(0,0,0), -1);

    draw_sprite(buffer,cursor,mouse_x,mouse_y);

    draw_sprite(screen,buffer,0,0);




}







void setup(){
    buffer=create_bitmap(700,710);


    // Load fonts
    f1 = load_font("build\\slabo.pcx", NULL, NULL);
    f2 = extract_font_range(f1, ' ', 'A'-1);
    f3 = extract_font_range(f1, 'A', 'Z');
    f4 = extract_font_range(f1, 'Z'+1, 'z');
    slabo = merge_fonts(f4, f5 = merge_fonts(f2, f3));

    // Destroy temporary fonts
    destroy_font(f1);
    destroy_font(f2);
    destroy_font(f3);
    destroy_font(f4);
    destroy_font(f5);

    srand(time(NULL));

     // Setup for FPS system
    LOCK_VARIABLE(ticks);
    LOCK_FUNCTION(ticker);
    install_int_ex(ticker, BPS_TO_TIMER(updates_per_second));

    LOCK_VARIABLE(game_time);
    LOCK_FUNCTION(game_time_ticker);
    install_int_ex(game_time_ticker, BPS_TO_TIMER(10));

    // Close button
    LOCK_FUNCTION(close_button_handler);
    set_close_button_callback(close_button_handler);

   if (!(keen1 = load_bitmap("icons\\keen1.png", NULL)))
      abort_on_error("Cannot find image icons\\keen1.png\nPlease check your files and try again");
  if (!(keen2 = load_bitmap("icons\\keen2.png", NULL)))
      abort_on_error("Cannot find image icons\\keen2.png\nPlease check your files and try again");
  if (!(keen3 = load_bitmap("icons\\keen3.png", NULL)))
      abort_on_error("Cannot find image icons\\keen3.png\nPlease check your files and try again");
  if (!(keen4 = load_bitmap("icons\\keen4.png", NULL)))
      abort_on_error("Cannot find image icons\\keen4.png\nPlease check your files and try again");
  if (!(keen5 = load_bitmap("icons\\keen5.png", NULL)))
      abort_on_error("Cannot find image icons\\keen5.png\nPlease check your files and try again");
  if (!(keen6 = load_bitmap("icons\\keen6.png", NULL)))
      abort_on_error("Cannot find image icons\\keen6.png\nPlease check your files and try again");
  if (!(cursor = load_bitmap("build\\cursor.png", NULL)))
      abort_on_error("Cannot find image cursor.png\nPlease check your files and try again");
}






int main(){

  allegro_init();
  alpng_init();
  install_timer();
  install_keyboard();
  install_mouse();
  set_color_depth(32);


  set_gfx_mode(GFX_AUTODETECT_WINDOWED,700,710, 0, 0);
  install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,".");

  set_window_title("Keen Launcher");
  setup();


      while(!key[KEY_ESC] && !close_button_pressed){
        while(ticks == 0){
            rest(1);
        }
    while(ticks > 0){
        int old_ticks = ticks;

        update();

        ticks--;
        if(old_ticks <= ticks){
            break;
        }
    }
        if(game_time - old_time >= 10){
            fps = frames_done;
            frames_done = 0;
            old_time = game_time;
        }
        draw();
    }


	return 0;
}
END_OF_MAIN()
