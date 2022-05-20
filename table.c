#include <stdio.h>

#define F_CPU 1000000
#define PRESCALER 64

#define C 261
#define Db 277
#define D 293
#define Eb 311
#define E 329
#define F 349
#define Gb 369
#define G 392
#define Ab 415
#define A 440
#define Bb 466
#define B 494
#define C1 523

int calculate_value_for_freq(int freq){
    double temp = (freq * PRESCALER * 2);
    temp /= (double) F_CPU;
    temp = 1.f/temp;
    return (255 - (int) temp);
}

void freq_ranges(int range[2]){
    range[0] = F_CPU / (PRESCALER * 2);
    range[1] = range[0] / 256;
}

int main(){
    int ranges[2];
    freq_ranges(ranges);

    int scale[13];

    scale[0] = calculate_value_for_freq(C);
    scale[1] = calculate_value_for_freq(Db);
    scale[2] = calculate_value_for_freq(D);
    scale[3] = calculate_value_for_freq(Eb);
    scale[4] = calculate_value_for_freq(E);
    scale[5] = calculate_value_for_freq(F);
    scale[6] = calculate_value_for_freq(Gb);
    scale[7] = calculate_value_for_freq(G);
    scale[8] = calculate_value_for_freq(Ab);
    scale[9] = calculate_value_for_freq(A);
    scale[10] = calculate_value_for_freq(Bb);
    scale[11] = calculate_value_for_freq(B);
    scale[12] = calculate_value_for_freq(C1);

    printf("%d %d\n", ranges[0], ranges[1]);
    for(int i = 0; i < 13; i++){
        printf("%d\n", scale[i]);
    }

    return 1;
}
