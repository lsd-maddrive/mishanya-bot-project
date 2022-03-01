# Mishanya bot gazebo model

## Запуск модели 

1. Клонировать репо с помощью git clone --recursive https://github.com/lsd-maddrive/mishanya-bot-project.git (to fetch submodules)

2. Собрать пакет используя catkin_make 

3. Запустить модель roslaunch mishanya_description mishanya.launch

4. Управление с клавиатуры: 
- Установить пакет https://github.com/YugAjmera/teleop_keyboard_omni3 (Описание по установке в readme файле репо). Могут возникнуть проблемы с отступами в скрипте после клонирования (а так как код написан на python это критично), в этом случае нужно поправить табуляцию. 
- Запуск roslaunch mishanya_description twist_key.launch

<!-- 6. Получение карты
    - Запуск лаунч файла: roslaunch esaul_description gmap.launch
    - Сохранение карты: rosrun map_server map_saver -f test-1 (test-1 - имя сохранения файла)          --> 
 

## Полезные ссылки 

### Курсы
1. https://github.com/KaiL4eK/ros_course/tree/master/Topics

### Описание робота (модель, физика)
1. [omni-wheels model](https://github.com/GuiRitter/OpenBase)

2. [omni-wheels twist-key](https://github.com/YugAjmera/teleop_keyboard_omni3)

3. [link element in URDF](http://wiki.ros.org/urdf/XML/link)

4. [joint element in URDF](http://wiki.ros.org/urdf/XML/joint)

5. [zaWRka](https://github.com/lsd-maddrive/zaWRka-project/blob/1c5fed5e65bdc573844c7fcaa0568ca798f53ab2/wr8_description/urdf/model.urdf.xacro#L65)

6. [ROS plugin](http://gazebosim.org/tutorials/?tut=ros_plugins)

7. [Building a world in gazebo](http://gazebosim.org/tutorials?tut=build_world)

8. [Using roslaunch to start Gazebo, world files and URDF models](http://gazebosim.org/tutorials?tut=ros_roslaunch)

9. https://www.youtube.com/channel/UCt6Lag-vv25fTX3e11mVY1Q

