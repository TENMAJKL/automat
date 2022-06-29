/*
PINS:
1, 2, 4, 5, 6, 7, 9, 10 (0-7) - keys
11 (8) - patern
12 (9) - pitch
14 (10) - write
15 (11) - play
16 (12) - clock in

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
    for (int index = 0; index < 12; index++) {
        pinMode(index, INPUT);
    }

    pinMode(26, OUTPUT);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            paterns[row][col] = 0;
        }
    }
}

void loop()
{
    PUSH(isPlaying, 11);
    PUSH(retreivedGate, 12);
    
    MODE(MODE_WRITE, 10);
    MODE(MODE_PITCH, 9);
    MODE(MODE_PATERN, 8);

    if (isPlaying && retreivedGate) {
        analogWrite(32, paterns[patern][note]);
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
                    analogWrite(26, pitches[index]);

                    break;           
                case MODE_PATERN:
                    patern = index;

                    break; 
            }
        }
    }
}

