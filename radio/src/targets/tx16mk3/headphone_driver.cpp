#include "hal/gpio.h"
#include "stm32_gpio.h"
#include "trainer_driver.h"

#include "hal.h"
#include "edgetx.h"


static bool isJackPlugged()
{
  return gpio_read(AUDIO_HP_DETECT_PIN);
}

enum JackState
{
  SPEAKER_ACTIVE,
  HEADPHONE_ACTIVE,

};

uint8_t jackState = SPEAKER_ACTIVE;

void handleJackConnection()
{
  if (isJackPlugged()) 
  {
      jackState = HEADPHONE_ACTIVE;
      disableSpeaker();
      enableHeadphone();
      TRACE("is enableHeadphone\n");
  } 
  else if (!isJackPlugged()) 
  {
    jackState = SPEAKER_ACTIVE;
    enableSpeaker();
    disableHeadphone();
    TRACE("is enableSpeaker\n");
  }
}

void headphone_init()
{

  gpio_init(AUDIO_HP_DETECT_PIN, GPIO_IN_PU, GPIO_PIN_SPEED_LOW);
  handleJackConnection();

}

bool is_headphone_connected()
{
  return jackState;  
}

