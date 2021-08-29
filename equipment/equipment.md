![Миша](https://user-images.githubusercontent.com/71280717/131245913-9ea56fb0-4a8a-46c7-98de-e666c1b67c77.jpg)

# Части робота
Робот состоит из трех частей: 
- основание; 
- туловище;
- голова.

## Описание периферии нижнего уровня

### Описание основания
Основание состоит из:
- 3 электродвигателя;
![Привод перемещения](https://user-images.githubusercontent.com/71280717/131245807-e8c2e9f4-5ca9-4eab-b8fb-fc935f1da8dc.jpg)
 Номинальное напряжение 12В и мощностью 150Вт (см. папку с фото). Ток удержания (блокировка вращения) достигал значние 20А.
- 3 оптических энкодера;
![Оптический энкодер в основании](https://user-images.githubusercontent.com/71280717/131245813-b2c8beb8-1e13-4ec7-bda7-ed373201df05.jpg)
- 3 инфракарсный датчика расстояния sharp gp2d12 (Ссылка на DS: https://engineering.purdue.edu/ME588/SpecSheets/sharp_gp2d12.pdf);
- 4 ультразвуковых датчика расстояния jsn-sr04t (Ссылка на DS: https://www.makerguides.com/wp-content/uploads/2019/02/JSN-SR04T-Datasheet.pdf);
![Ультразвуковой датчик расстояния](https://user-images.githubusercontent.com/71280717/131245821-e8068733-2c04-4d4f-84f9-6ea8d8f0c0b4.jpg)
- uart-приемник 

### Описание туловища 
Туловище состоит из:
- 4 энкодера hae18u5v12a0.5 (Ссылка на DS: https://www.amazon.com/Resolution-Magnetic-Rotary-Encoder-Absolute/dp/B07QJ8S3JM);
![Энкодер рука_1](https://user-images.githubusercontent.com/71280717/131245833-8ec636f3-cefd-4379-bfe2-4843b3eae29e.jpg)
![Энкодер рука_2](https://user-images.githubusercontent.com/71280717/131245836-dae78758-9d40-49c6-839e-9146c7fc71fe.jpg)
![Энкодер рука_3](https://user-images.githubusercontent.com/71280717/131245838-925cd453-19c4-48ed-a841-45689b045c8b.jpg)
- 4 серво SRS-3216HTG (Ссылка на DS: https://cdn-global-hk.hobbyking.com/media/file/14371476X1921611X26.pdf);
![Серво на руке](https://user-images.githubusercontent.com/71280717/131245848-d31677d6-d783-4816-9ee8-3eb3f930a13b.jpg)
- 2 привода линейного перемещения;
![Информация о линейном приводе](https://user-images.githubusercontent.com/71280717/131245856-8765777b-7cff-4de1-9ca2-f07e3282e1cf.jpg)
 Привод установлен на плече робота. Отвечает за поднятие предплечья. Номинальное напряжение 12В. Ток без нагрузки 0.7А, с нагрузкой в 3.140 кг. ток - 2.4А. При последниех замерах уходил в насыщение по току - 1.4А и уже не мог поднять груз.
- 4 двигателя s150106xd88;
![Привод поворота руки](https://user-images.githubusercontent.com/71280717/131245896-239aa275-e2e6-4971-ad6c-ddb0c4fad8fd.jpg)
 Приводы стоят внутри робота. Один отвечает за поворот плеча, другой за поднятие руки. Номинальное напряжение 12В. Ток без нагрузки 0.8А, с нагрузкой в 3.140 кг. ток - 1.4А. Ток удержания (блокировка вращения) достигал значние 7А.


### Описание головы 
Голова состоит из:
- 4 серво HXT900HEXTRONIK (Ссылка на DS: http://electronics.inf.ua/P36.files/Hextronik_HXT900.pdf);
![Серво в голове](https://user-images.githubusercontent.com/71280717/131245904-008c2163-b645-43f6-9ab1-ed5473fc7c2d.jpg)
- 1 серво h king hk15138 (Ссылка на DS: http://www.agspecinfo.com/pdfs/H/HK15138.PDF);

## Описание периферии верхнего уровня
