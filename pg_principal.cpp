#include "pg_principal.h"
#include "./ui_pg_principal.h"

#include <QDebug>

pg_principal::pg_principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pg_principal)
{
    ui->setupUi(this);

    // Verificar a conexão e atualizar o QLabel
    verificarConexao();

    tabela_notas();

    ui->statusbar->addWidget(ui->conexao_status);

}

pg_principal::~pg_principal()
{
    delete ui;
}

void pg_principal::verificarConexao()
{
    if (conexao.conectar()) {
        ui->conexao_status->setText("Você está conectado");  // Atualiza o texto do QLabel para "CONECTADO" se conectar com sucesso
    } else {
        ui->conexao_status->setText("FALHA NA CONEXÃO");  // Atualiza o texto do QLabel em caso de falha
        conexao.conectar();
    }
}

void pg_principal::tabela_notas()
{
    // configuração da tabela
    ui->tabela_notas->horizontalHeader()->setVisible(true);
    ui->tabela_notas->setColumnCount(6);
    QStringList cabecalho = {"Disciplina", "Nota 1", "Nota 2", "Nota 3", "Resultado", "Periodo"};
    ui->tabela_notas->setHorizontalHeaderLabels(cabecalho);
    ui->tabela_notas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tabela_notas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tabela_notas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabela_notas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // query
    int nlinhas = 0;
    // parametros de busca
    QString busca = "SELECT * FROM disciplina ";
    QString crescente = "ORDER BY periodo DESC";
    if(ui->rb_1->isChecked())
    {
        busca = busca + "WHERE periodo = 1";
    }
    else if(ui->rb_2->isChecked())
    {
        busca = busca + "WHERE periodo = 2";
    }
    else if(ui->rb_3->isChecked())
    {
        busca = busca + "WHERE periodo = 3";
    }
    else if(ui->rb_4->isChecked())
    {
        busca = busca + "WHERE periodo = 4";
    }
    else if(ui->rb_5->isChecked())
    {
        busca = busca + "WHERE periodo = 5";
    }
    else if(ui->rb_6->isChecked())
    {
        busca = busca + "WHERE periodo = 6";
    }
    else{
        busca = busca + crescente;
    }
    qDebug() << "Busca:" << busca;
    QSqlQuery query;
    query.prepare(busca);
    if(query.exec())
    {
        query.first();
        do
        {
            ui->tabela_notas->insertRow(nlinhas);
            ui->tabela_notas->setItem(nlinhas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tabela_notas->setItem(nlinhas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tabela_notas->setItem(nlinhas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tabela_notas->setItem(nlinhas,3,new QTableWidgetItem(query.value(3).toString()));
            ui->tabela_notas->setItem(nlinhas,4,new QTableWidgetItem(query.value(4).toString()));
            ui->tabela_notas->setItem(nlinhas,5,new QTableWidgetItem(query.value(5).toString()));
        }while(query.next());
        //conexao.desconectar();
    }
    else{
        QMessageBox::critical(this,"Falha na Consulta","Não foi possível exibir as notas");
    }
}

void pg_principal::limpar_tabela(QTableWidget *tw)
{
    while(tw->rowCount() > 0)
    {
        tw->removeRow(0);
    }
}

void pg_principal::on_btn_filtrar_clicked()
{
    limpar_tabela(ui->tabela_notas);
    tabela_notas();
}

void pg_principal::exibirGraficoNotas()
{
    // Coletar os dados do banco de dados
    QString busca = "SELECT id, resultado, periodo FROM disciplina";
    QSqlQuery query;
    query.prepare(busca);

    if (!query.exec()) {
        QMessageBox::critical(this, "Falha na Consulta", "Não foi possível obter os dados para o gráfico");
        return;
    }

    // Mapa para armazenar a soma dos resultados e a contagem por período
    QMap<int, double> somaResultadosPorPeriodo;
    QMap<int, int> contagemPorPeriodo;

    // Processar os resultados do banco de dados
    while (query.next()) {
        int periodo = query.value(2).toInt();  // Obtém o valor do período
        double resultado = query.value(1).toDouble();  // Obtém o valor do resultado

        // Acumula a soma dos resultados por período
        if (somaResultadosPorPeriodo.contains(periodo)) {
            somaResultadosPorPeriodo[periodo] += resultado;
            contagemPorPeriodo[periodo] += 1;  // Incrementa a contagem de disciplinas para o período
        } else {
            somaResultadosPorPeriodo[periodo] = resultado;
            contagemPorPeriodo[periodo] = 1;  // Inicializa a contagem de disciplinas para o período
        }
    }

    // Preparar os dados para o gráfico
    QVector<QString> periodos;
    QVector<double> mediasPorPeriodo;

    // Calcular a média dos resultados por período
    for (auto it = somaResultadosPorPeriodo.constBegin(); it != somaResultadosPorPeriodo.constEnd(); ++it) {
        int periodo = it.key();
        double somaResultados = it.value();
        int contagem = contagemPorPeriodo.value(periodo);

        // Calcula a média dos resultados para o período
        double media = somaResultados / contagem;

        // Armazena o período e a média
        periodos.append("Período " + QString::number(periodo));
        mediasPorPeriodo.append(media);

        // Debug para verificar o cálculo da média
        qDebug() << "Período:" << periodo << "Média dos Resultados:" << media;
    }

    // Criar o widget gráfico
    CustomChart *grafico = new CustomChart();
    grafico->setData(periodos, mediasPorPeriodo); // Passar os rótulos dos períodos e os valores médios

    // Limpar o conteúdo da aba `tab_2` antes de adicionar o novo gráfico
    if (ui->tab_2->layout() != nullptr) {
        QLayoutItem *item;
        while ((item = ui->tab_2->layout()->takeAt(0)) != nullptr) {
            delete item->widget(); // Apaga o widget (o gráfico antigo)
            delete item;           // Apaga o item do layout
        }
        delete ui->tab_2->layout();
    }

    // Configurar o layout para a `tab_2` e adicionar o gráfico
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(grafico);
    ui->tab_2->setLayout(layout);
}



void pg_principal::on_tabWidget_currentChanged(int index)
{
    if(index == 2)
    {
        qDebug() << "Segunda guia";

    }
}


void pg_principal::on_btn_grafico_clicked()
{
    exibirGraficoNotas();
}

