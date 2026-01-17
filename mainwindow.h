#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer_cycle;                    // таймер для анимации движения планеты
    int planet_size;                        // размер планеты
    int atmosphere_up_size;                 // увеличение атмосферы
    double speed_planet_rotation;           // скорость вращения планеты
    double planet_rotation = 0;             // счетчик вращения планеты
    double speed_rotation_atmosphere;       // скорость вращения атмосферы
    double atmosphere_rotation;             // вращение атмосферы

    QImage star_background;           // текстура звездное небо (фон)
    QImage planet_texture;            // текстурная карта планеты
    QImage planet_alpha;              // маска смешивания планеты альфа
    QImage planet;                    // сама планета
    QImage planet_shadow;             // планетарная тень
    QImage planet_lights_texture;     // текстура ночных огней городов
    QImage planet_lights_alpha;       // маска альфа смешивания (прозрачность)
    QImage planet_lights;             // итоговый объект ночных городов
    QImage planet_atmosphere_texture; // текстурная карта атмосферы
    QImage planet_atmosphere_alpha;   // маска смешивания атмосферы
    QImage planet_atmosphere;         // объект планетной атмосферы


private:
    Ui::MainWindow *ui;

private slots:
    void paintEvent(QPaintEvent * event); // область для рисования
    void cycle();                         // цикл для анимации
};
#endif // MAINWINDOW_H
