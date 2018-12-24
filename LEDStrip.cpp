/**
 * LEDStrip
 * @author Curt Henrichs
 * @date 1-15-18
 *
 * LEDStrip enumerates and documents the IR code interface to a RGB LED strip.
 * Rational for sending IR codes as opposed to hacking the controller box is
 * two-fold. First hacking the box would make compatibility with the original
 * remote more of a chore. Second, the LED strip used is an outdoor model with
 * waterproofing and operates the LEDs at 120v. Thus to hack the hardware would
 * be counterproductive relative to the IR API already established.
 *
 * The IR LED interface determined after recording the remote's transmitted data
 * is noted in the following tables. Note that all commands follow a NEC
 * encoding.
 *
 *    Address is 0x00.
 *
 *    Hex Value | Name
 *    ----------|----------------
 *    0x04      | Brightness-Down
 *    0x05      | Brightness-Up
 *    0x06      | Off
 *    0x07      | On
 *    0x08      | ~Green
 *    0x09      | ~Red
 *    0x0A      | ~Blue
 *    0x0B      | ~White
 *    0x0C      | ~Pea Green
 *    0x0D      | ~Orange
 *    0x0E      | ~Dark Orchid
 *    0x0F      | Flash Function
 *    0x10      | ~Cyan
 *    0x11      | ~Dark Yellow
 *    0x12      | ~Magenta
 *    0x13      | Fade Function
 *    0x14      | ~Light Blue
 *    0x15      | ~Yellow
 *    0x16      | ~Pink
 *    0x17      | Strobe Function
 *    0x18      | ~Sky Blue
 *    0x19      | ~Light Yellow
 *    0x1A      | ~Purple
 *    0x1B      | Smooth Function
 *
 * Special functions have a unique property depending if one send the command
 * after it is already in the selected mode. The following lists describes this
 * behavior.
 *  - Pressing Flash once does same action as smooth
 *  - Pressing Flash twice strobes between color transitions of flash 1 (unsure
 *    which entity knows that a second press has happend)
 *  - Pressing Strobe once strobes currently displayed color
 *  - Pressing Strobe twice smoothly changes brightness of static color (unsure
 *    which entity knows that a second press has happend)
 *  - Pressing fade once fades between all colors
 *  - Pressing fade twice fades only an rgb single cycling them (unsure which
 *    entity knows that a second press has happend)
 *  - Pressing smooth once transitions between all colors abruptly (irony)
 *  - Pressing smooth twice flashes only an rgb single cycling them (unsure
 *    which entity knows that a second press has happend)
 *
 * Brightness adjustment is measured in ticks. To move from brightest to least
 * will take 9 ticks.
 *
 * Brightness adjustment will act as expected for static colors. However when
 * running a special function the brightness adjustment will alter the
 * transition speed of the current function.
 *  - During Flash increases/decreases transition speed (9 ticks)
 *  - During Strobe increases/decreases transition speed (9 ticks)
 *  - During Fade increases/decreases transition speed (9 ticks)
 *  - During Smooth increases/decreases transition speed (9 ticks)
 *
 * Note that after searching all possible command space, no other codes exist.
 * It is also unlikely that other code combinations exist.
 */

//==============================================================================
//                                 Libraries
//==============================================================================

#include "LEDStrip.h"

#include "HardwareConfig.h"
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRutils.h>

//==============================================================================
//                         Constant and Macro Definitions
//==============================================================================

/**
 * LED Strip NEC encoded address
 */
#define LED_STRIP_ADDRESS (0x00)

//==============================================================================
//                              Private Attributes
//==============================================================================

/**
 * Transmission object, connected via an interrupt to modulate data for IR LED
 */
IRsend irsend(LED_STRIP_IR_LED_PIN);

//==============================================================================
//                         Public Function Implementation
//==============================================================================

/**
 * Initialize LED Strip communication IR transmitter.
 */
void led_init(void){
  irsend.begin();
}

/**
 * Set a raw command to LED strip controller. Note that all data is transmitted
 * as a NEC command to controller.
 * @param cmd as a byte of data to transmit.
 */
void led_send_value(uint8_t cmd){
  irsend.sendNEC(irsend.encodeNEC(LED_STRIP_ADDRESS,cmd),32);
}
