#include<allegro.h>
#include<alpng.h>
#include<time.h>
#include<windows.h>
#include<string>
#include<cstring>

BITMAP* buffer;
BITMAP* keen1;
BITMAP* keen2;
BITMAP* keen3;
BITMAP* keen4;
BITMAP* keen5;
BITMAP* keen6;

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


void update(){

   if(key[KEY_F])ShellExecute(NULL, "open", dosbox_dir, keen_1, NULL, SW_SHOWDEFAULT);



}

void draw(){


     rectfill(buffer,0,0,1024,768,makecol(255,255,255));
    draw_sprite(buffer,keen1,20,20);
    draw_sprite(buffer,keen3,20,240);
    draw_sprite(buffer,keen4,20,460);
    draw_sprite(buffer,keen2,360,20);
    draw_sprite(buffer,keen5,360,240);
    draw_sprite(buffer,keen6,360,470);

    draw_sprite(screen,buffer,0,0);




}







void setup(){
    buffer=create_bitmap(1024,768);


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
}






int main(){

  allegro_init();
  alpng_init();
  install_timer();
  install_keyboard();
  install_mouse();
  set_color_depth(32);


  set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768, 0, 0);
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
