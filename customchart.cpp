#include "customchart.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPen>

CustomChart::CustomChart(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(800, 600);  // Define um tamanho mínimo para o gráfico
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CustomChart::setData(const QVector<QString> &labels, const QVector<double> &data)
{
    this->labels = labels;
    this->data = data;
    update(); // Solicita a atualização do widget para desenhar o gráfico
}

void CustomChart::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Configurações de dimensão do gráfico
    int leftMargin = 60;
    int bottomMargin = 60;
    int pointRadius = 5;
    int maxGraphHeight = height() - bottomMargin - 40;
    int maxGraphWidth = width() - leftMargin - 40;

    // Calcular o valor máximo dos dados para ajustar a escala do gráfico
    double maxValue = 10.0; // Valor máximo fixo para o eixo Y (0 a 10)

    // Calcular as posições dos pontos
    int numPoints = data.size();
    if (numPoints < 2) return; // Verifica se há pontos suficientes para um gráfico de linha

    double xSpacing = static_cast<double>(maxGraphWidth) / (numPoints - 1);
    QVector<QPointF> points;

    for (int i = 0; i < numPoints; ++i) {
        double value = data[i];
        int x = leftMargin + static_cast<int>(i * xSpacing);
        int y = height() - bottomMargin - static_cast<int>((value / maxValue) * maxGraphHeight);
        points.append(QPointF(x, y));
    }

    // Desenhar as linhas que conectam os pontos
    QPen linePen(Qt::black, 2);
    painter.setPen(linePen);

    for (int i = 0; i < points.size() - 1; ++i) {
        painter.drawLine(points[i], points[i + 1]);
    }

    // Desenhar os pontos no gráfico
    QPen pointPen(Qt::red);
    painter.setPen(pointPen);
    painter.setBrush(Qt::red);

    for (const QPointF &point : points) {
        painter.drawEllipse(point, pointRadius, pointRadius);
    }

    // Desenhar os rótulos no eixo X
    painter.setPen(Qt::black);
    for (int i = 0; i < labels.size(); ++i) {
        int x = leftMargin + static_cast<int>(i * xSpacing);
        painter.drawText(x - 20, height() - bottomMargin + 30, labels[i]); // Reposiciona o rótulo para evitar ser cortado
    }

    // Desenhar os eixos
    QPen axisPen(Qt::black, 1);
    painter.setPen(axisPen);
    painter.drawLine(leftMargin, height() - bottomMargin, width() - 20, height() - bottomMargin); // Eixo X
    painter.drawLine(leftMargin, height() - bottomMargin, leftMargin, 20); // Eixo Y

    // Desenhar a escala do eixo Y (0 a 10)
    int numTicks = 11; // De 0 a 10, com incremento de 1
    double ySpacing = static_cast<double>(maxGraphHeight) / (numTicks - 1);
    for (int i = 0; i < numTicks; ++i) {
        int y = height() - bottomMargin - static_cast<int>(i * ySpacing);
        painter.drawLine(leftMargin - 5, y, leftMargin, y); // Marca no eixo Y
        painter.drawText(leftMargin - 30, y + 5, QString::number(i)); // Texto da escala (0, 1, 2, ..., 10)
    }
}
