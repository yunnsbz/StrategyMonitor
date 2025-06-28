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
        if(ui->doubleSpinBox_min->value() <= ui->doubleSpinBox_max->value()){
        m_filterActive = true;
        m_filterCleared = false;
        accept();
        storedMinVal = minVal;
        storedMaxVal = maxVal;
        }
        else reject();
    });

    // filtre sıfırlama:
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
    return ui->doubleSpinBox_min->value();
}

double FilterDialog::maxValue() const {
    return ui->doubleSpinBox_max->value();
}

void FilterDialog::setInfoText(QString text)
{
    ui->label_info->setText(text);
}

void FilterDialog::setRange(double min, double max) {
    ui->label_minVal->setText(QString("Min Value: %1").arg(min));
    ui->label_maxVal->setText(QString("Max Value: %1").arg(max));

    ui->doubleSpinBox_min->setMinimum(0);
    ui->doubleSpinBox_min->setMaximum(10'000'000);

    ui->doubleSpinBox_max->setMinimum(0);
    ui->doubleSpinBox_max->setMaximum(10'000'000);

    minVal = min;
    maxVal = max;

    setInitialValues();
}

bool FilterDialog::wasClearFilterPressed() const
{
    return m_filterCleared;
}

void FilterDialog::setInitialValues() {
    if(m_filterActive){
        ui->doubleSpinBox_min->setValue(storedMinVal);
        ui->doubleSpinBox_max->setValue(storedMaxVal);
    }
    else{
        ui->doubleSpinBox_min->setValue(minVal);
        ui->doubleSpinBox_max->setValue(maxVal);
    }
}
