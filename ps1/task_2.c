#include <superkarel.h>

void turn_right();
void turn_around();

int main(){
	turn_on("task_2.kw");
	
	set_step_delay(100);
	while ( no_beepers_present() ){
		if(front_is_blocked() && left_is_clear()){
			turn_left();
		}	
		else if( front_is_blocked() && right_is_clear() ){
			turn_right();
		}	
		step();	
	}	
	while (beepers_present()){
		pick_beeper();
	}	
	
	turn_around();
	step();
	while ( front_is_clear() || right_is_clear() || left_is_clear()  ){
                if(front_is_blocked() && left_is_clear()){
                        turn_left();
		}	
		else if( front_is_blocked() && right_is_clear() ){
                        turn_right();
		}	
       		step();
        }

		
	turn_off();
	return 0	
}

void turn_right(){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(100);
	turn_left();
}

void turn_around(){
	set_step_delay(0);
	turn_left();
	set_step_delay(100);
	turn_left();
}
