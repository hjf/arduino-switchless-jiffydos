#define RESET 0
#define RESTORE 1
#define JDENABLE 2

#define DEBOUNCE_DELAY 20


void setup() {
  // put your setup code here, to run once:
  pinMode(RESET, INPUT_PULLUP);
  pinMode(RESTORE, INPUT_PULLUP);
  pinMode(JDENABLE, OUTPUT);
  digitalWrite(JDENABLE, HIGH);
}

void loop() {
  char debounce = 0;
  // wait for reset to go low
  while (digitalRead(RESET));

  //make sure reset actually stays low and it's not a fluke
  while (!digitalRead(RESET)) {
    debounce++;
    delay(1);
    if (debounce > DEBOUNCE_DELAY)
      break;
  }

  if (debounce < DEBOUNCE_DELAY)
    return;

    //reset the debounce counter and start counting again 
  debounce = 0;
  for (char i = 0; i < DEBOUNCE_DELAY; i++) {
    if (digitalRead(RESTORE)) debounce++;
    delay(1);
  }
  //enable output latch if restore was pressed for long enough
  digitalWrite(JDENABLE, debounce > (DEBOUNCE_DELAY / 2));

  //wait for C64's RESET to finish
  while (!digitalRead(RESET));

  //wait for 1s, for good measure
  delay(1000);
}
