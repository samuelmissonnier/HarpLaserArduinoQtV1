#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
 //(higher velocity usually makes MIDI instruments louder)
 
int noteON = 144;//144 = 10010000 in binary, note on command

String getAnswQt;
String getAnswQtBrak;
int c5 = A0;
int rcvc5 = 0;
String test = "12 24 36 48";
//int e5 = A1;
//int g5 = A2;
//int  =   A3
//int A4 = 
//int A5 = 
//int rcve5 = 0;
//int rcvg5 = 0;



  /*while (ptr != NULL)
  {
    printf("'%s'\n", ptr);
    ptr = strtok(NULL, delim);
  }*/

void setup() {
  //  Set MIDI baud rate:
  //Serial.begin(9600);
  Serial.begin(31250);
  pinMode(c5, INPUT);
  /*String test = "salut ca va ?";
  int str_len = test.length() + 1;  
  char char_array[str_len];
  test.toCharArray(char_array, str_len);
  char *ptr = strtok(char_array, " ");
  while (ptr != NULL)
  {
    Serial.println(ptr);
    ptr = strtok(NULL, " ");
  }*/
  //pinMode(e5, INPUT);
  //pinMode(g5, INPUT);
}
                  //60      //c5
void activateNoteManual(int note, int input)
{
  int rcv = analogRead(input);
  if (rcv == 0) {
    MIDImessage(noteON, note, velocity);//turn note on
    delay(300);//hold note for 300ms
  } else {
    MIDImessage(noteON, note, 0);//turn note off
    delay(300);//wait 200ms until triggering next note
  }
}

void activateNoteAuto(int note)
{
  MIDImessage(noteON, note, velocity);//turn note on
  delay(300);//hold note for 300ms
  MIDImessage(noteON, note, 0);//turn note on
  delay(300);//hold note for 300ms
}

void loop() {
  if (Serial.available() > 0) {
    getAnswQt = Serial.readString();
    while (getAnswQt == "no") {
        MIDImessage(noteON, 60, 0);//turn note off
    }
    while (getAnswQt == "Manual") {
      getAnswQtBrak = Serial.readString();
      if (getAnswQtBrak == "no")
        break;
      activateNoteManual(60, c5);
    }
    while (getAnswQt != "Manual") {
      getAnswQtBrak = Serial.readString();
      if (getAnswQtBrak == "no")
        break;
      if (getAnswQtBrak != 0) {
        test = getAnswQtBrak;
        int str_len = test.length() + 1;  
        char char_array[str_len];
        test.toCharArray(char_array, str_len);
        char *ptr = strtok(char_array, " ");
        while (ptr != NULL)
        {
          activateNoteAuto(atoi(ptr));
          //Serial.println(ptr);
          ptr = strtok(NULL, " ");
        }
        //activateNoteAuto(60);
      }
    } 
  }
    //rcvc5 = analogRead(c5);
    //rcve5 = analogRead(e5);
    //rcvg5 = analogRead(g5);
    //Serial.println(rcvc5);
 
    //if (rcve5 < 25) {
    //  MIDImessage(noteON, 64, velocity);//turn note on
    //  delay(300);//hold note for 300ms
    //} else {
    //  MIDImessage(noteON, 64, 0);//turn note off
    //  delay(300);//wait 200ms until triggering next note
    //}
    //if (rcvg5 < 25) {
    //  MIDImessage(noteON, 67, velocity);//turn note on
    //  delay(300);//hold note for 300ms
    //} else {
    //  MIDImessage(noteON, 67, 0);//turn note off
    //  delay(300);//wait 200ms until triggering next note
    //}
    

    
    /*MIDImessage(noteON, 64, velocity);//turn note on
    delay(300);//hold note for 300ms
    MIDImessage(noteON, 64, 0);//turn note off
    delay(200);//wait 200ms until triggering next note
    
    
    MIDImessage(noteON, 67, velocity);//turn note on
    delay(300);//hold note for 300ms
    MIDImessage(noteON, 67, 0);//turn note off
    delay(200);//wait 200ms until triggering next note

    
    MIDImessage(noteON, 71, velocity);//turn note on
    delay(300);//hold note for 300ms
    MIDImessage(noteON, 71, 0);//turn note off
    delay(200);//wait 200ms until triggering next note
    
    MIDImessage(noteON, 76, velocity);//turn note on
    delay(300);//hold note for 300ms
    MIDImessage(noteON, 76, 0);//turn note off
    delay(200);//wait 200ms until triggering next note
    
    
    MIDImessage(noteON, 79, velocity);//turn note on
    delay(300);//hold note for 300ms
    MIDImessage(noteON, 79, 0);//turn note off
    delay(200);//wait 200ms until triggering next note*/
  
  
  /*for (int note=60 ;note <= 70 ; note++) {//from note 50 (D3) to note 69 (A4)
    MIDImessage(noteON, note, velocity);//turn note on
    delay(300);//hold note for 300ms
    MIDImessage(noteON, note, 0);//turn note off
    delay(200);//wait 200ms until triggering next note
  }*/
}
   
 

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) 
{
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}
