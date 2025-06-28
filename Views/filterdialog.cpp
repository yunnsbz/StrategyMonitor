#include "filterdialog.h"
#include "ui_filterdialog.h"

#include <QPushButton>
#include <QDialogButtonBox>

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &QDialog::accept);
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
    ui->doubleSpinBox_min->setMinimum(min);
    ui->doubleSpinBox_min->setMaximum(max);
    ui->doubleSpinBox_max->setMinimum(min);
    ui->doubleSpinBox_max->setMaximum(max);
}

void FilterDialog::setInitialValues(double min, double max) {
    ui->doubleSpinBox_min->setValue(min);
    ui->doubleSpinBox_max->setValue(max);
}
