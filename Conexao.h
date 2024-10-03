#ifndef CONEXAO_H
#define CONEXAO_H

#include <QtSql>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>
#include <QSqlDatabase>

class Conexao {
public:
    QSqlDatabase banco_db;
    QString host;
    QString database;
    QString user;
    QString password;
    int port;

    Conexao() {
        // Definir parâmetros de conexão com PostgreSQL
        host = "localhost";       // Nome do container PostgreSQL dentro da rede Docker
        database = "postgres";      // Nome do banco de dados padrão (pode ser alterado se necessário)
        user = "postgres";          // Usuário padrão do PostgreSQL
        password = "postgres";      // Senha definida ao criar o container
        port = 5433;                // Porta interna do PostgreSQL (não a porta mapeada)

        // Adiciona o driver do PostgreSQL
        banco_db = QSqlDatabase::addDatabase("QPSQL");
    }

    bool conectar(){
        banco_db.setHostName(host);           // Definir o host
        banco_db.setDatabaseName(database);   // Nome do banco de dados
        banco_db.setUserName(user);           // Nome do usuário
        banco_db.setPassword(password);       // Senha do usuário
        banco_db.setPort(port);               // Porta do PostgreSQL

        // Tenta abrir a conexão
        if(!banco_db.open())
        {
            qDebug() << "Erro ao conectar ao banco de dados PostgreSQL: " << banco_db.lastError().text();
            return false;
        }
        else{
            qDebug() << "Conexão com banco de dados PostgreSQL bem-sucedida!";
            return true;
        }
    }

    void desconectar(){
        banco_db.close();
        qDebug() << "Conexão com o banco de dados foi fechada.";
    }

    bool verifica_conexao(){
        if(banco_db.isOpen())
        {
            return true;
        }
        else{
            return false;
        }
    }
};

#endif // CONEXAO_H
