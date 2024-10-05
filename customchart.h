#ifndef CUSTOMCHART_H
#define CUSTOMCHART_H

#include <QWidget>
#include <QVector>

class CustomChart : public QWidget
{
    Q_OBJECT

public:
    explicit CustomChart(QWidget *parent = nullptr);

    void setData(const QVector<QString> &labels, const QVector<double> &data);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QString> labels; // Armazena os rótulos (nomes dos períodos)
    QVector<double> data;    // Armazena os dados (médias)
};

#endif // CUSTOMCHART_H
