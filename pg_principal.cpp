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
    QString busca = "SELECT * FROM disciplina ORDER BY periodo DESC";
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
        conexao.desconectar();
    }
    else{
        QMessageBox::critical(this,"Falha na Consulta","Não foi possível exibir as notas");
    }

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
    }
}
