// Andrew Brownback
// 04/03/2022
// Wack-A-Mole FSM Theoretical Code

typdef enum {			// Set of states enumerated
       game_off,
       mole_up,
       moles_dowm,
       } state_e;

typedef enum {			//click events defined
	CLICK_START_EVENT,
	WACK_EVENT,
    HIT_EVENT,
	TIMER1_EVENT,
    TIMER2_EVENT,
	MAX_EVENTS
	} event_e;

state_e state = game_off;	
state_e next_state;
event_e event;
int score = 0; 
while(1)			
{
	event = read_event();
	if (state == game_off)
	{
		if (event == CLICK_START_EVENT)
		{
			next_state == mole_up_event_handler();
		}
	else if (state == mole_up)
	{
		if (event == WACK_EVENT)
		{
			next_state == moles_down_event_handler();
            score += 1;
		}
        else if(event == TIMER2_EVENT)
        {
            next_state = moles_down_event_handler(); 
			miss -= 1;
        }
	else if (state == moles_down)
	{
		if (event == TIMER2_EVENT|| miss>=3)//timer 2 ending ends the game or 3 misses
		{
			next_state == game_off_event_handler();
		}
        else if (event == TIMER1_EVENT)//timer 1 ending goes back to mole up
        {
            
            next_state = mole_up_event_handler(); 
        }
	}
	state = next_state;
    printf("You scored: %d!", score); 
