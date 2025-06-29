#include "filterdialog.h"
#include "ui_filterdialog.h"

#include <QPushButton>
#include <QDialogButtonBox>

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);

    // apply
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, [this](){
        if(ui->doubleSpinBoxMin->value() <= ui->doubleSpinBoxMax->value()){
            m_filterCleared = false;
            m_filterActive = true;
            m_storedMinVal = ui->doubleSpinBoxMin->value();
            m_storedMaxVal = ui->doubleSpinBoxMax->value();
            accept();
        }
        else {
            reject();
        }
    });

    // clear filter
    connect(ui->buttonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, [this]() {
        m_filterCleared = true;
        m_filterActive = false;
        accept();
    });

    // cancel
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &QDialog::reject);
}

FilterDialog::~FilterDialog()
{
    delete ui;
}


double FilterDialog::minValue() const {
    return ui->doubleSpinBoxMin->value();
}

double FilterDialog::maxValue() const {
    return ui->doubleSpinBoxMax->value();
}

void FilterDialog::setTitleText(QString text)
{
    setWindowTitle(text);
}

void FilterDialog::setRange(double min, double max, bool useParamForLimit)
{
    ui->labelMinVal->setText(QString("Min Value: %1").arg(min));
    ui->labelMaxVal->setText(QString("Max Value: %1").arg(max));

    if(useParamForLimit){
        ui->doubleSpinBoxMin->setMinimum(min);
        ui->doubleSpinBoxMin->setMaximum(max);

        ui->doubleSpinBoxMax->setMinimum(min);
        ui->doubleSpinBoxMax->setMaximum(max);
    }
    else{
        ui->doubleSpinBoxMin->setMinimum(0);
        ui->doubleSpinBoxMin->setMaximum(10'000'000);

        ui->doubleSpinBoxMax->setMinimum(0);
        ui->doubleSpinBoxMax->setMaximum(10'000'000);
    }

    m_minVal = min;
    m_maxVal = max;

    setInitialValues();
}

bool FilterDialog::wasClearFilterPressed() const
{
    return m_filterCleared;
}

void FilterDialog::setInitialValues()
{
    // stored value will be used if previously user choosed to apply filter.
    if (m_filterActive) {
        ui->doubleSpinBoxMin->setValue(m_storedMinVal);
        ui->doubleSpinBoxMax->setValue(m_storedMaxVal);
    } else {
        ui->doubleSpinBoxMin->setValue(m_minVal);
        ui->doubleSpinBoxMax->setValue(m_maxVal);
    }
}
