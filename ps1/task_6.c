#include <superkarel.h>
void turn_right();

bool if_one_beeper();
bool if_two_beeper();
bool if_tree_beeper();
bool if_four_beeper();
bool if_five_beeper();


void turn_n();
void turn_s();
void turn_w();
void turn_e();

int main(){
	turn_on("task_6.kw");
	set_step_delay(75);
	while(no_beepers_present()){
		step();
	}
	//how many beepers
	while(1){
		if(beepers_present() && if_one_beeper())
			turn_n();
		else if(beepers_present() && if_two_beeper())
			turn_w();
		else if(beepers_present() && if_tree_beeper())
                        turn_s();
		else if(beepers_present() && if_four_beeper())
                        turn_e();
		else if(beepers_present() && if_five_beeper())
                        break;
		step();
	}
	
	turn_off();
	return 0;
}

bool if_one_beeper(){
	if(beepers_present())
		pick_beeper();
	if(no_beepers_present()){
		return true;
	}
	else{
		put_beeper();
		return false;
	}
}	


bool if_two_beeper(){
	if(beepers_present()){
		pick_beeper();
		pick_beeper();
	}
	if(no_beepers_present()){
                return true;
        }
        else{
                put_beeper();
		put_beeper();
		return false;
        }
}	


bool if_tree_beeper(){
	if(beepers_present()){
        	pick_beeper();
		pick_beeper();
        	pick_beeper();
	}
        if(no_beepers_present()){
                return true;
        }
	else{
                put_beeper();
		put_beeper();
                put_beeper();
		return false;
        }
}	


bool if_four_beeper(){
	if(beepers_present()){
        	pick_beeper();
		pick_beeper();
        	pick_beeper();
		pick_beeper();
	}	
        if(no_beepers_present()){
                return true;
	}
        else{
                put_beeper();
                put_beeper();
		put_beeper();
                put_beeper();
                return false;
        }
}	
bool if_five_beeper(){
	if(beepers_present()){
        	pick_beeper();
		pick_beeper();
		pick_beeper();
        	pick_beeper();
        	pick_beeper();
	}
        if(no_beepers_present()){
                return true;
        }
        else{
                put_beeper();
                put_beeper();
                put_beeper();
		put_beeper();
                put_beeper();
                return false;

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










