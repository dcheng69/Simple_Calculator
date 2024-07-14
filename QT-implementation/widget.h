#ifndef WIDGET_H
#define WIDGET_H

#include "button.h"
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QStateMachine>
#include <QStack>

namespace Ui {
    class Widget;
}

typedef enum {
    Plus = 0,
    Minus,
    Multiply,
    Division,
    OpenBracket,
    CloseBreaket
} operationType;

typedef enum {
    stateClear = 0,
    stateOperand,
    stateOperator,
    stateError,
    stateOpenBracket,
    stateCloseBracket,
    stateChangeSign
} stateType;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void buttonClicked();
    void digitClicked();
    void plusClicked();
    void minusClick();
    void multiplyClicked();
    void divisionClicked();
    void openBracketClicked();
    void closeBracketClicked();
    void changeSignClicked();
    void clearClicked();
    void equalClicked();

private:
    enum {
        numDigitButtons = 10,
    };
    template<typename PointerToMemberFunction>
    Button *createButton(const QString &text, const PointerToMemberFunction &member);
    void clearCalculator();

    // layout and display
    QGridLayout *mainLayout;
    QLineEdit *display;
    // digit buttons
    Button *digitButtons[numDigitButtons];
    // intitialize the operator buttons
    Button *plusButton;
    Button *minusButton;
    Button *multiplyButton;
    Button *divisionButton;

    // initialize the bracket buttons
    Button *openBracketButton;
    Button *closeBracketButton;

    // initialize other function buttons
    Button *clearButton;
    Button *changeSignButton;
    Button *equalSignButton;

    // calculator variables
    double m_result;
    double m_operand;
    operationType m_operator;
    QStack<double> operand_stk;
    QStack<operationType> operator_stk;

    // state variable
    stateType m_state;
};

#endif // WIDGET_H
