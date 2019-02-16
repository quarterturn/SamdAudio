/*
  Audio player, non blocking.
  read 8bit mono .wav file, up to 4 channels
  use Audacity to convert your audio file

  Author : AloyseTech
  Modified: BriscoeTech
*/

//#include <SdFat.h>
//SdFat SD;
//#include <SPI.h>
#include <SamdAudio.h>

SamdAudio AudioPlayer;

#define NUM_AUDIO_CHANNELS 4 //could be 1,2 or 4 for sound

// which Serial you prefer, for information.
#define SERIAL SerialUSB
//#define SERIAL Serial

// SD chip select pin (with ethernet shield : 4)
#define YOUR_SD_CS 4//10

//indicate sample rate here (use audacity to convert your wav)
const unsigned int sampleRate = 22050;

bool state = true;

uint32_t timer = 0, updatetimer = 0;

void setup()
{
  pinMode(2, OUTPUT);
  //pinMode(2, INPUT_PULLUP);
  //pinMode(3, INPUT_PULLUP);
  //pinMode(4, INPUT_PULLUP);

  // debug output at 115200 baud
  SERIAL.begin(115200);
  while (!SERIAL);


  // setup SD-card
  SERIAL.print("Initializing SD card...");
  if (AudioPlayer.begin(sampleRate, NUM_AUDIO_CHANNELS, YOUR_SD_CS) == -1) 
  {
    SERIAL.println(" failed!");
    return;
  }
  SERIAL.println(" done.");

  AudioPlayer.play("R2D2.wav", 0);

  SERIAL.println("Playing file.....");
}

void loop()
{
  /*
  if (millis() - timer > 500) 
  {
    //I'm working late at night, full led brightness is dazzling!
    //digitalWrite(13,state);
    analogWrite(2, state ? 0 : 4);

    state = !state;
    timer = millis();
  }
  */

  if (SERIAL.available()) 
  {
    char c = SERIAL.read();

    if ( c == 'q') 
    {
      AudioPlayer.play("LaserFire1.wav", 0);
    }
    else if ( c == 'w') 
    {
      AudioPlayer.play("LaserFire1.wav", 1);
    }
    else if ( c == 'e') 
    {
      AudioPlayer.play("LaserFire2.wav", 2);
    }
    else if ( c == 'r') 
    {
      AudioPlayer.play("LaserFire2.wav", 3);
    }
    else if ( c == 't') 
    {
      AudioPlayer.play("R2D2.wav", 3);
    }

    else if ( c == '1') 
    {
      AudioPlayer.stopChannel(0);
      SERIAL.println("ch0 off!");
    }
    else if ( c == '2') 
    {
      AudioPlayer.stopChannel(1);
      SERIAL.println("ch1 off!");
    }
    else if ( c == '3') 
    {
      AudioPlayer.stopChannel(2);
      SERIAL.println("ch2 off!");
    }
    else if ( c == '4') 
    {
      AudioPlayer.stopChannel(3);
      SERIAL.println("ch3 off!");
    }
  }

}
