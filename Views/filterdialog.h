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

    void setRange(double min, double max, bool useParamForLimit = false);

    bool wasClearFilterPressed() const;

private:
    void setInitialValues();

private:
    Ui::FilterDialog *ui;

    bool m_filterCleared = false;
    bool m_filterActive = false;

    double minVal = 0;
    double maxVal = 0;
    double storedMinVal = 0;
    double storedMaxVal = 0;
};

#endif // FILTERDIALOG_H
