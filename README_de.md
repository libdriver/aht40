[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AHT40

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/aht40/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der AHT40 ist ein neuer Temperatur- und Feuchtigkeitssensor mit den entscheidenden Vorteilen eines geringen Stromverbrauchs und einer hohen Genauigkeit. Er verfügt über ein zweireihiges, flaches SMD-Gehäuse ohne Pins, das sich für das Reflow-Löten eignet, und ein robustes, kompaktes Gehäuse, das die Integration in anspruchsvolle Designs erleichtert. Der Sensor ist mit einem neu optimierten ASIC-Chip, einem verbesserten kapazitiven MEMS-Halbleiter-Feuchtigkeitssensor und einem standardmäßigen On-Chip-Temperatursensor ausgestattet. Dies verbessert die Leistung erheblich und gewährleistet einen stabilen Betrieb auch unter rauen Umgebungsbedingungen. Der AHT40 trägt zur Reduzierung des Stromverbrauchs von Anwendungen bei und bietet ein hohes Kosten-Nutzen-Verhältnis. Er eignet sich besonders für Unternehmen mit strenger Kostenkontrolle und hohem Qualitätsanspruch in der Serienfertigung.

LibDriver AHT40 ist der voll funktionsfähige Treiber von AHT40, der von LibDriver gestartet wurde. Er bietet die Funktion zum Lesen von Temperatur und relativer Luftfeuchtigkeit. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver AHT40-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver AHT40 IIC.

/test enthält den Testcode des LibDriver AHT40-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver AHT40-Beispielcode.

/doc enthält das LibDriver AHT40-Offlinedokument.

/Datenblatt enthält AHT40-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_aht40_basic.h"

uint8_t res;
uint32_t i;
float temperature;
float humidity;

/* basic init */
res = aht40_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 2000ms */
    aht40_interface_delay_ms(2000);

    /* read data */
    res = aht40_basic_read((float *)&temperature, (float *)&humidity);
    if (res != 0)
    {
        (void)aht40_basic_deinit();

        return 1;
    }

    /* output */
    aht40_interface_debug_print("aht40: temperature is %0.2fC.\n", temperature);
    aht40_interface_debug_print("aht40: humidity is %.01f%%.\n", humidity); 
    
    ...
}

...
    
/* deinit */
(void)aht40_basic_deinit();

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/aht40/index.html](https://www.libdriver.com/docs/aht40/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.