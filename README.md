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
| PA12 | CAN1_TX     |             |                |
| PA11 | CAN1_RX     |             |                |

## クロック設定
| 項目                   | 内容 | 備考              |
| ---------------------- | ---- | ----------------- |
| APB1 peripheral clocks | 30   | CANを使いたかった |

## 変更した設定
### Project Manager
Code Generator, Generated files\
✅Generate peripheral initialization as a pair of '.c/.h' files per peripheral

### CAN1
MODE: ✅Activated\
CAN1で通信する．
#### Parameter Settings

| 項目                       | 内容         |
| -------------------------- | ------------ |
| 転送速度 Baud Rate         | 1Mbps        |
| サンプリングポイント       | 80%          |
| Bit Time(Time for one Bit) | 1μs          |
| CANのクロック源            | 30MHz        |
| Prescaler                  | 2            |
| Time Quantum               | 66.6666...ns |
| TSeg1                      | 11           |
| TSeg2                      | 3            |
| SJW                        | 1            |

$$
\begin{aligned}
    \text{time quantum}
        &= \frac 1 {\text{APB1 clock}} \times \text{Prescaler} \\
        &= \frac 1 {30[\mathrm{MHz}]} \times 2 \\
        &= 66.6666...[\mathrm{ns}] \\
    \text{NominalBitTime}
        &= (1 + \text{TSeg1} + \text{TSeg2}) \times \text{TimeQuantum} \\
        &= 15 \times 66.6666...[\mathrm{ns}] \\
        &= 1[\mu\mathrm{s}] \\
    \text{BaudRate}
        &= \frac 1 {\text{NominalBitTime}} \\
        &= \frac 1 {1[\mu\mathrm{s}]} \\
        &= 1[\mathrm{Mbps}] \\
    \text{sample point}
        &= \frac {1 + \text{TSeg1}} {1 + \text{TSeg1} + \text{TSeg2}} \\
        &= \frac {12} {15} \\
        &= 80[\%]
\end{aligned}
$$
参考:
- [STM32F446xx reference manual - STMicroelectronics](https://www.st.com/resource/en/reference_manual/dm00135183.pdf)
- [STM32マイコンでCAN通信 - ヒトミソフト開発](https://hsdev.co.jp/stm32-can/)
- [CAN Bit Time Calculation](http://www.bittiming.can-wiki.info/)
- [STM32F446_CAN/bitrate.c neo-Thrcot - GitHub](https://github.com/neo-Thrcot/STM32F446_CAN/blob/main/bitrate.c)
- [過去の議論 - esa](https://gifukosen-robot.esa.io/posts/367#%E5%88%B6%E5%BE%A1%E7%8F%AD%E3%81%A7%E8%A9%B1%E3%81%97%E5%90%88%E3%81%84%E3%81%99%E3%82%8B)
#### NVIC Settings
✅ CAN1 TX interrupt
✅ CAN1 RX0 interrupt

### USART2
#### NVIC Settings
USART2 global interrupt ✅
