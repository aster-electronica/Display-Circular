/*******************************************************************************
 
  *  Áster Electrónica
  *  Display Circular GC9A01 240x240.
  *  Ejemplo 'Hola Mundo Random' para Tarjetas UNO, NANO y Pro Mini con ATmega328 a 16MHz.
  *  Abstract: En este ejemplo aparecerá el mensaje 'Hola Mundo' en el centro de la pantalla
  *  en un fondo blanco con font de color negro.
  *  Modificado y comentado por Miguel AngelLo.
  *  Conexiones físicas:
  *  UNO/NANO/ProMini | Display Circular
  *        3.3V ó Vin -> VCC
  *               GND -> GND
  *               D13 -> SCL
  *               D11 -> SDA
  *               D7  -> RST  
  *               D8  -> DC
  *               D9  -> CS
  *               D6  -> BL
  *          
  * IMPORTANTE:
  * Deberás contar con la biblioteca 'Arduino_GFX_Library' instalada en tu Arduino IDE
  * puedes descargarla en el siguiente enlace
  * https://github.com/moononournation/Arduino_GFX
  
********************************************************************************/

#include <Arduino_GFX_Library.h>
/* Para más información sobre la declaración del display y la tarjeta de control consulta:
https://github.com/moononournation/Arduino_GFX/wiki/Dev-Device-Declaration */


/* Configuramos el tipo de Bus de Datos que usaremos, en este caso será Hardware SPI del ATmega328
para más información consulte:
https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class */
Arduino_DataBus *bus = new Arduino_HWSPI(8 /* DC */, 9 /* CS */);

/* Configuramos el controlador de la pantalla, en este caso es el CI GC9A01
para más información consulte:
https://github.com/moononournation/Arduino_GFX/wiki/Display-Class */
Arduino_GFX *gfx = new Arduino_GC9A01(bus, 7 /* RST */, 0 /* rotation */, true /* IPS */);


/*******************************************************************************
 * Aquí termina el bloque de configuración de nuestro Display Circular GC9A01 para ESP32 DevKit
 ******************************************************************************/

//Declaramos el D22 del DevKit para controlar la retroiluminacion del display
#define TFT_BL 6

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
