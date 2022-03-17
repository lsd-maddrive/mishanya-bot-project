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

<img src="https://latex.codecogs.com/svg.image?\begin{cases}x&space;=&space;\cos(&space;\theta_{1})\cdot&space;(L_{1}&plus;L_{2}\cos(&space;\theta&space;_{2}))-L_{2}\cos(&space;\theta&space;_{3})\sin(&space;\theta_{1})\sin(&space;\theta_{2})\\y&space;=&space;\sin(&space;\theta_{1})\cdot&space;(L_{1}&plus;L_{2}\cos(&space;\theta&space;_{2}))&plus;L_{2}\cos(&space;\theta&space;_{1})\cos(&space;\theta_{3})\sin(&space;\theta_{2})\\z&space;=&space;L_{2}\sin(&space;\theta_{2})\sin(&space;\theta_{3})\end{cases}" title="https://latex.codecogs.com/svg.image?\begin{cases}x = \cos( \theta_{1})\cdot (L_{1}+L_{2}\cos( \theta _{2}))-L_{2}\cos( \theta _{3})\sin( \theta_{1})\sin( \theta_{2})\\y = \sin( \theta_{1})\cdot (L_{1}+L_{2}\cos( \theta _{2}))+L_{2}\cos( \theta _{1})\cos( \theta_{3})\sin( \theta_{2})\\z = L_{2}\sin( \theta_{2})\sin( \theta_{3})\end{cases}" />

Обратная кинематика:

Для начала введём несколько обозначений:
<img src="http://latex.codecogs.com/svg.latex?A&space;=&space;-2\cdot&space;x_{0}" title="http://latex.codecogs.com/svg.latex?A = -2\cdot x_{0}" /> , <img src="http://latex.codecogs.com/svg.latex?B&space;=&space;-2\cdot&space;y_{0}" title="http://latex.codecogs.com/svg.latex?B = -2\cdot y_{0}" /> , <img src="http://latex.codecogs.com/svg.latex?C&space;=&space;-2\cdot&space;z_{0}" title="http://latex.codecogs.com/svg.latex?C = -2\cdot z_{0}" /> , <img src="http://latex.codecogs.com/svg.latex?d&space;=&space;x_{0}^{2}&space;&plus;&space;y_{0}^{2}&space;&plus;&space;z_{0}^{2}" title="http://latex.codecogs.com/svg.latex?d = x_{0}^{2} + y_{0}^{2} + z_{0}^{2}" /> , где <img src="http://latex.codecogs.com/svg.latex?x_{0},&space;y_{0},&space;z_{0}" title="http://latex.codecogs.com/svg.latex?x_{0}, y_{0}, z_{0}" /> - координаты желаемой точки.
Далее обозначим:
###
<img src="http://latex.codecogs.com/svg.latex?D&space;=&space;L_{1}^{2}&space;-&space;L_{2}^{2}&space;&plus;&space;d" title="http://latex.codecogs.com/svg.latex?D = L_{1}^{2} - L_{2}^{2} + d" />
###
<img src="http://latex.codecogs.com/svg.latex?y_{m_{1,2}}&space;=&space;\frac{-2DB\pm&space;\sqrt{(2DB)^{2}-4(A^{2}&plus;B^{2})(D^{2}-(AL_{1})^{2})}}{2(A^{2}&plus;B^{2})}" title="http://latex.codecogs.com/svg.latex?y_{m_{1,2}} = \frac{-2DB\pm \sqrt{(2DB)^{2}-4(A^{2}+B^{2})(D^{2}-(AL_{1})^{2})}}{2(A^{2}+B^{2})}" />
###
<img src="http://latex.codecogs.com/svg.latex?x_{m_{1,2}}&space;=&space;\frac{-D-By_{m_{1,2}}}{A}" title="http://latex.codecogs.com/svg.latex?x_{m_{1,2}} = \frac{-D-By_{m_{1,2}}}{A}" /> или <img src="https://latex.codecogs.com/svg.image?x_{m_{1,2}}&space;=&space;\sqrt{L_{1}^{2}-y_{m_{1,2}}^{2}}" title="https://latex.codecogs.com/svg.image?x_{m_{1,2}} = \sqrt{L_{1}^{2}-y_{m_{1,2}}^{2}}" />

Окончательно:

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}\theta&space;_{1}=\arctan(\frac{y_{m}}{x_{m}})\\\\\theta&space;_{2}=\pi&space;-\arccos(\frac{L_{1}^{2}&plus;L_{2}^{2}-d}{2L_{1}L_{2}})\\\\\theta&space;_{3}=\frac{\pi}{2}&space;-&space;\arctan(\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}}})\end{matrix}\right." title="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}\theta _{1}=\arctan(\frac{y_{m}}{x_{m}})\\\\\theta _{2}=\pi -\arccos(\frac{L_{1}^{2}+L_{2}^{2}-d}{2L_{1}L_{2}})\\\\\theta _{3}=\frac{\pi}{2} - \arctan(\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2}}})\end{matrix}\right." />

