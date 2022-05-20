#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define T0_PRESCALER 64
#define OUTPUT PB0

#define C 226
#define Db 227
#define D 229
#define Eb 230
#define E 232
#define F 233
#define Gb 234
#define G 236
#define Ab 237
#define A 238
#define Bb 239
#define B 240
#define C1 241

//freq = F_CPU/prescaler/special_val/2
// Sets the freq of timer
int channel0_val;
int channel0_enable;

ISR (TIMER0_OVF_vect){
    PORTB ^= (1 << OUTPUT);
    TCNT0 = channel0_val;
}

void init_timer0(){
    // Disabled at first
    TCCR0 = 0;

    // Enable timer0 overflow interrupt
    TIMSK = (1 << TOIE0);

    DDRB = (1 << OUTPUT);
}

void channel0_start(int freq){
    if(channel0_enable)
        return;

    channel0_val = freq;

    // Prescaler /64
    TCCR0 = (1 << CS00) | (1 << CS01);
    TCNT0 = channel0_val;

    channel0_enable = 1;
}

void channel0_end(){
    TCCR0 = 0;
    channel0_enable = 0;
}

void channel0_play_song(char *song, int len){
    for(int i = 0; i < len; i += 2){
        channel0_start(song[i]);
        switch(song[i + 1]){
            case 0:
                _delay_ms(250);
                break;
            case 1:
                _delay_ms(500);
                break;
            case 2:
                _delay_ms(750);
                break;
            case 3:
            default:
                _delay_ms(1000);
                break;
        }
        channel0_end();
        _delay_ms(25);
    }
}

int main(void){
    init_timer0();
    PORTD = 0xff;

    sei();

    while(1){
        if(!(PIND & (1 << 0))){
            channel0_start(C);
        } 
        else if(!(PIND & (1 << 1))){
            channel0_start(D);
        }else if(!(PIND & (1 << 2))){
            channel0_start(E);
        }else if(!(PIND & (1 << 3))){
            channel0_start(F);
        }else if(!(PIND & (1 << 4))){
            channel0_start(G);
        }else if(!(PIND & (1 << 5))){
            channel0_start(A);
        }else if(!(PIND & (1 << 6))){
            channel0_start(B);
        }else if(!(PIND & (1 << 7))){
            channel0_start(C1);
        }
        else {
            channel0_end();
        }
        /*
        char song[] = {E, 0, E, 0, F, 0, G, 0, G, 0, F, 0, E, 0, D, 0, C, 0, C, 0, D, 0, E, 0, D, 2, C, 1, C, 4};
        channel0_play_song(song, sizeof(song));
        */
    }
}
