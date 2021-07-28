/*******************************************************************************
 
  *  Áster Electrónica
  *  Display Circular GC9A01 240x240.
  *  Ejemplo 'Hola Mundo Random' para Tarjetas UNO, NANO y Pro Mini con ATmega328 a 16MHz.
  *  Abstract: En este ejemplo aparecerá el mensaje 'Hola Mundo' en diferentes lugares de nuestra pantalla
  *  con un color de font, de fondo y tamaño aleatorio.
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
 * Aquí termina el bloque de configuración de nuestro Display Circular GC9A01 para ATmega328
 ******************************************************************************/

//Declaramos el D6 del Arduino para controlar la retroiluminacion del display
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
    //Colocamos el cursor en la posición 10,10
    gfx->setCursor(10, 10);
    //Declaramos el siguiente texto en rojo (se pueden usar colores hexadecimales)
    gfx->setTextColor(RED);
    //Envíamos una cadena de texto 
    gfx->println("Hello World!");
    //Retardo de 5 segundos
    delay(5000);
}

void loop()
{
    //Acontinuación este bucle sin fin enviará mensajes con tamaños y colores aleatorios
    //Colocamos el cursor en una posición x,y aleatoria dentro del rango del tamaño aceptado
    gfx->setCursor(random(gfx->width()), random(gfx->height()));
    //Ajustamos el color de la letra y el color del fondo del texto a un valor aleatorio
    gfx->setTextColor(random(0xffff), random(0xffff));
    //Colocamos el tamaño de largo, ancho y el margen del texto a valores aleatorios
    gfx->setTextSize(random(6) /* x scale */, random(6) /* y scale */, random(2) /* pixel_margin */);
    //Enviamos el mensaje 
    gfx->println("Hello World!");
    //Retardo de un segundo
    delay(1000);
    //Se repite el ciclo
}
