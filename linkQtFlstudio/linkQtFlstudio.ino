#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int velocity = 100;
int noteON = 144;
String getAnswQt;
String getAnswQtBrak;
String str;
String message;
int c5 = A0;
int e5 = A1;
int g5 = A2;
int b5 = A3;
int e6 = A4;
int g6 = A5;
int rcvc5, rcve5, rcvg5, rcvb5, rcve6, rcvg6 = 0;
bool start;
bool autoStart;
unsigned long time_now = 0;
int period = 500;

int inputArray[6] = {c5, e5, g5, b5, e6, g6};
int inputAverage[6];
bool play[6] = {false, false, false, false, false, false};

void setup() {
  Serial.begin(31250);
  pinMode(c5, INPUT);
  pinMode(e5, INPUT);
  pinMode(g5, INPUT);
  pinMode(b5, INPUT);
  pinMode(e6, INPUT);
  pinMode(g6, INPUT);
  startAverage();
  start = false;
  message = "Stop";
}

void startAverage() {
  int stock = 0;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 5; j++) {
      stock += analogRead(inputArray[i]);
    }
    inputAverage[i] = stock / 5;
  }
}

int Average(int input) {
  int stock = 0;

  for (int i = 0; i < 5; i++) {
    stock += analogRead(input);
  }
  if (stock > 0)
    return (stock / 5);
  return (0);
}

int getPlay(int input)
{
  for(int i = 0; i < 6; i++) {
    if (inputArray[i] == input) {
      return (i);
    }
  }
  return (-1);
}

void activateNoteManual(int note, int input)
{
  int rcv = Average(input);
  int loc = getPlay(input);

  if (rcv < (inputAverage[loc] / 1,5) && play[loc] != true) {
    MIDImessage(noteON, note, velocity);
    play[loc] = true;
  } else if (rcv > (inputAverage[loc] / 1,05)){
    MIDImessage(noteON, note, 0);
    play[loc] = false;
  }
}

void activateNoteAuto(int note)
{
  MIDImessage(noteON, note, velocity);
  delay(300);
  MIDImessage(noteON, note, 0);
  delay(300);
}

void manualPLay()
{
  activateNoteManual(60, c5);
  activateNoteManual(64, e5);
  activateNoteManual(67, g5);
  activateNoteManual(71, b5);
  activateNoteManual(76, e6);
  activateNoteManual(79, g6);
}

void automaticLoop()
{
  while (getAnswQt == "Auto") {
      if (Serial.available() > 0)
        getAnswQtBrak = Serial.readString();
      if (getAnswQtBrak == "no"){
        getAnswQtBrak = "";
        break;
      }
      if (getAnswQtBrak != 0) {
        str = getAnswQtBrak;
        getAnswQtBrak = "";
        int str_len = str.length() + 1;  
        char char_array[str_len];
        str.toCharArray(char_array, str_len);
        char *ptr = strtok(char_array, " ");
        while (ptr != NULL)
        {
          activateNoteAuto(atoi(ptr));
          ptr = strtok(NULL, " ");
        }
      }
   }
}

void manualLoop(String getAnswQt)
{
  while (getAnswQt == "Manual") {
     if (Serial.available() > 0)
        getAnswQtBrak = Serial.readString();
     if (getAnswQtBrak == "no") {
        getAnswQtBrak = "";
        getAnswQt = "";
        break;
     }
     manualPLay();
  }
}

void loop() {

  if (Serial.available() > 0 && start == false) {
        message = Serial.readString();
        start = true;
  }
  while (start == true) {
    if (Serial.available() > 0 ) {
      getAnswQt = Serial.readString();
      manualLoop(getAnswQt);
      automaticLoop();
    }
    if (getAnswQt == "Stop") {
      start = false;
      break;
    }   
  }
  if (start == false) {
    manualPLay();
  }
}

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) 
{
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}
