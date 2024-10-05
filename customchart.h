#ifndef CUSTOMCHART_H
#define CUSTOMCHART_H

#include <QWidget>
#include <QVector>

class CustomChart : public QWidget
{
    Q_OBJECT

public:
    explicit CustomChart(QWidget *parent = nullptr);

    void setData(const QVector<QString> &labels, const QVector<QVector<double>> &data);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QString> labels; // Disciplinas
    QVector<QVector<double>> data; // Notas (conjunto de dados)
};

#endif // CUSTOMCHART_H
