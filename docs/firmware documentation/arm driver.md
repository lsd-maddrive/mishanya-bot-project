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
- BB - управление осуществляется четырьмя выводами (4 ШИМ);
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


- ioline_t 	lin_1:
  * Нижний ключ первого полумоста при работе с BB;
  * Первый цифровой вывод при работе с RED.
- ioline_t 	lin_2:
  * Нижний ключ второго полумоста при работе с BB;
  * Второй цифровой вывод при работе с RED.
- ioline_t 	hin_1:
  * Верхний ключ первого полумоста при работе с BB;
  * Вывод ШИМ при работе с RED.
- ioline_t 	hin_2:
  * Верхний ключ второго полумоста при работе с BB;
  * Не используется при работе с RED.

6. normalize_angle_t

- target - флаг был ли достигнут заданный угол
- target_angle - заданный угол;
- max_norm_angle - нормированное значение энкодера соответствущее максимальному углу;  
- min_norm_angle - нормированное значение энкодера соответствущее минимальному углу;
- shift - смещение между нулем и минимальным ненормированным углом;
- zero_cross - флаг есть ли нуль между крайними положениями энкодера.

7. angle_lim_t

- min_angle - минимальное положение энкодера 
- max_angle - максимальное положение энкодера

8. traking_cs_t

- normalize_angle - структура из пунтка 6;
- angle_lim - структура из пункта 7;
- arm_PID - настройка регулятора;
- angle_dead_zone - мертвая зона регулирования

9. control_driver_t

Объединяет в себе структуры из пункта 4 и 5.

10. arm_system_t

Объединяет в себе структуры из пункта 8 и 9.


11. arm_driver_ctx_t

Содержит enum из пункта 2, указатели на функции управления рукой
и массив из двух элементов типа control_driver_t (первый элемент описывает левую руку, второй правую). 

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

На момент написания, в локетвом суставе применялся 1 таймер STM32F411.

Для начала определим номера каналов, а также номер альтернативной функции. Используем 1 и 2 канал таймера. 
Номер альтернативной функции для 1 таймера в данном случае равен единице.

```c
const pwm_channel_t ch_left_pwm = {
    .ch_pwm_1 = 0,
    .ch_pwm_2 = 1,
    .alt_func_1 = 1,
    .alt_func_2 = 1
};
```

Определим структуру с настройками ШИМ:
```c
const pwm_ctx_t left_pwm_ctx = {
    .pwm_ch = ch_left_pwm,
    .driver_ptr = &PWMD1,
    .pwm_conf = {
    .frequency = PWM_frequency,
    .period    = PWM_period,
    .callback  = NULL,
    .channels  = {
            
            {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// LEFT LIN1 & HIN1
            
            {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // LEFT HIN2 & LIN2
            
            {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},	// RIGHT LIN1 & HIN1
            
            {.mode = PWM_OUTPUT_ACTIVE_HIGH | PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},  // RIGHT LN2 & HIN2I
        
        },
        .cr2        = 0,
        // !!!!!!!! THE CALCULATION WAS MADE FOR F411 !!!!!!!! //
        .bdtr 		= 0b11111111,
        // !!!!!!!! THE CALCULATION WAS MADE FOR F411 !!!!!!!! //
        .dier       = 0
    }
};

```

Далее определяем выводы управления и формируем описание для левого локтевого сустава:
```c
const line_driver_t left_control = {
    .hin_1 = LEFT_HIN_1,
    .hin_2 = LEFT_HIN_2,
    .lin_1 = LEFT_LIN_1,
    .lin_2 = LEFT_LIN_2
};

const control_driver_t left_arm = {
    .line_control = left_control,
    .pwm_setting_ctx = left_pwm_ctx
};
```

Объявляем, но не инициализируем структуры контура управления и руки, далее они сведутся в elbow_driver:

traking_cs_t left_cs;
arm_system_t left_system;

arm_driver_ctx_t elbow_driver;

Аналогичным образом формируется описание для правого локтевого сустава, в функции init определяем структуры выше:


```c
left_cs.angle_lim = left_angle_lim;
left_cs.angle_dead_zone = ENCODER_DEADZONE;
left_cs.arm_PID = elbow_PID;

left_system.traking_cs = left_cs;
left_system.control = left_arm;

elbow_driver.type = DRIVER;
elbow_driver.down = &elbow_down;
elbow_driver.up = &elbow_up;
elbow_driver.off = &elbow_off;
elbow_driver.arm[0] = left_system;
elbow_driver.arm[1] = right_system;
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

По всем вопросам обращаться к [adhelll](https://github.com/adhelll).


