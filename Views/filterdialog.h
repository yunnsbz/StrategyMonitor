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

    void setTitleText(QString text);

    /**
     * Sets the minimum and maximum value range for the filter dialog.
     *
     * This function updates the UI labels and double spin boxes with the given range.
     * If useParamForLimit is true, the spin boxes are clamped to the provided min and max values.
     * Otherwise, a default wide range (0 to 10,000,000) is applied to allow unrestricted input.
     * Internal min and max values are stored for later use, and the dialog inputs are initialized accordingly.
     */
    void setRange(double min, double max, bool useParamForLimit = false);

    /**
     *  if pressed mainWindow will tell the viewModels to remove filters
     */
    bool wasClearFilterPressed() const;

private:
    void setInitialValues();

private:
    Ui::FilterDialog *ui;

    bool m_filterCleared = false;
    bool m_filterActive = false;

    double m_minVal = 0;
    double m_maxVal = 0;

    double m_storedMinVal = 0;
    double m_storedMaxVal = 0;
};

#endif // FILTERDIALOG_H
