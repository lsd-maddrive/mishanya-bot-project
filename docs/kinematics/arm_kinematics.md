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

Обратная кинематика:

Для начала введём несколько обозначений:
<img src="http://latex.codecogs.com/svg.latex?A&space;=&space;-2\cdot&space;x_{0}" title="http://latex.codecogs.com/svg.latex?A = -2\cdot x_{0}" /> , <img src="http://latex.codecogs.com/svg.latex?B&space;=&space;-2\cdot&space;y_{0}" title="http://latex.codecogs.com/svg.latex?B = -2\cdot y_{0}" /> , <img src="http://latex.codecogs.com/svg.latex?C&space;=&space;-2\cdot&space;z_{0}" title="http://latex.codecogs.com/svg.latex?C = -2\cdot z_{0}" /> , <img src="http://latex.codecogs.com/svg.latex?d&space;=&space;x_{0}^{2}&space;&plus;&space;y_{0}^{2}&space;&plus;&space;z_{0}^{2}" title="http://latex.codecogs.com/svg.latex?d = x_{0}^{2} + y_{0}^{2} + z_{0}^{2}" /> , где <img src="http://latex.codecogs.com/svg.latex?x_{0},&space;y_{0},&space;z_{0}" title="http://latex.codecogs.com/svg.latex?x_{0}, y_{0}, z_{0}" /> - координаты желаемой точки.
Далее обозначим:

<img src="http://latex.codecogs.com/svg.latex?D&space;=&space;L_{1}^{2}&space;-&space;L_{2}^{2}&space;&plus;&space;d" title="http://latex.codecogs.com/svg.latex?D = L_{1}^{2} - L_{2}^{2} + d" />

<img src="http://latex.codecogs.com/svg.latex?y_{m_{1,2}}&space;=&space;\frac{-2DB\pm&space;\sqrt{(2DB)^{2}-4(A^{2}&plus;B^{2})(D^{2}-(AL_{1})^{2})}}{2(A^{2}&plus;B^{2})}" title="http://latex.codecogs.com/svg.latex?y_{m_{1,2}} = \frac{-2DB\pm \sqrt{(2DB)^{2}-4(A^{2}+B^{2})(D^{2}-(AL_{1})^{2})}}{2(A^{2}+B^{2})}" />

<img src="http://latex.codecogs.com/svg.latex?x_{m_{1,2}}&space;=&space;\frac{-D-By_{m_{1,2}}}{A}" title="http://latex.codecogs.com/svg.latex?x_{m_{1,2}} = \frac{-D-By_{m_{1,2}}}{A}" />

Окончательно:

<img src="http://latex.codecogs.com/svg.latex?\left\{\begin{matrix}\theta&space;_{1}=\arctan(\frac{y_{m}}{x_{m}})\\\\\theta&space;_{2}=\pi&space;-\arccos(\frac{L_{1}^{2}&plus;L_{2}^{2}-d}{2L_{1}L_{2}})\\\\\theta&space;_{3}=-\pi&space;&plus;&space;\arctan(\frac{(x_{0}y_{m}&plus;x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}&plus;(y_{m}z_{0})^{2}}})\end{matrix}\right." title="http://latex.codecogs.com/svg.latex?\left\{\begin{matrix}\theta _{1}=\arctan(\frac{y_{m}}{x_{m}})\\\\\theta _{2}=\pi -\arccos(\frac{L_{1}^{2}+L_{2}^{2}-d}{2L_{1}L_{2}})\\\\\theta _{3}=-\pi + \arctan(\frac{(x_{0}y_{m}+x_{m}y_{0})}{\sqrt{(x_{m}z_{0})^{2}+(y_{m}z_{0})^{2}}})\end{matrix}\right." />

###
<details>
<summary>Вывод уравнений</summary>

Для прямой кинематики:

Для вывода уравнений прямой кинематики сначала рассмотрим движение в плоскости манипулятора - XY, не рассматривая пока что вращение вокруг плеча.

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

Далее нужно учесть поворот плоскости манипулятора вокруг оси звена L1  на угол <img src="https://latex.codecogs.com/svg.image?\theta_{3}&space;" title="\theta_{3} " />

