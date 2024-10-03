#ifndef PG_PRINCIPAL_H
#define PG_PRINCIPAL_H

#include <QMainWindow>
#include <QDateTime>
#include <QTableWidget>

#include "Conexao.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class pg_principal;
}
QT_END_NAMESPACE

class pg_principal : public QMainWindow
{
    Q_OBJECT

public:
    pg_principal(QWidget *parent = nullptr);
    ~pg_principal();
    static void limpar_tabela(QTableWidget *tw);

private slots:
    void on_btn_filtrar_clicked();

private:
    Ui::pg_principal *ui;
    Conexao conexao;  // Instância da classe Conexao para gerenciar a conexão ao banco de dados
    void verificarConexao();  // Método para verificar a conexão e atualizar o QLabel]
    void tabela_notas();
};
#endif // PG_PRINCIPAL_H
