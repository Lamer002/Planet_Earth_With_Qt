#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    speed_planet_rotation = 2.0;
    speed_rotation_atmosphere = 3.0;
    atmosphere_up_size = 6;

    planet_size = 500;

    // загрузка картинки
    star_background.load("D:/QT dev/WorkWithImage2/build/img/star_background.jpg");
    planet_texture.load("D:/QT dev/WorkWithImage2/build/img/planet_texture.png");
    planet_alpha.load("D:/QT dev/WorkWithImage2/build/img/planet_alpha.png");
    planet_shadow.load("D:/QT dev/WorkWithImage2/build/img/planet_shadow.png");
    planet_lights_texture.load("D:/QT dev/WorkWithImage2/build/img/planet_lights_texture.png");
    planet_lights_alpha.load("D:/QT dev/WorkWithImage2/build/img/planet_lights_alpha.png");
    planet_atmosphere_texture.load("D:/QT dev/WorkWithImage2/build/img/planet_atmosphere_texture.png");
    planet_atmosphere_alpha.load("D:/QT dev/WorkWithImage2/build/img/planet_atmosphere_alpha.png");


    //масштабируем до размера планеты
    planet_alpha = planet_alpha.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planet_shadow = planet_shadow.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planet_lights_texture = planet_lights_texture.scaled(planet_texture.width(), planet_texture.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planet_lights_alpha = planet_lights_alpha.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planet_atmosphere_texture = planet_atmosphere_texture.scaled(planet_texture.width(), planet_texture.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    planet_atmosphere_alpha = planet_atmosphere_alpha.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    timer_cycle = new QTimer();
    connect(timer_cycle, SIGNAL(timeout()), this, SLOT(cycle()));
    timer_cycle->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // устанавливаем окно просмотра и подгоняем под размеры frame
    painter.setViewport(ui->screen->geometry().x(), ui->screen->geometry().y(),
                        ui->screen->geometry().width(), ui->screen->geometry().height());

    //Масштабирование приложения
    star_background = star_background.scaled(ui->screen->geometry().width(), ui->screen->geometry().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    //отображаем изображение
    painter.drawImage(0, 0, star_background);   //фон звездное небо
    painter.save();                             //сохраняем сцену

    //выставляем текстуру в центр (при этом рисуем координаты не 0, 0 в painter.drawImage, а -planet_size/2, -planet_size/2)
    painter.translate(ui->screen->geometry().width()/2, ui->screen->geometry().height()/2);
    painter.drawImage(-planet_size/2, -planet_size/2, planet);
    painter.drawImage(-(planet_size + atmosphere_up_size)/2, -(planet_size + atmosphere_up_size)/2, planet_atmosphere);    //планета текстура
    painter.drawImage(-planet_size/2, -planet_size/2, planet_shadow);
    painter.drawImage(-planet_size/2, -planet_size/2, planet_lights);

}

void MainWindow::cycle()
{
    //в planet записываем квадрат текстуры который равен высоте самой текстуры (высота и ширина квдрата = высоте текстуры)
    planet = planet_texture.copy(planet_rotation, 0, planet_texture.height(), planet_texture.height());
    //Масштабируем тектуру вращающейся планеты по координатам
    planet = planet.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    //ночные огни городов
    planet_lights = planet_lights_texture.copy(planet_rotation, 0, planet_lights_texture.height(), planet_lights_texture.height());
    planet_lights = planet_lights.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    planet_atmosphere = planet_atmosphere_texture.copy(atmosphere_rotation, 0, planet_atmosphere_texture.height(), planet_atmosphere_texture.height());
    planet_atmosphere = planet_atmosphere.scaled(planet_size, planet_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    //Рисовальщик чтобы рисовать на картинке планеты
    QPainter painter(&planet);
    //настройка смешения альфаканала
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    //рисуем
    painter.drawImage(0, 0, planet_alpha);

    //альфа канал для ночных огней рисовальщик 2
    QPainter painter2(&planet_lights);
    painter2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter2.drawImage(0, 0, planet_lights_alpha);

    QPainter painter3(&planet_atmosphere);
    painter3.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter3.drawImage(0, 0, planet_atmosphere_alpha);

    //вращение планеты
    planet_rotation += speed_planet_rotation;
    //проверка на сколько повернулась текстура, если много, вернуть все обратно
    if (planet_rotation + planet_texture.height() >= planet_texture.width()) planet_rotation = 0;

    atmosphere_rotation += speed_rotation_atmosphere;
    if(atmosphere_rotation + planet_atmosphere_texture.height() >= planet_atmosphere_texture.width()) atmosphere_rotation = 0;


    update();
}
