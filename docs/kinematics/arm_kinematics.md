<p align="center">
<img src="Arm.png">
</p>
<details>
<summary>Обозначения и значения параметров</summary>

Значение параметров взяты [отсюда](https://github.com/lsd-maddrive/mishanya-bot-project/blob/develop/docs/kinematics/dimensions.md)

| Обозначение| Смысл| Значение, ед. изм.|
| -------------------|:---------------:| ---------:|
| *XY*      | абсолютная система координат | м |
| *X'Y'*      | связанная система координат      |   м |
| <a href="https://www.codecogs.com/eqnedit.php?latex=\alpha" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\alpha" title="\alpha" /></a> | угол поворота основания      |    рад |
| <a href="https://www.codecogs.com/eqnedit.php?latex=\Omega" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\Omega" title="\Omega" /></a>      | угловая скорость основания | рад/с |
| *L*      | радиус основания | 0.40643 м |
| <a href="https://www.codecogs.com/eqnedit.php?latex=V_{x},V_{y}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?V_{x},V_{y}" title="V_{x},V_{y}" /></a>      | линейные скорости основания в абсолютной системе | м/с |
|<a href="https://www.codecogs.com/eqnedit.php?latex=V_{a},V_{b},V_{c}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?V_{a},V_{b},V_{c}" title="V_{a},V_{b},V_{c}" /></a>|линейные скорости омниколёс|м/с|
|<a href="https://www.codecogs.com/eqnedit.php?latex=\omega_{a},\omega_{b},\omega_{c}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\omega_{a},\omega_{b},\omega_{c}" title="\omega_{a},\omega_{b},\omega_{c}" /></a>|угловые скорости омниколёс|рад/с|
|*r*|радиус омниколёс|0.061 м|

</details>

Прямая кинематика:

<a href="https://www.codecogs.com/eqnedit.php?latex=\begin{cases}x&space;=&space;L_{1}\sin(&space;\theta&space;_{1})&plus;L_{2}\cos(&space;\theta&space;_{2})\sin(&space;\theta&space;_{1})&plus;L_{2}\cos(&space;\theta&space;_{1})\cos(&space;\theta_{3})sin(&space;\theta_{2})\\y&space;=&space;L_{1}\cos(&space;\theta&space;_{1})&plus;L_{2}\cos(&space;\theta&space;_{1})\cos(&space;\theta&space;_{2})-L_{2}\cos(&space;\theta&space;_{3})\sin(&space;\theta_{1})sin(&space;\theta_{2})\\z&space;=&space;\sin(&space;\theta&space;_{3})(L_{1}\sin(&space;2\theta&space;_{1}&plus;\theta&space;_{2})&plus;L_{1}\sin(&space;2\theta&space;_{1}))\end{cases}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\begin{cases}x&space;=&space;L_{1}\sin(&space;\theta&space;_{1})&plus;L_{2}\cos(&space;\theta&space;_{2})\sin(&space;\theta&space;_{1})&plus;L_{2}\cos(&space;\theta&space;_{1})\cos(&space;\theta_{3})sin(&space;\theta_{2})\\y&space;=&space;L_{1}\cos(&space;\theta&space;_{1})&plus;L_{2}\cos(&space;\theta&space;_{1})\cos(&space;\theta&space;_{2})-L_{2}\cos(&space;\theta&space;_{3})\sin(&space;\theta_{1})sin(&space;\theta_{2})\\z&space;=&space;\sin(&space;\theta&space;_{3})(L_{1}\sin(&space;2\theta&space;_{1}&plus;\theta&space;_{2})&plus;L_{1}\sin(&space;2\theta&space;_{1}))\end{cases}" title="\begin{cases}x = L_{1}\sin( \theta _{1})+L_{2}\cos( \theta _{2})\sin( \theta _{1})+L_{2}\cos( \theta _{1})\cos( \theta_{3})sin( \theta_{2})\\y = L_{1}\cos( \theta _{1})+L_{2}\cos( \theta _{1})\cos( \theta _{2})-L_{2}\cos( \theta _{3})\sin( \theta_{1})sin( \theta_{2})\\z = \sin( \theta _{3})(L_{1}\sin( 2\theta _{1}+\theta _{2})+L_{1}\sin( 2\theta _{1}))\end{cases}" /></a>

###
<details>
<summary>Вывод уравнений</summary>

Для вывода уравнений прямой кинематики сначала рассмотрим движение в плоскости манипулятора - XY, не рассматривая пока что вращение вокруг плеча.

Первое звено L1 закреплёно одним концом на плече в точки О и поворачивается на угол <img src="https://latex.codecogs.com/svg.image?\theta&space;_{1}" title="\theta _{1}" />,
второе звено L2 крепится к концу первого звена в точке a1 и поворачивается относительно него на угол <img src="https://latex.codecogs.com/svg.image?\theta&space;_{2}" title="\theta _{2}" />.
Задавать мы пытаемся координаты конца второго звена - точки a2.

Найдём сначала положение точки a1 относительно точки крепления плеча:

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}X_{a1}=L_{1}\cdot&space;\cos(&space;\theta&space;_{1})\\Y_{a1}=L_{1}\cdot&space;\sin(&space;\theta&space;_{1})\end{matrix}\right." title="\left\{\begin{matrix}X_{a1}=L_{1}\cdot \cos( \theta _{1})\\Y_{a1}=L_{1}\cdot \sin( \theta _{1})\end{matrix}\right." />

Далее положение точки a2 относительно точки a1:

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}X_{a2}^{'}=L_{2}\cdot&space;\cos(&space;\theta&space;_{2})\\Y_{a2}^{'}=L_{2}\cdot&space;\sin(&space;\theta&space;_{2})\end{matrix}\right." title="\left\{\begin{matrix}X_{a2}^{'}=L_{2}\cdot \cos( \theta _{2})\\Y_{a2}^{'}=L_{2}\cdot \sin( \theta _{2})\end{matrix}\right." />

Так как система координат, привязанная к точке a1 также вращается - учтём это в относитльном положении для точки a2. Расчёт коордиеат во вращающейся системе осуществляется с использованием матрицы поворота: умножаем предыдущую систему на матрицу поворота угла <img src="https://latex.codecogs.com/svg.image?\theta&space;_{1}" title="\theta _{1}" />. Таким образом положение точки a2 относительно точки a1 в случае вращающейся системы координат получим:

<img src="https://latex.codecogs.com/svg.image?\begin{bmatrix}X_{a2}^{''}\\Y_{a2}^{''}\end{bmatrix}&space;=&space;\begin{bmatrix}cos(&space;\theta&space;_{1}&space;)&-sin(&space;\theta&space;_{1}&space;)\\&space;sin(&space;\theta&space;_{1})&cos(&space;\theta&space;_{1}&space;)\end{bmatrix}&space;\begin{bmatrix}L_{2}\cdot&space;\cos(&space;\theta&space;_{2})\\L_{2}\cdot&space;\sin(&space;\theta&space;_{2})\end{bmatrix}" title="\begin{bmatrix}X_{a2}^{''}\\Y_{a2}^{''}\end{bmatrix} = \begin{bmatrix}cos( \theta _{1} )&-sin( \theta _{1} )\\ sin( \theta _{1})&cos( \theta _{1} )\end{bmatrix} \begin{bmatrix}L_{2}\cdot \cos( \theta _{2})\\L_{2}\cdot \sin( \theta _{2})\end{bmatrix}" />

Раскрыв правую часть и используя формулу косинуса и синуса сумму углов, получим:

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}X_{a2}^{''}=L_{2}\cdot&space;\cos(&space;\theta&space;_{1}&space;&plus;&space;\theta&space;_{2})\\Y_{a2}^{''}=L_{2}\cdot&space;\sin(&space;\theta&space;_{1}&space;&plus;&space;\theta&space;_{2})\end{matrix}\right." title="\left\{\begin{matrix}X_{a2}^{''}=L_{2}\cdot \cos( \theta _{1} + \theta _{2})\\Y_{a2}^{''}=L_{2}\cdot \sin( \theta _{1} + \theta _{2})\end{matrix}\right." />

Если помимо вращение системы координат, привязанной к точки a1, учесть также смещение этой точки относительно начала глобальной системы координат, которое по сути равно координатам точки a1 в этой глобальной системе, окончательно получим:

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}X_{a2}=L_{1}\cdot&space;\cos(&space;\theta&space;_{1}&space;)&plus;L_{2}\cdot&space;\cos(&space;\theta&space;_{1}&space;&plus;&space;\theta&space;_{2})\\Y_{a2}=L_{1}\cdot&space;\sin(&space;\theta&space;_{1})&plus;L_{2}\cdot&space;\sin(&space;\theta&space;_{1}&space;&plus;&space;\theta&space;_{2})\end{matrix}\right." title="\left\{\begin{matrix}X_{a2}=L_{1}\cdot \cos( \theta _{1} )+L_{2}\cdot \cos( \theta _{1} + \theta _{2})\\Y_{a2}=L_{1}\cdot \sin( \theta _{1})+L_{2}\cdot \sin( \theta _{1} + \theta _{2})\end{matrix}\right." />

Далее нужно учесть поворот плоскости манипулятора вокруг оси звена L1  на угол <img src="https://latex.codecogs.com/svg.image?\theta_{3}&space;" title="\theta_{3} " />

Для этого используем уравнение матрицы поворота вокруг произвольной оси, взятое [отсюда](https://ru.wikipedia.org/wiki/%D0%9C%D0%B0%D1%82%D1%80%D0%B8%D1%86%D0%B0_%D0%BF%D0%BE%D0%B2%D0%BE%D1%80%D0%BE%D1%82%D0%B0):

<img src="https://latex.codecogs.com/svg.image?M(\hat{\mathbf{v}},\theta)&space;=&space;\begin{pmatrix}&space;&space;&space;\cos&space;\theta&space;&plus;&space;(1&space;-&space;\cos&space;\theta)&space;x^2&space;&&space;(1&space;-&space;\cos&space;\theta)&space;x&space;y&space;-&space;(\sin&space;\theta)&space;z&space;&space;&&space;(1&space;-&space;\cos&space;\theta)&space;x&space;z&space;&plus;&space;(\sin&space;\theta)&space;y&space;&space;\\&space;&space;&space;(1&space;-&space;\cos&space;\theta)&space;y&space;x&space;&plus;&space;(\sin&space;\theta)&space;z&space;&space;&&space;\cos&space;\theta&space;&plus;&space;(1&space;-&space;\cos&space;\theta)&space;y^2&space;&&space;(1&space;-&space;\cos&space;\theta)&space;y&space;z&space;-&space;(\sin&space;\theta)&space;x\\&space;&space;&space;(1&space;-&space;\cos&space;\theta)&space;z&space;x&space;-&space;(\sin&space;\theta)&space;y&space;&&space;(1&space;-&space;\cos&space;\theta)&space;z&space;y&space;&plus;&space;(\sin&space;\theta)&space;x&space;&&space;\cos&space;\theta&space;&plus;&space;(1&space;-&space;\cos&space;\theta)&space;z^2&space;\end{pmatrix}" title="M(\hat{\mathbf{v}},\theta) = \begin{pmatrix} \cos \theta + (1 - \cos \theta) x^2 & (1 - \cos \theta) x y - (\sin \theta) z & (1 - \cos \theta) x z + (\sin \theta) y \\ (1 - \cos \theta) y x + (\sin \theta) z & \cos \theta + (1 - \cos \theta) y^2 & (1 - \cos \theta) y z - (\sin \theta) x\\ (1 - \cos \theta) z x - (\sin \theta) y & (1 - \cos \theta) z y + (\sin \theta) x & \cos \theta + (1 - \cos \theta) z^2 \end{pmatrix}" />

Для задания поворота нам нужно знать единичный вектор поворота <img src="https://latex.codecogs.com/svg.image?\hat{\mathbf{v}}&space;=&space;(x,y,z)" title="\hat{\mathbf{v}} = (x,y,z)" />, который задаёт направление оси, вокруг которой происходит поворот, и угол поворота <img src="https://latex.codecogs.com/svg.image?\theta" title="\theta" />. Углом поворота будет, собственно, угол <img src="https://latex.codecogs.com/svg.image?\theta_{3}&space;" title="\theta_{3} " />. Так как вращение идёт вокруг оси звена L1, единичный вектор будет задаваться аналогично координатам точки а1 относительно точки O(см. выше), но с единичной амплитудой - без домножения на L1(так как присутсвие в формулах величины L1 задаёт именно положение точки а1, так как именно на расстоянии L1 находится точка a1). Координата z оси вращения будет всегда равна 0, так как ось двигается в плоскости. Таким образом:

<img src="https://latex.codecogs.com/svg.image?\hat{\mathbf{v}}&space;=&space;(x,y,z)&space;=&space;(\cos(&space;\theta&space;_{1}),\sin(&space;\theta&space;_{1}),0)" title="\hat{\mathbf{v}} = (x,y,z) = (\cos( \theta _{1}),\sin( \theta _{1}),0)" />

В силу громоздкости записи и вычислений был использован матлаб-скрипт [Hand_formul.m](Hand_formul.m). В нём прописаны символьные выражения и вычисления: для системы уравнений точки хвата в неподвижной плосоксти манипулятора; подстановка в формулу матрицы вращения вокруг произвольной оси на угол <img src="https://latex.codecogs.com/svg.image?\theta_{3}&space;" title="\theta_{3} " /> координат единичного вектора оси L1; умножение полученной матрицы поворота на систему уравнений координат в неподвижной плоскости; автоматическое упрощение полученных символьных выражений. После проделанных действий, скрипт выводит символьное выражение для прямой кинематики, которые обозначены в самом начале.

</details>