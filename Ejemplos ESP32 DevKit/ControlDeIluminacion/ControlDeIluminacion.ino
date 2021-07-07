/*******************************************************************************
 
  *  Áster Electrónica
  *  Display Circular GC9A01 240x240.
  *  Ejemplo 'Hola Mundo Random' para ESP32 DevKit
  *  Abstract: En este ejemplo aparecerá el mensaje 'Hola Mundo' de manera fija, pero 
  *  el pin 22 tendra una señal PWM para aumentar y disminuir el brillo de la pantalla.
  *  Modificado y comentado por Miguel AngelLo.
  *  Conexiones físicas:
  *  Esp32 DevKit | Display Circular
  *   3.3V ó Vin -> VCC
  *          GND -> GND
  *          D18 -> SCL
  *          D23 -> SDA
  *          D33 -> RST  
  *          D27 -> DC
  *          D5  -> CS
  *          D22 -> BL
  *          
  * IMPORTANTE:
  * Deberás contar con la biblioteca 'Arduino_GFX_Library' instalada en tu Arduino IDE
  * puedes descargarla en el siguiente enlace
  * https://github.com/moononournation/Arduino_GFX
  
********************************************************************************/

#include <Arduino_GFX_Library.h>
/* Para más información sobre la declaración del display y la tarjeta de control consulta:
https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration */
#if defined(DISPLAY_DEV_KIT)
Arduino_GFX *gfx = create_default_Arduino_GFX();
#else /* !defined(DISPLAY_DEV_KIT) */

/* Configuramos el tipo de Bus de Datos que usaremos, en este caso será Hardware SPI del ESP32 DevKit
para más información consulte:
https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus *bus = new Arduino_ESP32SPI(27 /* DC */, 5 /* CS */, 18 /* SCK */, 23 /* MOSI */, -1 /* MISO */, VSPI /* spi_num */);

/* Configuramos el controlador de la pantalla, en este caso es el CI GC9A01
para más información consulte:
https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX *gfx = new Arduino_GC9A01(bus, 33 /* RST */, 2 /* rotation */, true /* IPS */);

#endif /* !defined(DISPLAY_DEV_KIT) */
/*******************************************************************************
 * Aquí termina el bloque de configuración de nuestro Display Circular GC9A01 para ESP32 DevKit
 ******************************************************************************/
 
//Declaramos el D22 del DevKit para controlar la retroiluminacion del display
#define TFT_BL 22

//Declaramos los ajustes del control PWM, como el canal 0, la resolución a 8 bits y la frecuencia de 1KHz.
#define PWM1_Ch    0
#define PWM1_Res   8
#define PWM1_Freq  1000

//Declaramos la variable que almacenará el ciclo de trabajo del PWM como variable global.
int PWM1_DutyCycle = 0;

void setup(void)
{
    //Inicializamos la comunicación
    gfx->begin();
    //Colocamos un fondo de color blanco
    gfx->fillScreen(WHITE);
    
  //Inicializamos el pin con las configuraciones para el PWM
  ledcAttachPin(TFT_BL/*Pin D22*/, PWM1_Ch/*Canal 0*/);
  ledcSetup(PWM1_Ch/*Canal 0*/, PWM1_Freq/*1KHz*/, PWM1_Res/*8bits*/);
}

void loop()
{
    //Colocamos el cursor en la posición 10,10
    gfx->setCursor(30, 110);
    //Ajustamos el tamaño de la escala x,y a 3 sin margen de pixel
    gfx->setTextSize(3/* x scale */,3/* y scale */,0/* pixel_margin */);
    //Declaramos el siguiente texto en rojo (se pueden usar colores hexadecimales)
    gfx->setTextColor(BLACK);
    //Envíamos una cadena de texto 
    gfx->println("Hola Mundo!");
    //En este ciclo incrementamos gradualmente la intensidad de 0 a 255 valores
    while(PWM1_DutyCycle < 255)
  {
    ledcWrite(PWM1_Ch, PWM1_DutyCycle++);
    delay(20);
  }
  //En este ciclo reducimos gradualmente la intensidad de 255 a 0 y el ciclo se repite.
  while(PWM1_DutyCycle > 0)
  {
    ledcWrite(PWM1_Ch, PWM1_DutyCycle--);
    delay(20);
  }
}
