https://github.com/lsd-maddrive/mishanya-bot-project/blob/feature/%232_Mishanya_equipment/equipment/equipment_pics/%D0%9C%D0%B8%D1%88%D0%B0.jpg
# Части робота
Робот состоит из трех частей: 
- основание; 
- туловище;
- голова.

## Описание периферии нижнего уровня

### Описание основания
Основание состоит из:
- 3 электродвигателя;
https://github.com/lsd-maddrive/mishanya-bot-project/blob/feature/%232_Mishanya_equipment/equipment/equipment_pics/%D0%9F%D1%80%D0%B8%D0%B2%D0%BE%D0%B4%20%D0%BF%D0%B5%D1%80%D0%B5%D0%BC%D0%B5%D1%89%D0%B5%D0%BD%D0%B8%D1%8F%20%D0%B2%20%D0%BE%D1%81%D0%BD%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B8.jpg
 Номинальное напряжение 12В и мощностью 150Вт (см. папку с фото). Ток удержания (блокировка вращения) достигал значние 20А.
- 3 оптических энкодера;
https://github.com/lsd-maddrive/mishanya-bot-project/blob/feature/%232_Mishanya_equipment/equipment/equipment_pics/%D0%9E%D0%BF%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B9%20%D1%8D%D0%BD%D0%BA%D0%BE%D0%B4%D0%B5%D1%80%20%D0%B2%20%D0%BE%D1%81%D0%BD%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B8.jpg
- 3 инфракарсный датчика расстояния sharp gp2d12 (Ссылка на DS: https://engineering.purdue.edu/ME588/SpecSheets/sharp_gp2d12.pdf);
- 4 ультразвуковых датчика расстояния jsn-sr04t (Ссылка на DS: https://www.makerguides.com/wp-content/uploads/2019/02/JSN-SR04T-Datasheet.pdf);
https://github.com/lsd-maddrive/mishanya-bot-project/blob/feature/%232_Mishanya_equipment/equipment/equipment_pics/%D0%A3%D0%BB%D1%8C%D1%82%D1%80%D0%B0%D0%B7%D0%B2%D1%83%D0%BA%D0%BE%D0%B2%D0%BE%D0%B9%20%D0%B4%D0%B0%D1%82%D1%87%D0%B8%D0%BA%20%D1%80%D0%B0%D1%81%D1%81%D1%82%D0%BE%D1%8F%D0%BD%D0%B8%D1%8F.jpg
- uart-приемник 

### Описание туловища 
Туловище состоит из:
- 4 энкодера hae18u5v12a0.5 (Ссылка на DS: https://www.amazon.com/Resolution-Magnetic-Rotary-Encoder-Absolute/dp/B07QJ8S3JM);
https://github.com/lsd-maddrive/mishanya-bot-project/blob/feature/%232_Mishanya_equipment/equipment/equipment_pics/%D0%AD%D0%BD%D0%BA%D0%BE%D0%B4%D0%B5%D1%80%20%D1%80%D1%83%D0%BA%D0%B0_1.jpg
https://github.com/lsd-maddrive/mishanya-bot-project/blob/feature/%232_Mishanya_equipment/equipment/equipment_pics/%D0%AD%D0%BD%D0%BA%D0%BE%D0%B4%D0%B5%D1%80%20%D1%80%D1%83%D0%BA%D0%B0_2.jpg
https://github.com/lsd-maddrive/mishanya-bot-project/blob/feature/%232_Mishanya_equipment/equipment/equipment_pics/%D0%AD%D0%BD%D0%BA%D0%BE%D0%B4%D0%B5%D1%80%20%D1%80%D1%83%D0%BA%D0%B0_3.jpg
- 4 серво SRS-3216HTG (Ссылка на DS: https://cdn-global-hk.hobbyking.com/media/file/14371476X1921611X26.pdf);
https://github.com/lsd-maddrive/mishanya-bot-project/blob/feature/%232_Mishanya_equipment/equipment/equipment_pics/%D0%A1%D0%B5%D1%80%D0%B2%D0%BE%20%D0%BD%D0%B0%20%D1%80%D1%83%D0%BA%D0%B5.jpg
- 2 привода линейного перемещения;
https://github.com/lsd-maddrive/mishanya-bot-project/blob/feature/%232_Mishanya_equipment/equipment/equipment_pics/%D0%98%D0%BD%D1%84%D0%BE%D1%80%D0%BC%D0%B0%D1%86%D0%B8%D1%8F%20%D0%BE%20%D0%BB%D0%B8%D0%BD%D0%B5%D0%B9%D0%BD%D0%BE%D0%BC%20%D0%BF%D1%80%D0%B8%D0%B2%D0%BE%D0%B4%D0%B5.jpg
 Привод установлен на плече робота. Отвечает за поднятие предплечья. Номинальное напряжение 12В. Ток без нагрузки 0.7А, с нагрузкой в 3.140 кг. ток - 2.4А. При последниех замерах уходил в насыщение по току - 1.4А и уже не мог поднять груз.
- 4 двигателя s150106xd88;
https://github.com/lsd-maddrive/mishanya-bot-project/blob/feature/%232_Mishanya_equipment/equipment/equipment_pics/%D0%9F%D1%80%D0%B8%D0%B2%D0%BE%D0%B4%20%D0%BF%D0%BE%D0%B2%D0%BE%D1%80%D0%BE%D1%82%D0%B0%20%D1%80%D1%83%D0%BA%D0%B8.jpg
 Приводы стоят внутри робота. Один отвечает за поворот плеча, другой за поднятие руки. Номинальное напряжение 12В. Ток без нагрузки 0.8А, с нагрузкой в 3.140 кг. ток - 1.4А. Ток удержания (блокировка вращения) достигал значние 7А.


### Описание головы 
Голова состоит из:
- 4 серво HXT900HEXTRONIK (Ссылка на DS: http://electronics.inf.ua/P36.files/Hextronik_HXT900.pdf);
https://github.com/lsd-maddrive/mishanya-bot-project/blob/feature/%232_Mishanya_equipment/equipment/equipment_pics/%D0%A1%D0%B5%D1%80%D0%B2%D0%BE%20%D0%B2%20%D0%B3%D0%BE%D0%BB%D0%BE%D0%B2%D0%B5.jpg
- 1 серво h king hk15138 (Ссылка на DS: http://www.agspecinfo.com/pdfs/H/HK15138.PDF);

## Описание периферии верхнего уровня
