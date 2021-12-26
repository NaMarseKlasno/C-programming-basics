#include <superkarel.h>
void turn_right();

int main(){
	turn_on("task_1.kw");
	
	set_step_delay(100);
	put_beeper();
	if(front_is_blocked() && left_is_blocked() && right_is_blocked()){
        	turn_left();
               	turn_left();
        }
        else if(front_is_blocked() && right_is_blocked()){
        	turn_left();
    	}
      	else if(right_is_clear()){
           	turn_right();
        }
       	step();


	while(no_beepers_present()){
		if(front_is_blocked() && left_is_blocked() && right_is_blocked()){
			turn_left();
			turn_left();
		}
		else if(front_is_blocked() && right_is_blocked()){
			turn_left();
		}
		else if(right_is_clear()){
			turn_right();
		}
		step();
	}
 	if(beepers_present()){	
		pick_beeper();
		while(not_facing_west()){
			turn_left();
		}
	}	
	while(no_beepers_present()){
        	if(front_is_blocked() && left_is_blocked() && right_is_blocked()){
                        turn_left();
                        turn_left();
                }
                else if(front_is_blocked() && right_is_blocked()){
                        turn_left();
                }
                else if(left_is_clear()){
                        turn_left();
                }
		else if(front_is_blocked() && right_is_clear())
			turn_right();
		step();
		
	}
	pick_beeper();
	while(not_facing_west()){
		turn_right();
	}


	turn_off();
	return 0;
}

void turn_right(){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(100);
	turn_left();
}
