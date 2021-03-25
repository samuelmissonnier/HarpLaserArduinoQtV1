#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int velocity = 100;
int noteON = 144;
String getAnswQt;
String getAnswQtBrak;
String str;
int c5 = A0;
int e5 = A1;
int g5 = A2;
int b5 = A3;
int e6 = A4;
int g6 = A5;
int rcvc5 = 0;
int rcve5 = 0;
int rcvg5 = 0;
int rcvb5 = 0;
int rcve6 = 0;
int rcvg6 = 0;

void setup() {
  Serial.begin(31250);
  pinMode(c5, INPUT);
  pinMode(e5, INPUT);
  pinMode(g5, INPUT);
  pinMode(b5, INPUT);
  pinMode(e6, INPUT);
  pinMode(g6, INPUT);
}

void activateNoteManual(int note, int input)
{
  int rcv = analogRead(input);
  if (rcv < 30) {
    MIDImessage(noteON, note, velocity);
    //delay(100);
  } else {
    MIDImessage(noteON, note, 0);
    //delay(100);
  }
}

void activateNoteAuto(int note)
{
  MIDImessage(noteON, note, velocity);//turn note on // quand on enlève le delay les notes se jouent en même temps 
  // le principe est simple le delay permet d'espacer les notes autrement on ne peut pas
  //---------------------------------------------------------------------------------------------
  //------- poser la question a jeremy comment sans delay jouer les notes une par une ? ---------
  //---------------------------------------------------------------------------------------------
  delay(300);//hold note for 300ms
  MIDImessage(noteON, note, 0);//turn note on
  delay(300);//hold note for 300ms
}

void manualLoop()
{
  while (getAnswQt == "Manual") {
      //activateNoteAuto(12);
      if (Serial.available() > 0)
        getAnswQtBrak = Serial.readString();
      if (getAnswQtBrak == "no")
        break;
      activateNoteManual(60, c5);
      activateNoteManual(64, e5);
      activateNoteManual(67, g5);
      activateNoteManual(71, b5);
      activateNoteManual(76, e6);
      activateNoteManual(79, g6);
    }
}

void automaticLoop()
{
  while (getAnswQt == "Auto") {
      //activateNoteAuto(84);
      getAnswQtBrak = Serial.readString();
      if (getAnswQtBrak == "no")
        break;
      if (getAnswQtBrak != 0) {
        str = getAnswQtBrak;
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

void loop() {
  if (Serial.available() > 0) {
    getAnswQt = Serial.readString();
    manualLoop();
    automaticLoop();
  }
}

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) 
{
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}
