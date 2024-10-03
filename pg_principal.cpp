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

