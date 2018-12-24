/**
 * HardwareConfig
 * @author Curt Henrichs
 * @date 1-15-18
 *
 * Hardware configuration file captures hardware pinout and design as to inform
 * the application of the hardware layer. Note that this is not a device driver
 * rather this is merely a location to place physical dependencies for drivers.
 *
 * Additionally, any hardware designs external to the processor should be noted
 * in this documentation.
 *    - 10 Ohm resistor connected in series with IR LED for transmission
 *    - Reset pin attached to button, normally pulled high internally.
 *    - Status LED attached in series with a 1 kOhm resistor to GND
 *    - 1 kOhm resistor pullup on Boot 0 and Boot 2
 *    - 1 kOhm resistor pulldown on Boot 15
 */

//==============================================================================
//                                 Libraries
//==============================================================================

#include <Arduino.h>

//==============================================================================
//                                Device Pinout
//==============================================================================

#define LED_STRIP_IR_LED_PIN (D2) //! IR LED connected for tx with LED strip

#define STATUS_LED_PIN (D6)       //! Status LED to note active functioning

#define BOOT_0_PIN (D3)           //! Vcc for flash run, GND for program

#define BOOT_2_PIN (D4)           //! Always Vcc (via external pullup)

#define BOOT_15_PIN (D8)          //! Always GND (via external pulldown)

//==============================================================================
//                       Hardware Initialization Routine
//==============================================================================

/**
 * Initialize hardware pins as defined in the device pinout
 */
static inline void hwcfig_init(void){
  pinMode(LED_STRIP_IR_LED_PIN,OUTPUT);
  digitalWrite(LED_STRIP_IR_LED_PIN,LOW);
  pinMode(STATUS_LED_PIN,OUTPUT);
  digitalWrite(STATUS_LED_PIN,LOW);

  pinMode(BOOT_0_PIN,INPUT);
  pinMode(BOOT_2_PIN,INPUT);
  pinMode(BOOT_15_PIN,INPUT);
}
