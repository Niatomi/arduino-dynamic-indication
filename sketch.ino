const byte digit_pins[4] = {4,2,3,1};
unsigned long time, next_flick;
const unsigned int to_flick = 1;



byte digit = 0;

void setup() {
    Serial.begin(9600);

    for(int i=0; i<4; i++) {
        pinMode(digit_pins[i], OUTPUT); 
    }

    for(int i=0; i<8; i++) {
        pinMode(i+5, OUTPUT);
    }
}

void loop() {
    String counter = String(analogRead(A5)/204.6);
    
    time = millis();
    if( time > next_flick ) {
        next_flick = time + to_flick;
        digit++;
        if(digit == 4)
            digit = 0;
        setDigit(digit, counter);
    }

    Serial.println(counter);
}

const byte digits[10] = {
    250,
    34,
    185,
    171,
    99,
    203,
    219,
    162,
    251,
    235
};

void fill(byte d, bool point = false) {
    for (byte j = 0; j < 8; j++) {
        if (point){
            digitalWrite(5+j, bitRead(digits[d]+4, j));
        } else {
            digitalWrite(5+j, bitRead(digits[d], j));
        }
    }
}

void setDigit(byte digit, String counter){
    byte i = 0;
    byte d = 0;
    byte s = counter.indexOf(".");

    if (digit == 0) {
        digitalWrite(digit_pins[3], LOW);
        if (s == 0){
            d = counter.charAt(1)-48;
            fill(d,true);
        } else {
            d = counter.charAt(0)-48;
            fill(d);
        }
        digitalWrite(digit_pins[0], HIGH);
    } 

    if (digit == 1) {
        digitalWrite(digit_pins[0], LOW);
        if (s == 1) {
            d = counter.charAt(2)-48;
            fill(d,true);
        } else {
            d = counter.charAt(1)-48;
            fill(d);
        }
        digitalWrite(digit_pins[1], HIGH);
    } 
    if (digit == 2) {
        digitalWrite(digit_pins[1], LOW);
        if (s == 2) {
            d = counter.charAt(3)-48;
            fill(d,true);
        } else {
            d = counter.charAt(2)-48;
            fill(d);
        }
        digitalWrite(digit_pins[2], HIGH);
    } 
    if (digit == 3) {
        if (s == 3) {
            d = counter.charAt(4)-48;
            fill(d,true);
        } else {
            d = counter.charAt(3)-48;
            fill(d);
        }
        digitalWrite(digit_pins[3], HIGH);
    } 
}


