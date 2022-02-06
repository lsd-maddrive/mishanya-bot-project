# arm driver v1.0 

Данный файл содержить информацию по использованию модуля `arm_driver`.
На данный момент с помощью данного модуля полностью описана работа:
- локтевого сустава робота `elbow_driver`;


## Описание конструкий

В h-файле находятся компоненты, которые описывают часть руки робота:

1. arm_side_t

enum для выбора левой или правой руки.

2. driver_t

enum для выбора типа драйвера:
- BB - управление осуществляется четырьмя выводами (2 ШИМ, 2 дискретных);
- RED - управление осуществляется тремя выводами (1 ШИМ, 2 дискретных).

3. pwm_channel_t

Структура с информацией о ШИМ-каналах

- uint8_t ch_pwm_1 - первый используемый канал ШИМ; 
- uint8_t ch_pwm_2 - второй используемый канал ШИМ;
- uint8_t alt_func_1 - номер альтернативной функции первого канала ШИМ;
- uint8_t alt_func_2 - номер альтернативной функции второго канала ШИМ.

4. pwm_ctx_t

Структура с информацией о настройках ШИМ.

- PWMDriver driver_ptr -  указатель на используемый таймер;
- PWMConfig pwm_conf -  структура с настройкой ШИМа;
- pwm_channel_t pwm_ch - описана в 4 пункте.

5. line_driver_t

Структура с информацией о используемых выводах.

- ioline_t digit_1 - первый цифровой вывод;
- ioline_t digit_2 - второй цифровой вывод;
- ioline_t PWM_1 - первый вывод ШИМ;
- ioline_t PWM_2 - второй вывод ШИМ.

6. control_driver_t

Объединяет в себе структуры из пункта 4 и 5.

7. arm_driver_ctx_t

Содержит enum из пунта 2 и массив из двух элементов типа control_driver_t (первый элемент описывает левую руку, второй правую). 

## Описание функций

Модуль содержит 4 функции:

1. Инициализация драйвера 
```c
void driver_init(const arm_driver_ctx_t *arm_driver);
```
Принимает полностью описанную часть руки робота.

2. Поднятие части руки робота вверх
```c
void arm_up(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period);
```
Принимает выбор правой или левой руки, полностью описанную часть руки робота и необходимый период ШИМ.

3. Опускание части руки робота вверх
```c
void arm_down(arm_side_t side, const arm_driver_ctx_t *arm_driver, uint16_t period);
```
Принимает выбор правой или левой руки, полностью описанную часть руки робота и необходимый период ШИМ.

4. Выключение руки
```c
void arm_off (arm_side_t side, const arm_driver_ctx_t *arm_driver);
```
Принимает выбор правой или левой руки, полностью описанную часть руки робота и необходимый период ШИМ.

## Пример использования

В качестве примера рассмотрим применение модуля для описания локтевого сустава для BB-драйвера. 
Описание приведено для левой руки.

На момент написания, в локетвом суставе применялся 3 и 4 таймер STM32F411.

Для начала определим номера каналов, а также номер альтернативной функции. Используем 1 и 2 канал таймера. 
Номер альтернативной функции для 3 и 4 таймера в данном случае равен двум.

```c
const pwm_channel_t ch_left_pwm = {
    .ch_pwm_1 = 0,
    .ch_pwm_2 = 1,
    .alt_func_1 = 2,
    .alt_func_2 = 2
};
```

Определим структуру с настройками ШИМ:
```c
const pwm_ctx_t left_pwm_ctx = {
        .pwm_ch = ch_left_pwm,
        .driver_ptr = &PWMD3,
        .pwm_conf = {
                .frequency = PWM_frequency,
                .period    = PWM_period,
                .callback  = NULL,
                .channels  = {
                        
                        {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// LEFT_PWM_1
                        
                        {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// LEFT_PWM_2

                        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},

                        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
                },
                .cr2        = 0,

    // !!!!!!!! THE CALCULATION WAS MADE FOR A CLOCK FREQUENCY OF 8 MHz AND THE APB1 BUS !!!!!!!! //
                                .bdtr 		= 0b10011100,
    // !!!!!!!! THE CALCULATION WAS MADE FOR A CLOCK FREQUENCY OF 8 MHz AND THE APB1 BUS !!!!!!!! //

                .dier       = 0
        }
};
```

Далее определяем выводы управления и формируем описание для левого локтевого сустава:
```c
const line_driver_t left_control = {
        .PWM_1 = LEFT_PWM_1,
        .PWM_2 = LEFT_PWM_2,
        .digit_1 = LEFT_UP,
        .digit_2 = LEFT_DOWN

};

const control_driver_t left_arm = {
        .line_control = left_control,
        .arm_ctx = left_pwm_ctx
};
```

Аналогичным образом формируется описание для правого локтевого сустава и в итоге сводится в одну структуру:


```c
const arm_driver_ctx_t elbow_driver = {
        .type = BB,
        .arm[0] = left_arm,
        .arm[1] = right_arm
};
```

Полученное описание можно использовать для вызова функций из arm_driver, получая более верхнеуровневые
их реализациия. Например, функция поднятия локтевого сустава просто вызывает arm_up, но при этом, чтобы
ее вызвать нам не надо вспоминать, какая именно структура описывает ту или иную часть робота. 
Мы просто выбирает соответствующую функцию и необходимую руку.



```c
void elbow_up(arm_side_t side, uint16_t period)
{
    arm_up(side, &elbow_driver, period);
}
```

## Допольнительная информация

Автор не утверждает, что данная реализация идеальна) Поэтому при наличии идей по доработке welcome.

По всем поросам обращаться к [adhelll](https://github.com/adhelll).


