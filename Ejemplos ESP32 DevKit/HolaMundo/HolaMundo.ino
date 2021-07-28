/*******************************************************************************
 
  *  Áster Electrónica
  *  Display Circular GC9A01 240x240.
  *  Ejemplo 'Hola Mundo Random' para ESP32 DevKit
  *  Abstract: En este ejemplo aparecerá el mensaje 'Hola Mundo' en el centro de la pantalla
  *  en un fondo blanco con font de color azul.
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
Arduino_GFX *gfx = new Arduino_GC9A01(bus, 33 /* RST */, 0 /* rotation */, true /* IPS */);

#endif /* !defined(DISPLAY_DEV_KIT) */
/*******************************************************************************
 * Aquí termina el bloque de configuración de nuestro Display Circular GC9A01 para ESP32 DevKit
 ******************************************************************************/

//Declaramos el D22 del DevKit para controlar la retroiluminacion del display
#define TFT_BL 22

void setup(void)
{
    //Inicializamos la comunicación
    gfx->begin();
    //Colocamos un fondo de color blanco
    gfx->fillScreen(WHITE);

    //Si se declaró un pin BL este encendará la retroiluminación de la pantalla 
#ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
#endif

}

void loop()
{
    //Colocamos el cursor en la posición 10,10
    gfx->setCursor(30, 110);
    //Ajustamos el tamaño de la escala x,y a 3 sin margen de pixel
    gfx->setTextSize(3/* x scale */,3/* y scale */,0/* pixel_margin */);
    //Declaramos el siguiente texto en azul (se pueden usar colores hexadecimales)
    gfx->setTextColor(BLUE);
    //Envíamos una cadena de texto 
    gfx->println("Hola Mundo!");
    //Retardo de 5 segundos
    delay(5000);
}
