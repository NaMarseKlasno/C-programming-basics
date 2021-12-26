#include <superkarel.h>

void turn_right();
void turn_around();

bool front_is_beepers();
bool b_is_beepers();
bool l_is_beepers();
bool r_is_beepers();

void turn_n();
void turn_s();
void turn_w();
void turn_e();

void turn_ldown();
void turn_rup();
void step_back();
void find_midle_west();
void find_midle_north();

int main(){
	turn_on("task_5.kw");
	set_step_delay(40);
	
	while(1){	
		while(no_beepers_present()){
			while(not_facing_north()){
				turn_left();
			}
			while(front_is_clear()){
				step();
			}
			// TURN N && IN THE RIGHT SIDE
			if(right_is_blocked()){
				while(front_is_clear()){
					step();
				}
				turn_left();
				put_beeper();
			}
			// TURN N && IN THE LEFT OF CENTER SIDE
			else{
				while(front_is_clear()){
					step();
				}
				turn_right();
				while(front_is_clear()){
	                                step();
	                        }
				turn_around();
				put_beeper();	
			}
		}
		//PUTTING BEEPERS ON MAP
		step();
		while(no_beepers_present()){
			put_beeper();
			if(front_is_blocked()){
				turn_left();
			}
			step();
		}
		turn_around();
		step();
		turn_right();
		while(1){	
			if(front_is_beepers() == false){
				step();
				if(front_is_beepers() && r_is_beepers() && l_is_beepers() && b_is_beepers()){
					turn_n();
					break;
				}
				else{
					turn_around();
					step();
					turn_around();
					turn_left();
					break;
				}

			}
		}
		if(facing_north() && no_beepers_present()){
			break;
		}
		find_midle_west();
		pick_beeper();
		pick_beeper();
		turn_around();
		step();
		put_beeper();
		put_beeper();
		turn_ldown();
		while(front_is_clear()){
			step();
			pick_beeper();
		}
		put_beeper();
		turn_around();
		step();
		while(no_beepers_present()){
			step();
		}
		turn_w();
		while(front_is_clear()){
			if(no_beepers_present())
				put_beeper();
			step();
		}
		turn_around();	
		turn_left();
		turn_rup();
		//hard code	
		find_midle_north();	
		turn_rup();
		while(front_is_clear()){
                        step();
                        pick_beeper();
                }
		turn_around();
		put_beeper();
		step();
		while(no_beepers_present())
			step();
		pick_beeper();
		pick_beeper();
		turn_n();
		step();
		put_beeper();
		put_beeper();
		turn_ldown();
		while(front_is_clear()){
                        step();
                        pick_beeper();
                }
                put_beeper();
		turn_around();
		step();
		while(no_beepers_present())
                        step();
		pick_beeper();
		turn_s();
		step();
		turn_n();
		//konec)))!!!YPAAAA)))
		break;

	}
	turn_off();
	return 0;
}

void find_midle_west(){
	while(1){
		if(facing_east() && r_is_beepers() && l_is_beepers()){
     			break;
                }

	        if(no_beepers_present() && r_is_beepers() && l_is_beepers() && b_is_beepers()){
                	break;
                }//
			
		if(r_is_beepers() == false){
			turn_right();
			step();
			if(r_is_beepers() && l_is_beepers() && b_is_beepers()){
                     		step_back();
				put_beeper();
				put_beeper();
				turn_around();
				break;
                        }
			put_beeper();
			step_back();
		}
		else{
			while(beepers_present()){
                                while(not_facing_south())
					turn_left();
                                step();
                                if(r_is_beepers() == false){
                                        turn_right();
                                        step();
					if(r_is_beepers() && l_is_beepers() && b_is_beepers()){
                                		step_back();
						put_beeper();
                                		put_beeper();
						turn_around();
                                		break;
                       			 } 
                                        put_beeper();
                                        step_back();
                                        break;
                                }
                        }

		}
		if(facing_east() && r_is_beepers() && l_is_beepers()){
                        break;
                }

		turn_ldown();
		if(l_is_beepers() == false){
			turn_left();
			step();
			if(r_is_beepers() && l_is_beepers() && b_is_beepers()){
                                step_back();
				put_beeper();
                                put_beeper();
				turn_around();
                        	break;
                        }
			put_beeper();
			step_back();
		}
		else{
			while(beepers_present()){
				while(not_facing_north())
					turn_left();
				step();
				if(l_is_beepers() == false){
                	        	turn_left();
                	        	step();
					if(r_is_beepers() && l_is_beepers() && b_is_beepers()){
                          		      	step_back();
						put_beeper();
                                		put_beeper();
						turn_around();
                                		break;
                        		}
                	        	put_beeper();
                	        	step_back();
					turn_rup();
					break;
				}
			}
			if(facing_east() && r_is_beepers() && l_is_beepers()){
                        	break;
            		}
		
		}
	}
}
void turn_ldown(){
	turn_left();
	while(front_is_clear())
		step();
	turn_around();
}

