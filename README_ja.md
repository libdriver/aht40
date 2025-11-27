[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AHT40

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/aht40/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AHT40は、低消費電力と高精度という大きなメリットを備えた新型温湿度センサーです。リフローはんだ付けに適した2列フラットピンレスSMDパッケージを採用し、堅牢で小型の筐体により、高難度設計への統合を容易にします。センサーは、新たに最適化されたASIC専用チップ、改良されたMEMS半導体容量性湿度センシング素子、標準オンチップ温度センシング素子を搭載し、性能を大幅に向上させ、過酷な環境下でも安定した性能を維持できます。AHT40温湿度センサーは、アプリケーションデバイスの消費電力削減に貢献し、高いコストパフォーマンスを実現。特に、コスト管理を厳格に行い、量産品質を重視する企業に最適です。

LibDriver AHT40 は、LibDriver によって起動される AHT40 のフル機能ドライバーです。温度と相対湿度を読み取る機能を提供します。 LibDriver は MISRA 準拠です。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver AHT40のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver AHT40用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver AHT40ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver AHT40プログラミング例が含まれています。

/ docディレクトリには、LibDriver AHT40オフラインドキュメントが含まれています。

/ datasheetディレクトリには、AHT40データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/aht40/index.html](https://www.libdriver.com/docs/aht40/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。