Для этого используем уравнение матрицы поворота вокруг произвольной оси, взятое [отсюда](https://ru.wikipedia.org/wiki/%D0%9C%D0%B0%D1%82%D1%80%D0%B8%D1%86%D0%B0_%D0%BF%D0%BE%D0%B2%D0%BE%D1%80%D0%BE%D1%82%D0%B0):

<img src="https://latex.codecogs.com/svg.image?M(\hat{\mathbf{v}},\theta)&space;=&space;\begin{pmatrix}&space;&space;&space;\cos&space;\theta&space;&plus;&space;(1&space;-&space;\cos&space;\theta)&space;x^2&space;&&space;(1&space;-&space;\cos&space;\theta)&space;x&space;y&space;-&space;(\sin&space;\theta)&space;z&space;&space;&&space;(1&space;-&space;\cos&space;\theta)&space;x&space;z&space;&plus;&space;(\sin&space;\theta)&space;y&space;&space;\\&space;&space;&space;(1&space;-&space;\cos&space;\theta)&space;y&space;x&space;&plus;&space;(\sin&space;\theta)&space;z&space;&space;&&space;\cos&space;\theta&space;&plus;&space;(1&space;-&space;\cos&space;\theta)&space;y^2&space;&&space;(1&space;-&space;\cos&space;\theta)&space;y&space;z&space;-&space;(\sin&space;\theta)&space;x\\&space;&space;&space;(1&space;-&space;\cos&space;\theta)&space;z&space;x&space;-&space;(\sin&space;\theta)&space;y&space;&&space;(1&space;-&space;\cos&space;\theta)&space;z&space;y&space;&plus;&space;(\sin&space;\theta)&space;x&space;&&space;\cos&space;\theta&space;&plus;&space;(1&space;-&space;\cos&space;\theta)&space;z^2&space;\end{pmatrix}" title="M(\hat{\mathbf{v}},\theta) = \begin{pmatrix} \cos \theta + (1 - \cos \theta) x^2 & (1 - \cos \theta) x y - (\sin \theta) z & (1 - \cos \theta) x z + (\sin \theta) y \\ (1 - \cos \theta) y x + (\sin \theta) z & \cos \theta + (1 - \cos \theta) y^2 & (1 - \cos \theta) y z - (\sin \theta) x\\ (1 - \cos \theta) z x - (\sin \theta) y & (1 - \cos \theta) z y + (\sin \theta) x & \cos \theta + (1 - \cos \theta) z^2 \end{pmatrix}" />

Для задания поворота нам нужно знать единичный вектор поворота <img src="https://latex.codecogs.com/svg.image?\hat{\mathbf{v}}&space;=&space;(x,y,z)" title="\hat{\mathbf{v}} = (x,y,z)" />, который задаёт направление оси, вокруг которой происходит поворот, и угол поворота <img src="https://latex.codecogs.com/svg.image?\theta" title="\theta" />. Углом поворота будет, собственно, угол <img src="https://latex.codecogs.com/svg.image?\theta_{3}&space;" title="\theta_{3} " />. Так как вращение идёт вокруг оси звена L1, единичный вектор будет задаваться аналогично координатам точки а1 относительно точки O(см. выше), но с единичной амплитудой - без домножения на L1(так как присутсвие в формулах величины L1 задаёт именно положение точки а1, так как именно на расстоянии L1 находится точка a1). Координата z оси вращения будет всегда равна 0, так как ось двигается в плоскости. Таким образом:

<img src="https://latex.codecogs.com/svg.image?\hat{\mathbf{v}}&space;=&space;(x,y,z)&space;=&space;(\cos(&space;\theta&space;_{1}),\sin(&space;\theta&space;_{1}),0)" title="\hat{\mathbf{v}} = (x,y,z) = (\cos( \theta _{1}),\sin( \theta _{1}),0)" />

В силу громоздкости записи и вычислений был использован матлаб-скрипт [Hand_formul.m](Hand_formul.m). В нём прописаны символьные выражения и вычисления: для системы уравнений точки хвата в неподвижной плосоксти манипулятора; подстановка в формулу матрицы вращения вокруг произвольной оси на угол <img src="https://latex.codecogs.com/svg.image?\theta_{3}&space;" title="\theta_{3} " /> координат единичного вектора оси L1; умножение полученной матрицы поворота на систему уравнений координат в неподвижной плоскости; автоматическое упрощение полученных символьных выражений. После проделанных действий, скрипт выводит символьное выражение для прямой кинематики, которые обозначены в самом начале.

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



Угол <img src="https://latex.codecogs.com/svg.image?\theta&space;_{2}" title="\theta _{2}" /> составляет с углом <img src="https://latex.codecogs.com/svg.image?\beta_{3}&space;" title="\beta_{3} " /> 180 градусов. Угол <img src="https://latex.codecogs.com/svg.image?\beta_{3}&space;" title="\beta_{3} " /> мы можем также найти из теоремы косинусов:

<img src="https://latex.codecogs.com/svg.image?r^2&space;=&space;L_{1}^2&space;&plus;&space;L_{2}^2&space;-2\cdot&space;L_{1}&space;\cdot&space;L_{2}&space;\cdot&space;\cos&space;\beta_{3}" title="r^2 = L_{1}^2 + L_{2}^2 -2\cdot L_{1} \cdot L_{2} \cdot \cos \beta_{3}" />

Тогда:

<img src="https://latex.codecogs.com/svg.image?\theta_{2}&space;=&space;\pi&space;-&space;\arccos(\frac{L_{1}^2&space;&plus;&space;L_{2}^2&space;-&space;r^2}{2\cdot&space;L_{1}&space;\cdot&space;L_{2}})" title="\theta_{2} = \pi - \arccos(\frac{L_{1}^2 + L_{2}^2 - r^2}{2\cdot L_{1} \cdot L_{2}})" />

При подставновке <img src="https://latex.codecogs.com/svg.image?r&space;=&space;\sqrt{x^{2}&plus;y^{2}}" title="r = \sqrt{x^{2}+y^{2}}" /> получаем уравнения для обратной кинематики.

</details>