#include <superkarel.h>

void turn_right();
void turn_around();

int main(){
	turn_on("task_3.kw");
	
	set_step_delay(79);
	while(1){
		if(front_is_blocked() && left_is_blocked()){
                	turn_around();
			step();
			turn_left();
			while(1){	
				while(front_is_clear() && facing_north()){
					if(beepers_present()){
						continue;
					}
					if(no_beepers_present()){
						step();
					}	
				}
				if(no_beepers_present()){
					turn_around();
				}
				while(front_is_clear() && facing_south()){
					step();
				}
				if(no_beepers_present()){
					turn_left();
					step();
					turn_left();
				break;	
				}	
			}	
		while(front_is_clear()){
			step();
		}
		turn_left();
		while(front_is_clear()){
			step();
		}
		turn_around();
                break;
		}
		while(beepers_present()){
			pick_beeper();
		}
		step();
		while(beepers_present()){
                        pick_beeper();
		}
		if (front_is_blocked()){
			turn_left();

			while(1){
				if(front_is_blocked() && left_is_blocked()){
					break;
				}
				else if(front_is_blocked() && facing_north()){
					turn_left();
					if(no_beepers_in_bag() == false )
						put_beeper();
					step();
					turn_right();			
				}
				else if(front_is_blocked() && facing_west()){
					turn_left();
					if(front_is_blocked()){
						turn_right();
						break;
					}
					else{
						step();
						turn_left();
					}	
				}
				else if(front_is_clear() && facing_east()){
					break;
				}
				else{
					step();
					if(beepers_present()){
						turn_around();
						step();
						if(no_beepers_in_bag() == false)
							put_beeper();
						turn_right();
						step();
						turn_right();
					}	
					else{
						turn_around();
						step();
						turn_right();
						if(front_is_blocked() && facing_west()){
							continue; 
						}
						else{	
							step();
							turn_right();
						}	

					}	
					
				}
			}
		}
			
	}

	turn_off();
		
}

void turn_right(){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(79);
	turn_left();
}

void turn_around(){
	set_step_delay(0);
	turn_left();
	set_step_delay(79);
	turn_left();
}
