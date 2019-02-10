#include <util/delay.h>
#include <avr/io.h>
// #include <examples/strandtest/strandtest.ino>
// #include <ws2812_config.h>
#include <light_ws2812.h>

// avr library from QMK firmware.
// #include <avr/ws2812.h>

// #define LED PORTB5

#define MAXPIX  14

#define COLORLENGTH (MAXPIX/2)
#define FADE (256/COLORLENGTH)



struct cRGB colors[8];
struct cRGB led[MAXPIX];

uint8_t j = 1;
uint8_t k = 1;


void setVue(int level)
{
  int colorLength = (MAXPIX/2);
  int fadeLength = (256/colorLength);


  DDRB|=_BV(ws2812_pin);


  //Rainbowcolors
  colors[0].r=150; colors[0].g=150; colors[0].b=150;
  colors[1].r=255; colors[1].g=000; colors[1].b=000;//red
  colors[2].r=255; colors[2].g=100; colors[2].b=000;//orange
  colors[3].r=100; colors[3].g=255; colors[3].b=000;//yellow
  colors[4].r=000; colors[4].g=255; colors[4].b=000;//green
  colors[5].r=000; colors[5].g=100; colors[5].b=255;//light blue (türkis)
  colors[6].r=000; colors[6].g=000; colors[6].b=255;//blue
  colors[7].r=100; colors[7].g=000; colors[7].b=255;//violet

  //shift all vallues by one led
  uint8_t i;
  for(i=MAXPIX; i>1; i--)
      led[i-1]=led[i-2];
  //change colour when colourlength is reached
  if(k>COLORLENGTH)
  {
      j++;
      if(j>7)
      {
        j=0;
      }

      k=0;
  }
  k++;
  //loop colouers

  //fade red
  if(led[0].r<(colors[j].r-FADE))
      led[0].r+=FADE;

  if(led[0].r>(colors[j].r+FADE))
      led[0].r-=FADE;

  if(led[0].g<(colors[j].g-FADE))
      led[0].g+=FADE;

  if(led[0].g>(colors[j].g+FADE))
      led[0].g-=FADE;

  if(led[0].b<(colors[j].b-FADE))
      led[0].b+=FADE;

  if(led[0].b>(colors[j].b+FADE))
      led[0].b-=FADE;

  i = 0;
  for(i=MAXPIX; i>level; i--)
  {
      led[i-1].r=0;led[i-1].g=0;led[i-1].b=0;
  }

  _delay_ms(10);
  ws2812_sendarray((uint8_t *)led,MAXPIX*3);
}

int main(void) {
  int maxVue = 14;
  int vueLevel = 2;
  int steps = 0;
  int maxSteps = 20;

  uint8_t i;
  for(i=MAXPIX; i>0; i--)
  {
      led[i-1].r=0;led[i-1].g=0;led[i-1].b=0;
  }

  while(1) {
    setVue(vueLevel<=maxVue?vueLevel:(maxVue*2)-vueLevel);
    steps += 1;
    if (steps > maxSteps) {
      vueLevel += 1;
      vueLevel = vueLevel % (maxVue * 2);
      steps = 0;
    }

  }
}

// struct cRGB led[1];
//
// int main(void) {
//   while(1)
//   {
//     led[0].r=255;led[0].g=00;led[0].b=0;    // Write red to array
//     ws2812_setleds(led,1);
//     _delay_ms(500);                         // wait for 500ms.
//
//     led[0].r=0;led[0].g=255;led[0].b=0;			// green
//     ws2812_setleds(led,1);
//     _delay_ms(500);
//
//     led[0].r=0;led[0].g=00;led[0].b=255;		// blue
//     ws2812_setleds(led,1);
//     _delay_ms(500);
//   }
// }
