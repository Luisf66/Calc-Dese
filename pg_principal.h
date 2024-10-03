#ifndef PG_PRINCIPAL_H
#define PG_PRINCIPAL_H

#include <QMainWindow>

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

private:
    Ui::pg_principal *ui;
};
#endif // PG_PRINCIPAL_H
