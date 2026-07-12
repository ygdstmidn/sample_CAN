# sample_CAN
## 概要

| 項目         | 仕様             |
| ------------ | ---------------- |
| 使用マイコン | NUCLEO_F446RE    |
| 使用IDE      | CubeIDE,VSCode   |
| 使用言語等   | C++,STM32CubeHAL |

## ピン設定
| ピン | 設定        | ラベル      | 備考           |
| ---- | ----------- | ----------- | -------------- |
| PA5  | GPIO_Output | DebugLED    | ラベルのみ変更 |
| PC13 | GPIO_EXTI13 | DebugButton | ラベルのみ変更 |

## クロック設定
| 項目 | 内容 | 備考 |
| ---- | ---- | ---- |
|      |      |      |

## 変更した設定
### Project Manager
Code Generator, Generated files\
✅Generate peripheral initialization as a pair of '.c/.h' files per peripheral
