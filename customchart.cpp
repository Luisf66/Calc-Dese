#include "customchart.h"
#include <QPainter>
#include <QPaintEvent>

CustomChart::CustomChart(QWidget *parent)
    : QWidget(parent)
{
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
    int leftMargin = 50;
    int bottomMargin = 50;
    int barWidth = 40;
    int spacing = 30;
    int maxBarHeight = height() - bottomMargin - 20;

    // Calcular o valor máximo dos dados para ajustar a escala do gráfico
    double maxValue = *std::max_element(data.begin(), data.end());

    // Calcular as posições das barras e desenhar cada uma
    int currentX = leftMargin;

    for (int i = 0; i < data.size(); ++i) {
        double value = data[i];
        int barHeight = static_cast<int>((value / maxValue) * maxBarHeight);

        // Configuração da cor da barra
        QColor color = Qt::blue;
        painter.setBrush(color);

        // Desenha a barra
        painter.drawRect(currentX, height() - bottomMargin - barHeight, barWidth, barHeight);

        // Desenhar o rótulo da barra abaixo dela
        painter.drawText(currentX, height() - bottomMargin + 15, labels[i]);

        // Atualiza a posição X para a próxima barra
        currentX += barWidth + spacing;
    }

    // Desenhar os eixos
    painter.drawLine(leftMargin, height() - bottomMargin, width(), height() - bottomMargin); // Eixo X
    painter.drawLine(leftMargin, height() - bottomMargin, leftMargin, 20); // Eixo Y
}
