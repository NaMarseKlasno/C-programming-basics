#include <superkarel.h>

void turn_around();
void turn_n();
void turn_s();
void turn_w();
void turn_e();
void turn_right();
void check_area();
void beeper_in_west();

bool one_beeper();
bool two_beeper();


int main(){
	turn_on("task_7.kw");
	set_step_delay(75);
	while(front_is_clear()){
		put_beeper();
		put_beeper();
		step();
	}
	turn_around();
	put_beeper();
	put_beeper();
	while(front_is_clear()){
		step();
	}	
	turn_around();
	
	while(1){
		if(front_is_clear())
			turn_n();
		else{
			break;
		}
		if(front_is_clear()){
			pick_beeper();
			step();
			check_area();
			turn_e();
			if(beepers_present()){
				if(one_beeper()){
					turn_w();
					step();
					while(front_is_clear()){
						while(beepers_present())
							pick_beeper();
						step();
					}
					turn_around();
					while(no_beepers_present())
						step();
					pick_beeper();
					if(front_is_clear())
						step();
					else{
						break;
					}
				}
				else if(two_beeper()){
					turn_n();
					step();
					if(right_is_blocked() && left_is_blocked()){
						put_beeper();
					}
					turn_s();
					step();
					turn_w();
					pick_beeper();
					beeper_in_west();	
					turn_e();
					while(beepers_present())
						pick_beeper();
					if(front_is_clear()){
						step();
						if(front_is_blocked()){	
							while(beepers_present()){
                                                		pick_beeper();
							}
						}	
					}	
					else{
						while(beepers_present()){
                                                	pick_beeper();
						}	
						break;
					}
				}
			}

		}
		else{
			turn_e();
		        while(beepers_present())
                        	pick_beeper();
			if(front_is_clear())
				step();
			else if(front_is_blocked() && facing_east()){
				break;
			}	
		}
			
	}
	
	turn_off();
}
void beeper_in_west(){
	if(front_is_clear())
		step();
	while(1){
		if(beepers_present()){
			if(one_beeper()){
				pick_beeper();
				turn_n();
				step();
				put_beeper();
				turn_around();
				step();
				turn_e();
				while(no_beepers_present() && front_is_clear()){
					step();
				}
				pick_beeper();
				break;
			}
			else{
				while(beepers_present())
					pick_beeper();
			}
			step();
		}	
		else{
			if(front_is_clear())
				step();
		}
	}
}



void check_area(){
	step();
	while(no_beepers_present()){
		if(beepers_present())
			break;
		if(front_is_clear() && left_is_blocked() && right_is_blocked()){
			step();
		}
		else if(front_is_blocked() && right_is_blocked() && left_is_blocked()){
			turn_around();
			step();
		}
		else if(right_is_blocked() && front_is_blocked()){
                        turn_left();
                        step();
                }

		else if(right_is_clear()){
			turn_right();
			step();
		}
		else if(right_is_blocked() && front_is_clear()){
                        step();
                }
		
	}
}

void turn_right(){
        turn_left();
        turn_left();
        turn_left();
}

void turn_n(){
        while(not_facing_north()){
        turn_left();
        }
}
void turn_s(){
        while(not_facing_south()){
                turn_left();
        }
}
void turn_e(){
        while(not_facing_east()){
                turn_left();
        }
}
void turn_w(){
        while(not_facing_west()){
                turn_left();
        }
}

void step_back(){
        turn_around();
        step();
        turn_around();
}

void turn_around(){
        set_step_delay(0);
        turn_left();
        set_step_delay(75);
        turn_left();
}

bool one_beeper(){
        if(beepers_present())
                pick_beeper();
        if(no_beepers_present()){
                put_beeper();
		return true;
        }
        else{
                put_beeper();
                return false;
        }
}


bool two_beeper(){
        if(beepers_present()){
                pick_beeper();
                pick_beeper();
        }
        if(no_beepers_present()){
                put_beeper();
		put_beeper();
		return true;
        }
        else{
                put_beeper();
                put_beeper();
                return false;
        }
}