void turn_rup(){
	turn_right();
	while(front_is_clear())
		step();
	turn_around();
}

void step_back(){
	turn_around();
	step();
	turn_around();
}

bool front_is_beepers(){
	step();
	if(beepers_present()){
		turn_around();
	        step();
        	turn_around();
		return true;
	}	
	else{
		turn_around();
       	 	step();
        	turn_around();
		return false;
	}	
}
bool r_is_beepers(){
	turn_right();
	step();
	if(beepers_present()){
                turn_around();
                step();
                turn_right();
                return true;
        }
        else{
                turn_around();
                step();
                turn_right();
                return false;
        }
}

bool l_is_beepers(){
	turn_left();
	step();
	if(beepers_present()){
                turn_around();
                step();
                turn_left();
                return true;
        }
        else{
                turn_around();
                step();
                turn_left();
                return false;
        }
}

bool b_is_beepers(){
	turn_around();
	step();
	if(beepers_present()){
                turn_around();
                step();
                return true;
        }
        else{
                turn_around();
                step();
                return false;
        }
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

void turn_w(){
        while(not_facing_west()){
                turn_left();
        }
}
void turn_e(){
        while(not_facing_east()){
                turn_left();
        }
}

void turn_right(){
	set_step_delay(0);
	turn_left();
	turn_left();
	set_step_delay(40);
	turn_left();
}

void turn_around(){
	set_step_delay(40);
        turn_left();
        set_step_delay(40);
        turn_left();
}

void find_midle_north(){
        while(1){
                if(facing_north() && r_is_beepers() && l_is_beepers()){
                        break;
                }
                if(r_is_beepers() == false){
                        turn_right();
                        step();
                        put_beeper();
                        step_back();
                }
                else{
                        while(beepers_present()){
                                while(not_facing_west())
                                        turn_left();
                                step();
                                if(r_is_beepers() == false){
                                        turn_right();
                                        step();
                                        if(r_is_beepers() && l_is_beepers() && b_is_beepers()){
                                                step_back();
                                                put_beeper();
                                                put_beeper();
                                                turn_around();
                                                break;
                                         }
                                        put_beeper();
                                        step_back();
                                        break;
                                }
                        }

                }
                if(facing_south() && r_is_beepers() && l_is_beepers()){
                        break;
                }

                turn_ldown();
                if(l_is_beepers() == false){
                        turn_left();
                        step();
                        if(r_is_beepers() && l_is_beepers() && b_is_beepers()){
                                step_back();
                                put_beeper();
                                put_beeper();
                                turn_around();
                                break;
                        }
                        put_beeper();
                        step_back();
                }
                else{
                        while(beepers_present()){
                                while(not_facing_east())
                                        turn_left();
                                step();
                                if(l_is_beepers() == false){
                                        turn_left();
                                        step();
                                        if(r_is_beepers() && l_is_beepers() && b_is_beepers()){
                                                step_back();
                                                put_beeper();
                                                put_beeper();
                                                turn_around();
                                                break;
                                        }
                                        put_beeper();
                                        step_back();
                                        turn_rup();
                                        break;
                                }
                        }
                        if(facing_south() && r_is_beepers() && l_is_beepers()){
                                break;
                        }

                }
        }
}


