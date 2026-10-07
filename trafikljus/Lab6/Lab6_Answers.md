# Lab 6 - answers for the examination

Required tasks 1 and 2 only. This sheet uses the STM32L433RC and the settings in [the guide](Lab6_Step_by_step.html): TIM1, upcounting, PWM mode 1, PSC = 79, ARR = 999, RCR = 0, and an 80 MHz TIM1 input clock. The six required bold questions are on pages 2-3 of [Lab6_PWM.pdf](../.REF/Lab6_PWM.pdf). The song question on page 5 belongs to the optional task and is excluded.

**Status:** these are explanations and a measurement worksheet. The LED's actual brightness ratios have not been measured. Fill in questions 5-6 after testing your hardware.

## 1. Vilka frekvenser brukar en LED-dimmer arbeta på?

There is no single standard frequency. A practical choice for this small RGB indicator is around **1 kHz**; LED dimming commonly uses hundreds of hertz to several kilohertz, with higher rates in some applications. The PWM must repeat fast enough that individual on/off pulses are not normally visible; a camera or movement can still reveal flicker.

For context, TI's TPS61183 LED driver specifies PWM dimming from 100 Hz to 50 kHz and gives examples at 200 Hz and 20 kHz. That is a device example, not a universal requirement. **Our choice is 1000 Hz**, giving a period of 1 ms and satisfying this lab's requirement that the period exceed 50 microseconds. [TI TPS61183](https://www.ti.com/product/TPS61183)

Do not confuse the **1000 Hz PWM frequency** with `freq = 0.2f`: the latter makes the *colour pattern* repeat every five seconds.

## 2. Skriv en kort beskrivning (2-4 meningar) av hur PWM-generering fungerar. Nämn ARR, CNT, CCR1 och TIMx_CH1.

The timer's **CNT** counts from zero through **ARR**, then starts again at zero. In PWM mode 1 with upcounting and active-high polarity, **TIMx_CH1** is high while `CNT < CCR1` and low for the rest of the period. **CCR1** therefore controls the duty cycle, while ARR and the prescaler control the PWM frequency. Changing CCR1 changes the LED's average on-time and perceived brightness.

Source: [RM0394, section 26.3.11, pp. 750-751](../.REF/ReferenceManual-stm32l433.pdf#page=750).

Useful equations for this configuration:

```text
timer counter frequency = TIM1 input clock / (PSC + 1)
PWM frequency           = TIM1 input clock / ((PSC + 1) * (ARR + 1))
duty cycle              = CCRx / (ARR + 1)
```

| CCRx, decimal | Duty with ARR = 999 |
|---:|---:|
| 0 | 0% |
| 250 | 25% |
| 500 | 50% |
| 999 | 99.9% |
| 1000 | 100% |

**Correction to the handout:** ARR is not the highest useful CCR value in this configuration. With `CCRx = ARR + 1`, CNT is always smaller than CCRx, so the output remains active. This works here because 1000 fits in TIM1's 16-bit CCR register. It would not work with ARR = 65535 and a 16-bit CCR. RM0394 p. 751 explicitly describes the case `CCRx > ARR`.

For a common-anode RGB LED configured with LOW polarity, the electrical output levels are reversed, but the active fraction still controls the LED's on-time.

## 3. Vilka värden valde du för TIM1? f_TIM1, p, n?

| Quantity | Selected value |
|---|---:|
| TIM1 input clock, before PSC | 80,000,000 Hz |
| Prescaler division factor, p = PSC + 1 | 80 |
| CubeMX Prescaler / PSC register | 79 |
| Number of counter ticks, n = ARR + 1 | 1000 |
| CubeMX Counter Period / ARR register | 999 |
| Counter clock | 1,000,000 Hz |
| PWM / overflow frequency, f_TIM1 in the lab's period calculation | 1000 Hz |
| PWM period | 0.001 s = 1000 microseconds |
| Repetition counter RCR | 0 |

```text
f_PWM = 80,000,000 / (80 * 1000) = 1000 Hz
T_PWM = 1 / 1000 = 0.001 s = 1000 microseconds > 50 microseconds
```

The handout's symbols `p` and `n` are not explicitly defined. State both the **division/count factors** and the **register values** during the examination so the minus-one convention is clear. Also distinguish the timer's 80 MHz input clock from its 1 kHz overflow rate.

With APB2 prescaler = 1, TIM1 receives PCLK2 directly. With a divided APB2, STM32L433 normally supplies TIM1 with twice PCLK2. Always check **APB2 timer clocks** in CubeMX; do not assume CPU frequency equals timer frequency. The generated `Run.cpp` calculates the update rate from PCLK2, APB2 prescaling, PSC, and ARR, and requires RCR = 0.

Sources: [RM0394, section 6.2.14, timer clock, p. 192](../.REF/ReferenceManual-stm32l433.pdf#page=192); [TIM1 time base, section 26.3.1, p. 724](../.REF/ReferenceManual-stm32l433.pdf#page=724); [TIM1 repetition counter, p. 803](../.REF/ReferenceManual-stm32l433.pdf#page=803). Page numbers refer to your local Rev 5 manual.

## 4. Varför kan du ändra ljusets intensitet när processorn är pausad?

TIM1 is a hardware peripheral that can keep counting and generating PWM while the CPU is halted. The debugger can write CCR1, CCR2 and CCR3 through the debug interface, so changing those registers changes the pulse widths without executing the main loop. With compare preload enabled, the new value takes effect at the next timer update event.

**Condition:** `DBG_TIM1_STOP` must be **0**. If it is 1, TIM1 stops when the CPU is halted, so this demonstration does not work as intended. The supplied `Run.cpp` calls `__HAL_DBGMCU_UNFREEZE_TIM1()` before starting PWM. Pause only after startup has completed, inside the Task 1 loop.

Sources: [RM0394, section 47.16.6, p. 1598](../.REF/ReferenceManual-stm32l433.pdf#page=1598); [section 26.3.11, p. 750](../.REF/ReferenceManual-stm32l433.pdf#page=750); [CCR1 preload behaviour, p. 803](../.REF/ReferenceManual-stm32l433.pdf#page=803).

## 5. Är de tre färgerna av samma ljusintensitet för samma värde på CCRx?

**Expected explanation:** not necessarily, and usually not. Equal CCR values give equal duty cycles, not equal perceived brightness. Red, green and blue emitters have different forward voltages and efficiencies, and the eye responds differently to their wavelengths. Even with equal 220-ohm resistors, their on-state currents can differ approximately according to `I = (Vdrive - Vf) / R`.

**My observation, to fill in:** at CCR = **_____** for each colour, **_____** looked strongest and **_____** weakest. They **did / did not** appear equally bright.

Compare one colour at a time, under the same lighting and viewing conditions. Do not claim the expected result as your measured result. The actual ranking depends on your LED; no exact RGB component datasheet has been supplied. This is the empirical task in Lab 6 section 2.1, p. 3.

## 6. Om någon färg behöver högre duty cycle för att nå samma intensitet som den starkaste, vad är proportionerna?

There is no fixed numerical answer without measuring your RGB LED. Use the strongest-looking colour at a modest reference duty, such as **20%**, and adjust the others one at a time until their perceived brightness is approximately equal. If one reaches 100% before matching, lower the reference and repeat.

| Colour | CCR needed for a visual match | Duty = CCR / 1000 | Ratio to strongest colour's duty |
|---|---:|---:|---:|
| Red | _____ | _____ | _____ |
| Green | _____ | _____ | _____ |
| Blue | _____ | _____ | _____ |

Then say: **“For approximately equal perceived brightness, my duty-cycle proportions were R:G:B = _____:_____:_____.”** These are rough visual estimates, not calibrated optical measurements.

To apply those observations in `Run.cpp`, let the matching duties be `D_R`, `D_G`, and `D_B`:

```text
D_max      = max(D_R, D_G, D_B)
red_gain   = D_R / D_max
green_gain = D_G / D_max
blue_gain  = D_B / D_max
```

Pass those three gains to `led.SetBalance(...)`. They stay in 0-1: the strongest colours are attenuated, while the weakest can use full duty without clipping.

**Illustration only, not your measurement:** if matching duties were 0.40, 0.20, 0.50, the proportions would be 2:1:2.5 relative to green, and the balance factors would be:

```cpp
led.SetBalance(0.8f, 0.4f, 1.f);
```

This fulfils the instruction on Lab 6 p. 5 to apply the intensity observations from Task 1 during Task 2.

## Short explanations to know during the demonstration

- **TIM1 versus TIM15/TIM16 versus TIM6/TIM7:** TIM1 provides the three PWM output channels used here and advanced output control. TIM15/TIM16 have fewer output channels and simpler arrangements. TIM6/TIM7 are basic time-base timers; they have no channel pins for directly generating the RGB PWM outputs. Compare the block diagrams in RM0394, chapters 26, 28 and 29.
- **Why not do sine calculations in the ISR?** Keep the interrupt short so other work can run. The callback only increments an unsigned counter. `ColorCycle::Update()` consumes elapsed periods in the main loop and does the floating-point work there.
- **Why count periods rather than clear a boolean?** If main temporarily falls behind, a counter preserves elapsed serviced periods. The phase advances by `2*pi*freq*(elapsed/update_frequency)`, keeping the colour speed correct. This does not recover interrupts lost while the CPU is halted or interrupts are disabled for multiple periods.
- **Why 120-degree phase offsets?** Three sine waves offset by `2*pi/3` give smooth, different brightness changes for red, green and blue.
- **Why no endless growth of t?** The class wraps its phase to one revolution so float precision is not gradually lost by an ever-growing time variable.

## Source map

1. [Lab6_PWM.pdf](../.REF/Lab6_PWM.pdf): required questions pp. 2-3; cycling pp. 4-5; CubeMX/wiring p. 6. Code examples were checked independently rather than copied.
2. [RM0394 Rev 5](../.REF/ReferenceManual-stm32l433.pdf): chapter 26 TIM1; PWM pp. 750-751; debug freeze p. 1598; timer comparison chapters 28-29.
3. [STM32L433xx datasheet, DS11449 Rev 8](../.REF/stm32l433rc.pdf): Table 16, alternate functions AF0-AF7, maps PA8/PA9/PA10 to TIM1_CH1/CH2/CH3 on AF1.
4. [ST UM2206 Rev 6](https://www.st.com/resource/en/user_manual/dm00387966.pdf): NUCLEO-L433RC-P board, section 6.9 and Table 14. Default Arduino D9/D1/D0 routing is PA8/PA9/PA10; altered solder bridges can change the serial-pin routing.
5. [TI TPS61183](https://www.ti.com/product/TPS61183): an example of supported LED PWM dimming frequencies, not the RGB LED's datasheet.
6. The installed STM32L4 HAL implementation in the existing ADC project was checked for `HAL_TIM_PWM_Start`, `HAL_TIM_Base_Start_IT`, and the TIM1 unfreeze macro. Generated CubeMX startup must still be checked after you configure the new project.