###
<details>
<summary>Вывод уравнений</summary>

Для прямой кинематики:

Для начала отметим, что точки a1 и a2 всегда лежат в одной плоскости, которую мы будем называть плоскостью манипулятора. Внутри этой плоскости они однозначно связаны через угол <img src="https://latex.codecogs.com/svg.image?\theta_{2}" title="https://latex.codecogs.com/svg.image?\theta_{2}" />, поэтому сразу вычислим эту связь.

Первое звено L1 закреплёно одним концом на плече в точки О и поворачивается на угол <img src="https://latex.codecogs.com/svg.image?\theta&space;_{1}" title="\theta _{1}" />,
второе звено L2 крепится к концу первого звена в точке a1 и поворачивается относительно него на угол <img src="https://latex.codecogs.com/svg.image?\theta&space;_{2}" title="\theta _{2}" />.
Задавать мы пытаемся координаты конца второго звена - точки a2.

Найдём сначала положение точки a1 относительно точки крепления плеча:

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}X_{a1}=L_{1}\cdot&space;\sin(&space;\theta&space;_{1})\\Y_{a1}=L_{1}\cdot&space;\cos(&space;\theta&space;_{1})\end{matrix}\right." title="\left\{\begin{matrix}X_{a1}=L_{1}\cdot \sin( \theta _{1})\\Y_{a1}=L_{1}\cdot \cos( \theta _{1})\end{matrix}\right." />

Далее положение точки a2 относительно точки a1:

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}X_{a2}^{'}=L_{2}\cdot&space;\sin(&space;\theta&space;_{2})\\Y_{a2}^{'}=L_{2}\cdot&space;\cos(&space;\theta&space;_{2})\end{matrix}\right." title="\left\{\begin{matrix}X_{a2}^{'}=L_{2}\cdot \sin( \theta _{2})\\Y_{a2}^{'}=L_{2}\cdot \cos( \theta _{2})\end{matrix}\right." />

Так как система координат, привязанная к точке a1 также вращается - учтём это в относитльном положении для точки a2. Расчёт коордиеат во вращающейся системе осуществляется с использованием матрицы поворота: умножаем предыдущую систему на матрицу поворота угла <img src="https://latex.codecogs.com/svg.image?\theta&space;_{1}" title="\theta _{1}" />. Таким образом положение точки a2 относительно точки a1 в случае вращающейся системы координат получим:

<img src="https://latex.codecogs.com/svg.image?\begin{bmatrix}X_{a2}^{''}\\Y_{a2}^{''}\end{bmatrix}&space;=&space;\begin{bmatrix}cos(&space;\theta&space;_{1}&space;)&-sin(&space;\theta&space;_{1}&space;)\\&space;sin(&space;\theta&space;_{1})&cos(&space;\theta&space;_{1}&space;)\end{bmatrix}&space;\begin{bmatrix}L_{2}\cdot&space;\sin(&space;\theta&space;_{2})\\L_{2}\cdot&space;\cos(&space;\theta&space;_{2})\end{bmatrix}" title="\begin{bmatrix}X_{a2}^{''}\\Y_{a2}^{''}\end{bmatrix} = \begin{bmatrix}cos( \theta _{1} )&-sin( \theta _{1} )\\ sin( \theta _{1})&cos( \theta _{1} )\end{bmatrix} \begin{bmatrix}L_{2}\cdot \sin( \theta _{2})\\L_{2}\cdot \cos( \theta _{2})\end{bmatrix}" />

Раскрыв правую часть и используя формулу косинуса и синуса суммы углов, получим:

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}X_{a2}^{''}=L_{2}\cdot&space;\cos(&space;\theta&space;_{1}&space;&plus;&space;\theta&space;_{2})\\Y_{a2}^{''}=L_{2}\cdot&space;\sin(&space;\theta&space;_{1}&space;&plus;&space;\theta&space;_{2})\end{matrix}\right." title="\left\{\begin{matrix}X_{a2}^{''}=L_{2}\cdot \cos( \theta _{1} + \theta _{2})\\Y_{a2}^{''}=L_{2}\cdot \sin( \theta _{1} + \theta _{2})\end{matrix}\right." />

Если помимо вращение системы координат, привязанной к точки a1, учесть также смещение этой точки относительно начала глобальной системы координат, которое по сути равно координатам точки a1 в этой глобальной системе, окончательно получим:

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}X_{a2}=L_{1}\cdot&space;\cos(&space;\theta&space;_{1}&space;)&plus;L_{2}\cdot&space;\cos(&space;\theta&space;_{1}&space;&plus;&space;\theta&space;_{2})\\Y_{a2}=L_{1}\cdot&space;\sin(&space;\theta&space;_{1})&plus;L_{2}\cdot&space;\sin(&space;\theta&space;_{1}&space;&plus;&space;\theta&space;_{2})\end{matrix}\right." title="\left\{\begin{matrix}X_{a2}=L_{1}\cdot \cos( \theta _{1} )+L_{2}\cdot \cos( \theta _{1} + \theta _{2})\\Y_{a2}=L_{1}\cdot \sin( \theta _{1})+L_{2}\cdot \sin( \theta _{1} + \theta _{2})\end{matrix}\right." />

Далее заметим, что остальные углы лишь поворачивают эту плоскость вокруг какой-то произвольной оси. Для задания этих поворотов воспользуемся углами Эйлера. Они позволяют сложное вращательное движение в пространстве(у нас нет поступательных движений) представить как последовательное вращение вокруг определённых осей, что более простая задача. Все формулы были взяты [отсюда](https://ru.wikipedia.org/wiki/%D0%A3%D0%B3%D0%BB%D1%8B_%D0%AD%D0%B9%D0%BB%D0%B5%D1%80%D0%B0). Пускай начальное положение манипулятора лежит полностью в плоскости XY, причём так, что ось звена L1 сонаправлена с осью X, т.е. следующим образом:

<img src="Arm_start_position.png">

Сделали мы так, чтобы вращение вокруг звена L1 совпадало с вращением вокруг оси X, а не было вращением вокруг какой-то произвольно ориентированной в пространстве оси. Таким образом, сделав вращение сначала вокруг оси X на угол <img src="https://latex.codecogs.com/svg.image?\theta_{3}" title="https://latex.codecogs.com/svg.image?\theta_{3}" /> из начального положения, а после из нового положения - вокруг оси Z на угол <img src="https://latex.codecogs.com/svg.image?\theta_{1}" title="https://latex.codecogs.com/svg.image?\theta_{1}" />, мы получим полный поворот манипулятора с учётом всех углов. Формулы вращения вокруг осей системы координат известные и просты(ссылка выше), и представление сложного пространственного движения через последовательные более простые преобразования позволяет упростить задачу.

С учётом вышевыведенных формул, в начальном положении у нас <img src="https://latex.codecogs.com/svg.image?\theta_{1}" title="https://latex.codecogs.com/svg.image?\theta_{1}" /> = 0, а <img src="https://latex.codecogs.com/svg.image?\theta_{2}" title="https://latex.codecogs.com/svg.image?\theta_{2}" /> произвольный, получим:

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}x=L_{1}&space;&plus;&space;L_{2}\cdot&space;\cos(\theta&space;_{2})\\y=L_{2}\cdot&space;\sin(\theta&space;_{2})\\z=0\end{matrix}\right." title="https://latex.codecogs.com/svg.image?\left\{\begin{matrix}x=L_{1} + L_{2}\cdot \cos(\theta _{2})\\y=L_{2}\cdot \sin(\theta _{2})\\z=0\end{matrix}\right." />

Далее мы нашу систему координат, как уже было сказано, поворачиваем вокруг оси X на угол <img src="https://latex.codecogs.com/svg.image?\theta_{3}" title="https://latex.codecogs.com/svg.image?\theta_{3}" />. Тогда с учётом вида матрицы вращения вокруг оси X наше преобразование будет иметь вид:

<img src="https://latex.codecogs.com/svg.image?\begin{bmatrix}x^{'}\\y^{'}\\z^{'}\end{bmatrix}&space;=&space;\begin{bmatrix}1&0&0\\0&cos(&space;\theta&space;_{3}&space;)&-sin(&space;\theta&space;_{3}&space;)\\0&sin(&space;\theta&space;_{3})&cos(&space;\theta&space;_{3}&space;)\end{bmatrix}&space;\begin{bmatrix}x\\y\\z\end{bmatrix}=\begin{bmatrix}1&0&0\\0&cos(&space;\theta&space;_{3}&space;)&-sin(&space;\theta&space;_{3}&space;)\\0&sin(&space;\theta&space;_{3})&cos(&space;\theta&space;_{3}&space;)\end{bmatrix}&space;\begin{bmatrix}L_{1}&space;&plus;&space;L_{2}\cdot&space;\cos(\theta&space;_{2})\\L_{2}\cdot&space;\sin(\theta&space;_{2})\\0\end{bmatrix}" title="https://latex.codecogs.com/svg.image?\begin{bmatrix}x^{'}\\y^{'}\\z^{'}\end{bmatrix} = \begin{bmatrix}1&0&0\\0&cos( \theta _{3} )&-sin( \theta _{3} )\\0&sin( \theta _{3})&cos( \theta _{3} )\end{bmatrix} \begin{bmatrix}x\\y\\z\end{bmatrix}=\begin{bmatrix}1&0&0\\0&cos( \theta _{3} )&-sin( \theta _{3} )\\0&sin( \theta _{3})&cos( \theta _{3} )\end{bmatrix} \begin{bmatrix}L_{1} + L_{2}\cdot \cos(\theta _{2})\\L_{2}\cdot \sin(\theta _{2})\\0\end{bmatrix}" />

Получим:

<img src="https://latex.codecogs.com/svg.image?\begin{bmatrix}x^{'}\\y^{'}\\z^{'}\end{bmatrix}&space;=&space;\begin{bmatrix}L_{1}&space;&plus;&space;L_{2}\cdot&space;\cos(\theta&space;_{2})\\L_{2}\cdot\cos(\theta&space;_{3})\cdot\sin(\theta&space;_{2})\\L_{2}\cdot\sin(\theta&space;_{2})\cdot\sin(\theta&space;_{3})\end{bmatrix}" title="https://latex.codecogs.com/svg.image?\begin{bmatrix}x^{'}\\y^{'}\\z^{'}\end{bmatrix} = \begin{bmatrix}L_{1} + L_{2}\cdot \cos(\theta _{2})\\L_{2}\cdot\cos(\theta _{3})\cdot\sin(\theta _{2})\\L_{2}\cdot\sin(\theta _{2})\cdot\sin(\theta _{3})\end{bmatrix}" />

После поворачиваем вокруг оси Z на угол <img src="https://latex.codecogs.com/svg.image?\theta_{1}" title="https://latex.codecogs.com/svg.image?\theta_{1}" />. Тогда с учётом вида матрицы вращения вокруг оси Z наше преобразование будет иметь вид:

<img src="https://latex.codecogs.com/svg.image?\begin{bmatrix}x^{''}\\y^{''}\\z^{''}\end{bmatrix}&space;=&space;\begin{bmatrix}cos(&space;\theta&space;_{1}&space;)&-sin(&space;\theta&space;_{1}&space;)&0\\sin(&space;\theta&space;_{1})&cos(&space;\theta&space;_{1}&space;)&0\\0&0&1\end{bmatrix}&space;\begin{bmatrix}x^{'}\\y^{'}\\z^{'}\end{bmatrix}=\begin{bmatrix}cos(&space;\theta&space;_{1}&space;)&-sin(&space;\theta&space;_{1}&space;)&0\\sin(&space;\theta&space;_{1})&cos(&space;\theta&space;_{1}&space;)&0\\0&0&1\end{bmatrix}\begin{bmatrix}L_{1}&space;&plus;&space;L_{2}\cdot&space;\cos(\theta&space;_{2})\\L_{2}\cdot\cos(\theta&space;_{3})\cdot\sin(\theta&space;_{2})\\L_{2}\cdot\sin(\theta&space;_{2})\cdot\sin(\theta&space;_{3})\end{bmatrix}" title="https://latex.codecogs.com/svg.image?\begin{bmatrix}x^{''}\\y^{''}\\z^{''}\end{bmatrix} = \begin{bmatrix}cos( \theta _{1} )&-sin( \theta _{1} )&0\\sin( \theta _{1})&cos( \theta _{1} )&0\\0&0&1\end{bmatrix} \begin{bmatrix}x^{'}\\y^{'}\\z^{'}\end{bmatrix}=\begin{bmatrix}cos( \theta _{1} )&-sin( \theta _{1} )&0\\sin( \theta _{1})&cos( \theta _{1} )&0\\0&0&1\end{bmatrix}\begin{bmatrix}L_{1} + L_{2}\cdot \cos(\theta _{2})\\L_{2}\cdot\cos(\theta _{3})\cdot\sin(\theta _{2})\\L_{2}\cdot\sin(\theta _{2})\cdot\sin(\theta _{3})\end{bmatrix}" />

После перемножения получим формулу прямой кинематики, которая приведена в начале.

В силу громоздкости записи и вычислений был использован матлаб-скрипт [Hand_formul.m](Hand_formul.m). Cкрипт выводит все символьные выражения.

Для обратной кинематики:

Для начала упростим задачу. Представим, что звено L1 может двигаться не только в плоскости но и вообще во всём пространстве(относительно точки плеча), тогда все возможные положения конца звена - точки локтя будут описывать сферу с радиусом L1 и центром в точке плеча(в центре системы координат). Далее, мы знаем, что точка хвата должна оказаться в желаемой точке, чьи координаты заданы, при этом точку хвата описывает координаты конца звена L2, которые в свою очередь определяются координатами локтя. Представим, что точка хвата достигла желаемой точки, тогда всё возможные положения точки локтя лежат на сфере радиуса L2 и с центром - желаемой точкой(мысленно поставим точку хвата в желамую точку и покрутим предплечьем(звеном L2) во все стороны). Таким образом положения точки локтя при осуществелении обеих условий(1. начало звена L1 зафиксировано в начале координат, 2. точка хвата лежит в желаемой точке, а точка локтя жёстко связана с ней через звено L2) будет лежать на перечении этих двух сфер. Найдём координаты этих точек, для этого нужно решить систему:

<img src="http://latex.codecogs.com/svg.latex?\left\{\begin{matrix}x^{2}&plus;y^{2}&plus;z^{2}=L_{1}^{2}\\(x-x_{0})^{2}&plus;(y-y_{0})^{2}&plus;(z-z_{0})^{2}=L_{2}^{2}\end{matrix}\right." title="http://latex.codecogs.com/svg.latex?\left\{\begin{matrix}x^{2}+y^{2}+z^{2}=L_{1}^{2}\\(x-x_{0})^{2}+(y-y_{0})^{2}+(z-z_{0})^{2}=L_{2}^{2}\end{matrix}\right." />

где первое уравнение описывает первую сферу, второе - вторую. <img src="http://latex.codecogs.com/svg.latex?x_{0},&space;y_{0},&space;z_{0}" title="http://latex.codecogs.com/svg.latex?x_{0}, y_{0}, z_{0}" /> - координаты желаемой точки.

Раскроем во втором уравнении скобки:

<img src="http://latex.codecogs.com/svg.latex?x^{2}-2xx_{0}&plus;x_{0}^{2}&plus;y^{2}-2yy_{0}&plus;y_{0}^{2}&plus;z^{2}-2zz_{0}&plus;z_{0}^{2}=L_{2}^{2}" title="http://latex.codecogs.com/svg.latex?x^{2}-2xx_{0}+x_{0}^{2}+y^{2}-2yy_{0}+y_{0}^{2}+z^{2}-2zz_{0}+z_{0}^{2}=L_{2}^{2}" />

Вместо суммы квадратов координат можно поставить первое уравнение. Сумму квадратов координат желаемой точки обозначим за d. С учтом подстановок и обозначение перенесём всё влево:

<img src="http://latex.codecogs.com/svg.latex?-2xx_{0}-2yy_{0}-2zz_{0}&space;-&space;L_{2}^{2}&space;&plus;&space;L_{1}^{2}&space;&plus;&space;d=0" title="http://latex.codecogs.com/svg.latex?-2xx_{0}-2yy_{0}-2zz_{0} - L_{2}^{2} + L_{1}^{2} + d=0" />

Обозначим <img src="http://latex.codecogs.com/svg.latex?&space;-&space;L_{2}^{2}&space;&plus;&space;L_{1}^{2}&space;&plus;&space;d" title="http://latex.codecogs.com/svg.latex? - L_{2}^{2} + L_{1}^{2} + d" /> за D. В итоге получим уравнение плоскости вида:

<img src="http://latex.codecogs.com/svg.latex?Ax&space;&plus;&space;By&space;&plus;&space;Cz&space;&plus;&space;D=0" title="http://latex.codecogs.com/svg.latex?Ax + By + Cz + D=0" />,

где <img src="http://latex.codecogs.com/svg.latex?A&space;=&space;-2\cdot&space;x_{0}" title="http://latex.codecogs.com/svg.latex?A = -2\cdot x_{0}" /> , <img src="http://latex.codecogs.com/svg.latex?B&space;=&space;-2\cdot&space;y_{0}" title="http://latex.codecogs.com/svg.latex?B = -2\cdot y_{0}" /> , <img src="http://latex.codecogs.com/svg.latex?C&space;=&space;-2\cdot&space;z_{0}" title="http://latex.codecogs.com/svg.latex?C = -2\cdot z_{0}" /> соответственно.

Вообще пересечением сфер является окружность, но так как сложно описать уравнение окружности, произвольно лежащей в пространстве, мы получили уравнение плоскости, в которой лежит нужная нам окружность. Так как из всей плоксоти нам нужны конкретные точки, а именно лежащие на сфере, мы должны совместно решить уравнение плоскости и уравнение какой-нибудь из сфер(возьмём первое для удобства)(кстати, система из уравнения плоскости и сферы как раз даёт уравнение окружности произвольно ориентированной в пространстве), также вспомним, что мы опустили условие, что звено L1 может двигаться только в плоскости, поэтому сразу добавим третьим уравнением - уравнение плоскости L1, так как этой плоскостью является XY, то её уравнением будет просто z = 0. В итоге получим:

<img src="http://latex.codecogs.com/svg.latex?\left\{\begin{matrix}x^{2}&plus;y^{2}&plus;z^{2}=L_{1}^{2}\\Ax&space;&plus;&space;By&space;&plus;&space;Cz&space;&plus;&space;D=0\\z=0\end{matrix}\right." title="http://latex.codecogs.com/svg.latex?\left\{\begin{matrix}x^{2}+y^{2}+z^{2}=L_{1}^{2}\\Ax + By + Cz + D=0\\z=0\end{matrix}\right." />

Можем сразу подставить z=0 в два другим уравнения и получим:

<img src="http://latex.codecogs.com/svg.latex?\left\{\begin{matrix}x^{2}&plus;y^{2}=L_{1}^{2}\\Ax&space;&plus;&space;By&space;&plus;&space;D=0\end{matrix}\right." title="http://latex.codecogs.com/svg.latex?\left\{\begin{matrix}x^{2}+y^{2}=L_{1}^{2}\\Ax + By + D=0\end{matrix}\right." />

Из второго уравнения выразим x:

<img src="http://latex.codecogs.com/svg.latex?x&space;=&space;\frac{-D-By}{A}" title="http://latex.codecogs.com/svg.latex?x = \frac{-D-By}{A}" />

и подставим это в первое уравнение:

<img src="http://latex.codecogs.com/svg.latex?(\frac{-D-By}{A})^{2}&plus;y^{2}=L_{1}^{2}" title="http://latex.codecogs.com/svg.latex?(\frac{-D-By}{A})^{2}+y^{2}=L_{1}^{2}" />

<img src="https://latex.codecogs.com/svg.image?(\frac{D}{A}&plus;\frac{B}{A}y)^{2}&plus;y^{2}=L_{1}^{2}" title="https://latex.codecogs.com/svg.image?(\frac{D}{A}+\frac{B}{A}y)^{2}+y^{2}=L_{1}^{2}" />

###

<img src="https://latex.codecogs.com/svg.image?(\frac{D}{A})^{2}&plus;2\frac{D}{A}\frac{B}{A}y&plus;(\frac{B}{A}y)^{2}&plus;y^{2}=L_{1}^{2}" title="https://latex.codecogs.com/svg.image?(\frac{D}{A})^{2}+2\frac{D}{A}\frac{B}{A}y+(\frac{B}{A}y)^{2}+y^{2}=L_{1}^{2}" />

###

<img src="https://latex.codecogs.com/svg.image?D^{2}&plus;2DBy&plus;B^{2}y^{2}&plus;A^{2}y^{2}=A^{2}L_{1}^{2}" title="https://latex.codecogs.com/svg.image?D^{2}+2DBy+B^{2}y^{2}+A^{2}y^{2}=A^{2}L_{1}^{2}" />

###

<img src="https://latex.codecogs.com/svg.image?(A^{2}&plus;B^{2})y^{2}&plus;2DBy&plus;(D^{2}-A^{2}L_{1}^{2})=0" title="https://latex.codecogs.com/svg.image?(A^{2}+B^{2})y^{2}+2DBy+(D^{2}-A^{2}L_{1}^{2})=0" />

Отсюда можно найти решение - координату локтя:

<img src="https://latex.codecogs.com/svg.image?y_{m_{1,2}}&space;=&space;\frac{-2DB\pm&space;\sqrt{(2DB)^{2}-4(A^{2}&plus;B^{2})(D^{2}-(AL_{1})^{2})}}{2(A^{2}&plus;B^{2})}" title="https://latex.codecogs.com/svg.image?y_{m_{1,2}} = \frac{-2DB\pm \sqrt{(2DB)^{2}-4(A^{2}+B^{2})(D^{2}-(AL_{1})^{2})}}{2(A^{2}+B^{2})}" />

А по формулам полученным выше можно найти вторую координату:

<img src="https://latex.codecogs.com/svg.image?x_{m_{1,2}}&space;=&space;\frac{-D-By_{m_{1,2}}}{A}" title="https://latex.codecogs.com/svg.image?x_{m_{1,2}} = \frac{-D-By_{m_{1,2}}}{A}" />

или если нужно избежать возможное деление на ноль

 <img src="https://latex.codecogs.com/svg.image?x_{m_{1,2}}&space;=&space;\sqrt{L_{1}^{2}-y_{m_{1,2}}^{2}}" title="https://latex.codecogs.com/svg.image?x_{m_{1,2}} = \sqrt{L_{1}^{2}-y_{m_{1,2}}^{2}}" />

Зная координаты локтя, можно найти угол поворота первого звена, как:

<img src="https://latex.codecogs.com/svg.image?\theta&space;_{1}=\arctan(\frac{y_{m}}{x_{m}})" title="https://latex.codecogs.com/svg.image?\theta _{1}=\arctan(\frac{y_{m}}{x_{m}})" />

Для нахождения угла <img src="https://latex.codecogs.com/svg.image?\theta_{3}" title="https://latex.codecogs.com/svg.image?\theta_{3}" /> вспоним сначала, что это поворот плоскости манипулятора вокруг первого звена, значит нахождения этого угла можно поставить как задачу расчёта угла между плоскостями: исходной(XY) и новой(желаемой), которые имеют общую прямую пересечения(которая проходит через первое звено). Плоскость можно задавать с помощью координат нормали к этой плоскости. Для исходной плоскости это будет единичный вектор сонаправленный с осью Z. Для получения уравнения координат нормали к новой плоскости, построим сначала уравнение самой плоскости. Для этого используем уравнение:

<img src="https://latex.codecogs.com/svg.image?\left|&space;\begin{matrix}x-x_1&y-y_1&z-z_1\\&space;x_2-x_1&y_2-y_1&z_2-z_1\\&space;x_3-x_1&y_3-y_1&z_3-z_1\\&space;\end{matrix}\right|=0." title="https://latex.codecogs.com/svg.image?\left| \begin{matrix}x-x_1&y-y_1&z-z_1\\ x_2-x_1&y_2-y_1&z_2-z_1\\ x_3-x_1&y_3-y_1&z_3-z_1\\ \end{matrix}\right|=0." />

где вертикальные черты означают определитель, <img src="https://latex.codecogs.com/svg.image?x_{1-3},&space;y_{1-3},&space;z_{1-3}" title="https://latex.codecogs.com/svg.image?x_{1-3}, y_{1-3}, z_{1-3}" /> - координаты трёх точек, по которым строится плоскость. В качестве трёх точек возьмём начало координат, координаты локтя, желаемую точку, в итоге получим уравнение желамеой плоскости манипулятора:

<img src="https://latex.codecogs.com/svg.image?z_{0}y_{m}x&space;&plus;&space;(-z_{0}x_{m})y&space;&plus;(-x_{0}y_{m}&plus;x_{m}y_{0})z&space;=&space;0" title="https://latex.codecogs.com/svg.image?z_{0}y_{m}x + (-z_{0}x_{m})y +(-x_{0}y_{m}+x_{m}y_{0})z = 0" />

коэффициенты при переменных - и будут координатами нормали к данной плоскости. Тогда мы можем воспользоваться формулой косинуса угла между пересекающимеся плоскостями по координатам их нормали:

<img src="https://latex.codecogs.com/svg.image?\cos(\alpha&space;)=\frac{\left|(x_{1}x_{2}&plus;y_{1}y_{2}&plus;z_{1}z_{2})\right|}{\sqrt{x_{1}^{2}&plus;y_{1}^{2}&space;&plus;&space;z_{1}^{2}}\sqrt{x_{2}^{2}&plus;y_{2}^{2}&space;&plus;&space;z_{2}^{2}}}" title="https://latex.codecogs.com/svg.image?\cos(\alpha )=\frac{\left|(x_{1}x_{2}+y_{1}y_{2}+z_{1}z_{2})\right|}{\sqrt{x_{1}^{2}+y_{1}^{2} + z_{1}^{2}}\sqrt{x_{2}^{2}+y_{2}^{2} + z_{2}^{2}}}" />

так как нам важен знак(четверть угла), то воспользуемся формулой:

<img src="https://latex.codecogs.com/svg.image?\cos(\alpha&space;)=\frac{(x_{1}x_{2}&plus;y_{1}y_{2}&plus;z_{1}z_{2})}{\sqrt{x_{1}^{2}&plus;y_{1}^{2}&space;&plus;&space;z_{1}^{2}}\sqrt{x_{2}^{2}&plus;y_{2}^{2}&space;&plus;&space;z_{2}^{2}}}" title="https://latex.codecogs.com/svg.image?\cos(\alpha )=\frac{(x_{1}x_{2}+y_{1}y_{2}+z_{1}z_{2})}{\sqrt{x_{1}^{2}+y_{1}^{2} + z_{1}^{2}}\sqrt{x_{2}^{2}+y_{2}^{2} + z_{2}^{2}}}" />

Подставляя координаты наших нормалей получим:

<img src="https://latex.codecogs.com/svg.image?\cos(\theta_{3})=\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}&space;&plus;&space;(x_{0}y_{m}-x_{m}y_{0})^{2}}}" title="https://latex.codecogs.com/svg.image?\cos(\theta_{3})=\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2} + (x_{0}y_{m}-x_{m}y_{0})^{2}}}" />

Из-за громоздкости выражений и расчётов был использован скрипт для символьных выражений [Ang_plosk.m](Ang_plosk.m), который выводит выражения выше. От арккосинуса перейдём к арктангенсу, так как он позволяет сократить выражение, а также имеет специлизированные функции, защищающие от случай деления на ноль. Для этого сделаем преобразование:

<img src="https://latex.codecogs.com/svg.image?\cos(\theta_{3})=\sin(\frac{\pi&space;}{2}-\theta_{3})" title="https://latex.codecogs.com/svg.image?\cos(\theta_{3})=\sin(\frac{\pi }{2}-\theta_{3})" />

Используем выражение:

<img src="https://latex.codecogs.com/svg.image?\sin(\arctan(\alpha&space;))=\frac{\alpha&space;}{\sqrt{1&plus;\alpha&space;^{2}}}" title="https://latex.codecogs.com/svg.image?\sin(\arctan(\alpha ))=\frac{\alpha }{\sqrt{1+\alpha ^{2}}}" />

Для этого сделаем преобразование:

<img src="https://latex.codecogs.com/svg.image?\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}&space;&plus;&space;(x_{0}y_{m}-x_{m}y_{0})^{2}}}=\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}}\sqrt{1&space;&plus;&space;\frac{(x_{0}y_{m}-x_{m}y_{0})^{2}}{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}}}" title="https://latex.codecogs.com/svg.image?\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2} + (x_{0}y_{m}-x_{m}y_{0})^{2}}}=\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2}}\sqrt{1 + \frac{(x_{0}y_{m}-x_{m}y_{0})^{2}}{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2}}}" />

<img src="https://latex.codecogs.com/svg.image?\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}}\sqrt{1&space;&plus;&space;(\frac{(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}}})^{2}}}=\frac{\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}}}}{\sqrt{1&space;&plus;&space;(\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}}})^{2}}}" title="https://latex.codecogs.com/svg.image?\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2}}\sqrt{1 + (\frac{(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2}}})^{2}}}=\frac{\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2}}}}{\sqrt{1 + (\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2}}})^{2}}}" />

минус в одной из скобок знаменателя был добавлен так как дробь стоит под квадратом, а в знаменателе корень, который не меняет знака

С учётом всех вышеперечисленных выражений, получим:

<img src="https://latex.codecogs.com/svg.image?\frac{\pi}{2}-\theta_{3}=\arctan(\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}}})" title="https://latex.codecogs.com/svg.image?\frac{\pi}{2}-\theta_{3}=\arctan(\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2}}})" />

или

<img src="https://latex.codecogs.com/svg.image?\theta_{3}=\frac{\pi}{2}-\arctan(\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}}})" title="https://latex.codecogs.com/svg.image?\theta_{3}=\frac{\pi}{2}-\arctan(\frac{-(x_{0}y_{m}-x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2}}})" />

Для нахождения угла <img src="https://latex.codecogs.com/svg.image?\theta&space;_{2}" title="\theta _{2}" /> достаточно знать, что он всегда лежит в плоскости манипулятора, а значит для его нахождения можно рассмотреть манипулятор как плоскую фигуру. Построим:

<img src="Arm_inv.png">

нужный нам угол составляет с углом <img src="https://latex.codecogs.com/svg.image?\beta&space;" title="\beta " /> 180 градусов. Угол <img src="https://latex.codecogs.com/svg.image?\beta&space;" title="\beta " /> мы можем найти из теоремы косинусов:

<img src="https://latex.codecogs.com/svg.image?r^2&space;=&space;L_{1}^2&space;&plus;&space;L_{2}^2&space;-2\cdot&space;L_{1}&space;\cdot&space;L_{2}&space;\cdot&space;\cos&space;\beta" title="r^2 = L_{1}^2 + L_{2}^2 -2\cdot L_{1} \cdot L_{2} \cdot \cos \beta" />

###
<img src="https://latex.codecogs.com/svg.image?\beta&space;&space;=&space;\arccos(\frac{L_{1}^2&space;&plus;&space;L_{2}^2&space;-&space;r^2}{2\cdot&space;L_{1}&space;\cdot&space;L_{2}})" title="https://latex.codecogs.com/svg.image?\beta = \arccos(\frac{L_{1}^2 + L_{2}^2 - r^2}{2\cdot L_{1} \cdot L_{2}})" />

Тогда с заменой <img src="https://latex.codecogs.com/svg.image?r^2" title="https://latex.codecogs.com/svg.image?r^2" /> на <img src="https://latex.codecogs.com/svg.image?d" title="https://latex.codecogs.com/svg.image?d" /> получим:

<img src="https://latex.codecogs.com/svg.image?\theta_{2}&space;=&space;\pi&space;-&space;\arccos(\frac{L_{1}^2&space;&plus;&space;L_{2}^2&space;-&space;d}{2\cdot&space;L_{1}&space;\cdot&space;L_{2}})" title="\theta_{2} = \pi - \arccos(\frac{L_{1}^2 + L_{2}^2 - d}{2\cdot L_{1} \cdot L_{2}})" />

</details>