#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = nullptr);
    ~FilterDialog();

    double minValue() const;
    double maxValue() const;

    void setInfoText(QString text);

    void setRange(double min, double max);
    void setInitialValues(double min, double max);

private:
    Ui::FilterDialog *ui;
};

#endif // FILTERDIALOG_H
