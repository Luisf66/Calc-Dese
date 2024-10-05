#include "customchart.h"
#include <QPainter>
#include <QPaintEvent>

CustomChart::CustomChart(QWidget *parent)
    : QWidget(parent)
{
}

void CustomChart::setData(const QVector<QString> &labels, const QVector<QVector<double>> &data)
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
    int leftMargin = 50;
    int bottomMargin = 50;
    int barWidth = 30;
    int spacing = 20;
    int maxBarHeight = height() - bottomMargin - 20;

    // Calcular o valor máximo das notas para ajustar a escala do gráfico
    double maxValue = 10.0; // Supõe-se que a nota máxima seja 10

    // Calcular as posições das barras
    int numGroups = data.size();
    int numBarsPerGroup = data.isEmpty() ? 0 : data[0].size();

    int currentX = leftMargin;

    for (int i = 0; i < numGroups; ++i) {
        for (int j = 0; j < numBarsPerGroup; ++j) {
            double value = data[i][j];
            int barHeight = static_cast<int>((value / maxValue) * maxBarHeight);

            // Configuração de cor para cada barra
            QColor color;
            if (j == 0) color = Qt::red;    // Nota 1
            else if (j == 1) color = Qt::green; // Nota 2
            else if (j == 2) color = Qt::blue;  // Nota 3

            painter.setBrush(color);
            painter.drawRect(currentX, height() - bottomMargin - barHeight, barWidth, barHeight);

            currentX += barWidth + spacing;
        }

        // Desenhar o rótulo da disciplina abaixo do grupo de barras
        painter.drawText(currentX - (numBarsPerGroup * (barWidth + spacing)) / 2, height() - 10, labels[i]);

        // Espaço adicional entre grupos
        currentX += spacing * 2;
    }

    // Desenhar os eixos
    painter.drawLine(leftMargin, height() - bottomMargin, width(), height() - bottomMargin); // Eixo X
    painter.drawLine(leftMargin, height() - bottomMargin, leftMargin, 20); // Eixo Y
}
