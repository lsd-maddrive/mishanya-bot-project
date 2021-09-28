![Миша](equipment_pics/Миша.jpg)

# Части робота
Робот состоит из трех частей: 
- основание; 
- туловище;
- голова.

## Описание периферии нижнего уровня

### Описание основания
Основание состоит из:
- 3 электродвигателя;
    - Номинальное напряжение 12В и мощностью 150Вт (см. папку с фото). Ток удержания (блокировка вращения) достигал значние 20А.
    <details><summary>Фото</summary>

    ![Привод перемещения](equipment_pics/base_movement_drive.jpg)
    </details>

- 3 оптических энкодера:
    - На диске энкодера 20 засечек, шаг квантования 18 градусов при работе по фронту, 9 градусов при работе по фронту и срезу.
    <details><summary>Фото</summary>
    
    ![Оптический энкодер в основании](equipment_pics/base_optical_encoder.jpg)
    </details>

- 3 инфракарсный датчика расстояния **sharp gp2d12** [Ссылка на DS](https://engineering.purdue.edu/ME588/SpecSheets/sharp_gp2d12.pdf);

- 4 ультразвуковых датчика расстояния **jsn-sr04t** [Ссылка на DS](https://www.makerguides.com/wp-content/uploads/2019/02/JSN-SR04T-Datasheet.pdf);

    <details><summary>Фото</summary>

    ![Ультразвуковой датчик расстояния](equipment_pics/base_ultrasonic_sensor.jpg)
    </details>

- uart-приемник 

### Описание туловища 
Туловище состоит из:
- 4 энкодера hae18u5v12a0.5 [Ссылка на DS](https://www.amazon.com/Resolution-Magnetic-Rotary-Encoder-Absolute/dp/B07QJ8S3JM);
    <details><summary>Фото</summary>

    ![Энкодер рука_1](equipment_pics/arm_encoder_1.jpg)
    ![Энкодер рука_2](equipment_pics/arm_encoder_2.jpg)
    ![Энкодер рука_3](equipment_pics/arm_encoder_3.jpg)
    </details>

- 4 серво SRS-3216HTG [Ссылка на DS](https://cdn-global-hk.hobbyking.com/media/file/14371476X1921611X26.pdf);

    - Один серво управляет хватом, второй вращает хват вокруг своей оси. 
    - Возможный ход 270 градусов, с длительностью управляющих импульсов 0.9-2.1мкс. 
    - Серво в кисти имеет механические ограничения. 
    - Допустимы диапазон работы соответствует диапазону импульсов 1.11-1.62мкс. В случае выхода из диапазона ток удержания по даташиту порядка 6А. 
    > ⚠️ В одной из рук не работает серво в локте, возможно механически заблокирован.
    <details><summary>Фото</summary>

    ![Серво на руке](equipment_pics/arm_servo.jpg)
    </details>

- 2 привода линейного перемещения;
    - Привод установлен на плече робота. Отвечает за поднятие предплечья. 
    - Номинальное напряжение 12В.
    - Ток без нагрузки 0.7А, с нагрузкой в 3.140 кг. ток - 2.4А.
    - При последниех замерах уходил в насыщение по току - 1.4А и уже не мог поднять груз.

    <details><summary>Фото</summary>

    ![Информация о линейном приводе](equipment_pics/arm_linear_drive_info.jpg)
    </details>

- 4 двигателя **s150106xd88**;
    - Приводы стоят внутри робота. 
    - Один отвечает за поворот плеча, другой за поднятие руки.
    - Номинальное напряжение 12В. 
    - Ток без нагрузки 0.8А, с нагрузкой в 3.140 кг. ток - 1.4А. 
    - Ток удержания (блокировка вращения) достигал значние 7А.
    
    <details><summary>Фото</summary>

    ![Привод поворота руки](equipment_pics/arm_rotation_drive.jpg)
    </details>


### Описание головы 
Голова состоит из:
- 4 серво **HXT900HEXTRONIK** [Ссылка на DS](http://electronics.inf.ua/P36.files/Hextronik_HXT900.pdf);
    <details><summary>Фото</summary>

    ![Серво в голове](equipment_pics/head_servo.jpg)
    </details>
- 1 серво **h king hk15138** [Ссылка на DS](http://www.agspecinfo.com/pdfs/H/HK15138.PDF);

## Описание периферии верхнего уровня
