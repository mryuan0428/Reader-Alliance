#ifndef RA_ACTIVITY_H
#define RA_ACTIVITY_H

#include <QDialog>

namespace Ui {
class RA_Activity;
}

class RA_Activity : public QDialog
{
    Q_OBJECT

public:
    explicit RA_Activity(QWidget *parent = 0);
    ~RA_Activity();

private:
    Ui::RA_Activity *ui;
};

#endif // RA_ACTIVITY_H
