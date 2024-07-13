#ifndef WIDGET_H
#define WIDGET_H

#include "button.h"
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void buttonClicked();

private:
    enum {
        numDigitButtons = 10,
    };
    template<typename PointerToMemberFunction>
    Button *createButton(const QString &text, const PointerToMemberFunction &member);
    QGridLayout *mainLayout;
    QLineEdit *display;
    Button *digitButtons[numDigitButtons];
};

#endif // WIDGET_H
