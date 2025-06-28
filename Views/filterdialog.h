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

    bool wasClearFilterPressed() const;

private:
    void setInitialValues();

private:
    Ui::FilterDialog *ui;

    bool m_filterCleared;
    bool m_filterActive;

    double minVal;
    double maxVal;
    double storedMinVal;
    double storedMaxVal;
};

#endif // FILTERDIALOG_H
