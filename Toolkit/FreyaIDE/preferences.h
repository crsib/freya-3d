#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QtGui/QDialog>

namespace Ui {
    class Preferences;
}

class Preferences : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(Preferences)
public:
    explicit Preferences(QWidget *parent = 0);
    virtual ~Preferences();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Preferences *m_ui;

private slots:
    void on_btnOpenProjTopDirLoc_clicked();
};

#endif // PREFERENCES_H
