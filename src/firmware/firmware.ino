/*
PINS:
1, 2, 4, 5, 6, 7, 9, 10 - keys
11 - patern
12 - pitch
14 - write
15 - play
16 - clock in

TODO:
test it lol
 */

#define MODE_PITCH 1
#define MODE_PATERN 2
#define MODE_WRITE 3

#define PUSH(VARIABLE, PIN) VARIABLE = !VARIABLE && digitalRead(PIN) == HIGH ? true : VARIABLE; VARIABLE = VARIABLE && digitalRead(PIN) == LOW ? false : VARIABLE
#define MODE(MODE, PIN) mode = digitalRead(PIN) == HIGH ? MODE : mode

// TODO pitches
float pitches[8] = {0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1};

int mode = MODE_PITCH;
int pitch = 0;
int paterns[8][8];

int patern = 0;
int note = 0;

bool isPlaying = false;
bool retreivedGate = false;

const int keys[8]= {1, 2, 4, 5, 6, 7, 9, 10};

void setup()
{
    const int pins[13] = {1, 2, 4, 5, 6, 7, 9, 10, 11, 12, 14, 15, 16};
    for (int index = 0; index < 12; index++) {
        pinMode(pins[index], INPUT);
    }

    pinMode(32, OUTPUT);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            paterns[row][col] = 0;
        }
    }
}

void loop()
{
    PUSH(isPlaying, 15);
    PUSH(retreivedGate, 16);
    
    MODE(MODE_WRITE, 14);
    MODE(MODE_PITCH, 12);
    MODE(MODE_PATERN, 11);

    if (isPlaying && retreivedGate) {
        digitalWrite(32, paterns[patern][note]);
        note++;
        if (note == 8) {
            note = 0;
        }
    }

    for (int index = 0; index < 8; index++) {
        if (digitalRead(keys[index]) == HIGH) {
            switch (mode) {
                case MODE_WRITE:
                    paterns[patern][index] = paterns[patern][index] == 0 ? pitches[pitch] : 0;

                    break;
                case MODE_PITCH:
                    pitch = pitches[index]; 
                    digitalWrite(32, pitches[index]);

                    break;           
                case MODE_PATERN:
                    patern = index;

                    break; 
            }
        }
    }
}

