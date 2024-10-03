#include "pg_principal.h"
#include "./ui_pg_principal.h"

pg_principal::pg_principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pg_principal)
{
    ui->setupUi(this);

    // Verificar a conexão e atualizar o QLabel
    verificarConexao();
}

pg_principal::~pg_principal()
{
    delete ui;
}

void pg_principal::verificarConexao()
{
    if (conexao.conectar()) {
        ui->label->setText("CONECTADO");  // Atualiza o texto do QLabel para "CONECTADO" se conectar com sucesso
    } else {
        ui->label->setText("FALHA NA CONEXÃO");  // Atualiza o texto do QLabel em caso de falha
    }
}
