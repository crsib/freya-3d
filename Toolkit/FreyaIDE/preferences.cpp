#include "preferences.h"
#include "ui_preferences.h"

#include <QtGui>

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Preferences)
{
    m_ui->setupUi(this);
}

Preferences::~Preferences()
{
    delete m_ui;
}

void Preferences::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Preferences::on_btnOpenProjTopDirLoc_clicked()
{
    QString     addr = QFileDialog::getExistingDirectory(this,tr("Please select the projects top directory"));
    QSettings   settings;
    settings.setValue("pathes/ProjectTop",addr);
    m_ui->edtProjTopDir->setText(addr);
    m_ui->edtFrmWrkInclude->setText("Framework/Include");
    m_ui->edtFrmWrkInclude->setText("Framework/Source");
}
