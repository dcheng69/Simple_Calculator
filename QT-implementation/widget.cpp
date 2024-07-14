#include "widget.h"
#include <QState>
#include <QSignalTransition>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    // initialize the display line object
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    // Adjust the font size
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 10);
    display->setFont(font);

    // initialize the digit buttons
    for (int i = 0; i < numDigitButtons; ++i)
        digitButtons[i] = createButton(QString::number(i), &Widget::digitClicked);

    // intitialize the operator buttons
    plusButton = createButton(tr("+"), &Widget::plusClicked);
    minusButton = createButton(tr("-"), &Widget::minusClick);
    multiplyButton = createButton(tr("*"), &Widget::multiplyClicked);
    divisionButton = createButton(tr("/"), &Widget::divisionClicked);

    // initialize the bracket buttons
    openBracketButton = createButton(tr("("), &Widget::openBracketClicked);
    closeBracketButton = createButton(tr(")"), &Widget::closeBracketClicked);

    // initialize other function buttons
    clearButton = createButton(tr("C"), &Widget::clearClicked);
    changeSignButton = createButton(tr("-X"), &Widget::changeSignClicked);
    equalSignButton = createButton(tr("="), &Widget::equalClicked);

    // arrange the layout of the calculator
    mainLayout = new QGridLayout;
    // set size of the layout
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    // add previously initialzed widgets to the layout
    // row - 0
    mainLayout->addWidget(display, 0, 0, 1, 4);
    // row - 1
    mainLayout->addWidget(digitButtons[7], 1, 0);
    mainLayout->addWidget(digitButtons[8], 1, 1);
    mainLayout->addWidget(digitButtons[9], 1, 2);
    mainLayout->addWidget(plusButton, 1, 3);
    // row - 2
    mainLayout->addWidget(digitButtons[4], 2, 0);
    mainLayout->addWidget(digitButtons[5], 2, 1);
    mainLayout->addWidget(digitButtons[6], 2, 2);
    mainLayout->addWidget(minusButton, 2, 3);
    // row - 3
    mainLayout->addWidget(digitButtons[1], 3, 0);
    mainLayout->addWidget(digitButtons[2], 3, 1);
    mainLayout->addWidget(digitButtons[3], 3, 2);
    mainLayout->addWidget(multiplyButton, 3, 3);
    // row - 4
    mainLayout->addWidget(digitButtons[0], 4, 0);
    mainLayout->addWidget(openBracketButton, 4, 1);
    mainLayout->addWidget(closeBracketButton, 4, 2);
    mainLayout->addWidget(divisionButton, 4, 3);
    // row - 5
    mainLayout->addWidget(clearButton, 5, 0);
    mainLayout->addWidget(changeSignButton, 5, 1);
    mainLayout->addWidget(equalSignButton, 5, 2, 1, 2);
    // set layout to the widget
    setLayout(mainLayout);
    setWindowTitle("Simple Calculator");

    // set initial state
    m_state = stateClear;

    // set initial value
    m_result = 0;
    m_operand = 0;
}

Widget::~Widget()
{
    delete mainLayout;
    mainLayout = nullptr;
    display = nullptr;
    for (int i=0; i<numDigitButtons; ++i)
        digitButtons[i] = nullptr;
}

template<typename PointerToMemberFunction>
Button *Widget::createButton(const QString &text, const PointerToMemberFunction &member)
{
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}

void Widget::clearCalculator() {
    // clear the states of all the private variables
    m_operand = 0.0;
    operand_stk.clear();
    operator_stk.clear();
    display->setText("0");
    m_state = stateClear;
}

void Widget::buttonClicked()
{
    Button *clickedButton = qobject_cast<Button*>(sender());
    display->setText(clickedButton->text());
    return;
}

void Widget::digitClicked() {
    Button *clickedButton;
    switch (m_state) {
    case stateClear:
        clickedButton = qobject_cast<Button*>(sender());
        m_operand = m_operand*10 + clickedButton->text().toDouble();
        display->setText(QString::number(m_operand));
        m_state = stateOperand;
        break;
    case stateOperand:
        clickedButton = qobject_cast<Button*>(sender());
        m_operand = m_operand*10 + clickedButton->text().toDouble();
        display->setText(QString::number(m_operand));
        break;
    case stateOperator:
        clickedButton = qobject_cast<Button*>(sender());
        m_operand = m_operand*10 + clickedButton->text().toDouble();
        display->setText(QString::number(m_operand));
        operator_stk.push(m_operator);
        m_state = stateOperand;
        break;
    case stateError:
        display->setText("error!");
        break;
    case stateOpenBracket:
        clickedButton = qobject_cast<Button*>(sender());
        m_operand = m_operand*10 + clickedButton->text().toDouble();
        display->setText(QString::number(m_operand));
        m_state = stateOperand;
        break;
    case stateCloseBracket:
        display->setText("error!");
        m_state = stateError;
        break;
    case stateChangeSign:
        display->setText("-X error!");
        m_state = stateError;
        break;
    }
    return;
}

void Widget::plusClicked() {
    switch (m_state) {
    case stateClear:
        // do nothing
        break;
    case stateOperand:
        operand_stk.push(m_operand);
        m_operand = 0.0;
        while (!operator_stk.empty() && (operator_stk.top() == Multiply || operator_stk.top() == Division)) {
            if (operator_stk.top() == Multiply) {
                if (operand_stk.size() < 2) {
                    display->setText("syntax error!");
                    m_state = stateError;
                    return;
                }
                double opd2 = operand_stk.top();
                operand_stk.pop();
                double opd1 = operand_stk.top();
                operand_stk.pop();
                operator_stk.pop();
                operand_stk.push(opd1 * opd2);
            } else {
                if (operand_stk.size() < 2) {
                    display->setText("syntax error!");
                    m_state = stateError;
                    return;
                }
                double opd2 = operand_stk.top();
                operand_stk.pop();
                double opd1 = operand_stk.top();
                operand_stk.pop();
                operator_stk.pop();
                if (opd1 == 0) {
                    display->setText("divided by zero error!");
                    // transit to error state
                    m_state = stateError;
                } else {
                    operand_stk.push(opd1 / opd2);
                }
            }
        }
        m_operator = Plus;
        m_state = stateOperator;
        break;
    case stateOperator:
        m_operator = Plus;
        break;
    case stateError:
        display->setText("error!");
        break;
    case stateOpenBracket:
        // transit to error state
        display->setText("+ syntax error!");
        m_state = stateError;
        break;
    case stateCloseBracket:
        m_operator = Plus;
        m_state = stateOperator;
        break;
    case stateChangeSign:
        operand_stk.push(m_operand);
        m_operand = 0.0;
        m_operator = Plus;
        m_state = stateOperator;
        break;
    }
    return;
}

void Widget::minusClick() {
    switch (m_state) {
    case stateClear:
        // do nothing
        break;
    case stateOperand:
        operand_stk.push(m_operand);
        m_operand = 0.0;
        while (!operator_stk.empty() && (operator_stk.top() == Multiply || operator_stk.top() == Division)) {
            if (operator_stk.top() == Multiply) {
                if (operand_stk.size() < 2) {
                    display->setText("syntax error!");
                    m_state = stateError;
                    return;
                }
                double opd2 = operand_stk.top();
                operand_stk.pop();
                double opd1 = operand_stk.top();
                operand_stk.pop();
                operator_stk.pop();
                operand_stk.push(opd1 * opd2);
            } else {
                if (operand_stk.size() < 2) {
                    display->setText("syntax error!");
                    m_state = stateError;
                    return;
                }
                double opd2 = operand_stk.top();
                operand_stk.pop();
                double opd1 = operand_stk.top();
                operand_stk.pop();
                operator_stk.pop();
                if (opd2 == 0) {
                    display->setText("divided by zero error!");
                    // transit to error state
                    m_state = stateError;
                } else {
                    operand_stk.push(opd1 / opd2);
                }
            }
        }
        m_operator = Minus;
        m_state = stateOperator;
        break;
    case stateOperator:
        m_operator = Minus;
        break;
    case stateError:
        display->setText("error!");
        break;
    case stateOpenBracket:
        // transit to error state
        display->setText("- syntax error!");
        m_state = stateError;
        break;
    case stateCloseBracket:
        m_operator = Minus;
        m_state = stateOperator;
        break;
    case stateChangeSign:
        operand_stk.push(m_operand);
        m_operand = 0.0;
        m_operator = Minus;
        m_state = stateOperator;
        break;
    }
    return;
}

void Widget::multiplyClicked() {
    switch (m_state) {
    case stateClear:
        // do nothing
        break;
    case stateOperand:
        operand_stk.push(m_operand);
        m_operand = 0.0;
        while (!operator_stk.empty() && (operator_stk.top() == Multiply || operator_stk.top() == Division)) {
            if (operator_stk.top() == Multiply) {
                if (operand_stk.size() < 2) {
                    display->setText("syntax error!");
                    m_state = stateError;
                    return;
                }
                double opd2 = operand_stk.top();
                operand_stk.pop();
                double opd1 = operand_stk.top();
                operand_stk.pop();
                operator_stk.pop();
                operand_stk.push(opd1 * opd2);
            } else {
                if (operand_stk.size() < 2) {
                    display->setText("syntax error!");
                    m_state = stateError;
                    return;
                }
                double opd2 = operand_stk.top();
                operand_stk.pop();
                double opd1 = operand_stk.top();
                operand_stk.pop();
                operator_stk.pop();
                if (opd1 == 0) {
                    display->setText("divided by zero error!");
                    // transit to error state
                    m_state = stateError;
                } else {
                    operand_stk.push(opd1 / opd2);
                }
            }
        }
        m_operator = Multiply;
        m_state = stateOperator;
        break;
    case stateOperator:
        m_operator = Multiply;
        break;
    case stateError:
        display->setText("error!");
        break;
    case stateOpenBracket:
        // transit to error state
        display->setText("* syntax error!");
        m_state = stateError;
        break;
    case stateCloseBracket:
        m_operator = Multiply;
        m_state = stateOperator;
        break;
    case stateChangeSign:
        operand_stk.push(m_operand);
        m_operand = 0.0;
        m_operator = Multiply;
        m_state = stateOperator;
        break;
    }
    return;
}

void Widget::divisionClicked() {
    switch (m_state) {
    case stateClear:
        // do nothing
        break;
    case stateOperand:
        operand_stk.push(m_operand);
        m_operand = 0.0;
        while (!operator_stk.empty() && (operator_stk.top() == Multiply || operator_stk.top() == Division)) {
            if (operator_stk.top() == Multiply) {
                if (operand_stk.size() < 2) {
                    display->setText("syntax error!");
                    m_state = stateError;
                    return;
                }
                double opd2 = operand_stk.top();
                operand_stk.pop();
                double opd1 = operand_stk.top();
                operand_stk.pop();
                operator_stk.pop();
                operand_stk.push(opd1 * opd2);
            } else {
                if (operand_stk.size() < 2) {
                    display->setText("syntax error!");
                    m_state = stateError;
                    return;
                }
                double opd2 = operand_stk.top();
                operand_stk.pop();
                double opd1 = operand_stk.top();
                operand_stk.pop();
                operator_stk.pop();
                if (opd1 == 0) {
                    display->setText("divided by zero error!");
                    // transit to error state
                    m_state = stateError;
                } else {
                    operand_stk.push(opd1 / opd2);
                }
            }
        }
        m_operator = Division;
        m_state = stateOperator;
        break;
    case stateOperator:
        m_operator = Division;
        break;
    case stateError:
        display->setText("error!");
        break;
    case stateOpenBracket:
        // transit to error state
        display->setText("/ syntax error!");
        m_state = stateError;
        break;
    case stateCloseBracket:
        m_operator = Division;
        m_state = stateOperator;
        break;
    case stateChangeSign:
        operand_stk.push(m_operand);
        m_operand = 0.0;
        m_operator = Division;
        m_state = stateOperator;
        break;
    }
    return;
}

void Widget::openBracketClicked() {
    switch (m_state) {
    case stateClear:
        operator_stk.push(OpenBracket);
        m_state = stateOpenBracket;
        break;
    case stateOperand:
        // transit to error state
        display->setText(" ( syntax error!");
        m_state = stateError;
        break;
    case stateOperator:
        operator_stk.push(m_operator);
        operator_stk.push(OpenBracket);
        m_state = stateOpenBracket;
        break;
    case stateError:
        display->setText("error!");
        break;
    case stateOpenBracket:
        operator_stk.push(OpenBracket);
        break;
    case stateCloseBracket:
        display->setText("error!");
        m_state = stateError;
        break;
    case stateChangeSign:
        display->setText("( error!");
        m_state = stateError;
        break;
    }
    return;
}

void Widget::closeBracketClicked() {
    switch (m_state) {
    case stateClear:
        // do nothing
        break;
    case stateOperand:
        operand_stk.push(m_operand);
        m_operand = 0.0;
        while (!operator_stk.empty() && operator_stk.top() != OpenBracket) {
            if (operand_stk.size() < 2) {
                display->setText("syntax error!");
                m_state = stateError;
                return;
            }
            // pop out one operator and two operands and process
            double opd2 = operand_stk.top();
            operand_stk.pop();
            double opd1 = operand_stk.top();
            operand_stk.pop();
            switch (operator_stk.top()) {
            case Plus:
                operand_stk.push(opd1 + opd2);
                break;
            case Minus:
                operand_stk.push(opd1 - opd2);
                break;
            case Multiply:
                operand_stk.push(opd1 * opd2);
                break;
            case Division:
                if (opd2 == 0) {
                    display->setText("divided by zero error!");
                    m_state = stateError;
                    return;
                } else
                    operand_stk.push(opd1 / opd2);
                break;
            }
            operator_stk.pop();
        }
        if (!operator_stk.empty() && operator_stk.top() == OpenBracket)
            operator_stk.pop();
        m_state = stateCloseBracket;
        break;
    case stateOperator:
        m_state = stateError;
        break;
    case stateError:
        display->setText("error!");
        break;
    case stateOpenBracket:
        // transit to error state
        display->setText(") syntax error!");
        m_state = stateError;
        break;
    case stateCloseBracket:
        while (!operator_stk.empty() && operator_stk.top() != OpenBracket) {
            if (operand_stk.size() < 2) {
                display->setText("syntax error!");
                m_state = stateError;
                return;
            }
            // pop out one operator and two operands and process
            double opd2 = operand_stk.top();
            operand_stk.pop();
            double opd1 = operand_stk.top();
            operand_stk.pop();
            if (operator_stk.top() == Plus)
                operand_stk.push(opd1 + opd2);
            else
                operand_stk.push(opd1 - opd2);
            operator_stk.pop();
        }
        operator_stk.pop();
        break;
    case stateChangeSign:
        operand_stk.push(m_operand);
        while (!operator_stk.empty() && operator_stk.top() != OpenBracket) {
            if (operand_stk.size() < 2) {
                display->setText("syntax error!");
                m_state = stateError;
                return;
            }
            // pop out one operator and two operands and process
            double opd2 = operand_stk.top();
            operand_stk.pop();
            double opd1 = operand_stk.top();
            operand_stk.pop();
            if (operator_stk.top() == Plus)
                operand_stk.push(opd1 + opd2);
            else
                operand_stk.push(opd1 - opd2);
            operator_stk.pop();
        }
        operator_stk.pop();
        m_state = stateCloseBracket;
        break;
    }
    return;
}

void Widget::changeSignClicked() {
    switch (m_state) {
    case stateClear:
        // do nothing
        break;
    case stateOperand:
        m_operand = -1 * m_operand;
        m_state = stateChangeSign;
        break;
    case stateOperator:
        // change the sign of the top of the operand_stk
        if (!operand_stk.empty()) {
            double temp = operand_stk.top();
            operand_stk.pop();
            operand_stk.push(-1 * temp);
        }
        break;
    case stateError:
        display->setText("error!");
        break;
    case stateOpenBracket:
        // transit to error state
        display->setText("-X syntax error!");
        m_state = stateError;
        break;
    case stateCloseBracket:
        display->setText("error!");
        m_state = stateError;
        break;
    case stateChangeSign:
        m_operand = -1 * m_operand;
        break;
    }
    return;
}

void Widget::clearClicked() {
    switch (m_state) {
    case stateClear:
        // do nothing
        break;
    case stateOperand:
        clearCalculator();
        break;
    case stateOperator:
        clearCalculator();
        break;
    case stateError:
        clearCalculator();
        break;
    case stateOpenBracket:
        clearCalculator();
        break;
    case stateCloseBracket:
        clearCalculator();
        break;
    case stateChangeSign:
        clearCalculator();
        break;
    }
    return;
}

void Widget::equalClicked() {
    switch (m_state) {
    case stateClear:
        // do nothing
        break;
    case stateOperand:
        operand_stk.push(m_operand);
        m_operand = 0.0;
        while (!operator_stk.empty()) {
            if (operand_stk.size() < 2) {
                display->setText("syntax error!");
                m_state = stateError;
                return;
            }
            double opd2 = operand_stk.top();
            operand_stk.pop();
            double opd1 = operand_stk.top();
            operand_stk.pop();
            operationType opr = operator_stk.top();
            operator_stk.pop();
            switch (opr) {
            case Plus:
                operand_stk.push(opd1 + opd2);
                break;
            case Minus:
                operand_stk.push(opd1 - opd2);
                break;
            case Multiply:
                operand_stk.push(opd1 * opd2);
                break;
            case Division:
                if (opd2 == 0) {
                    display->setText("divided by zero error!");
                    m_state = stateError;
                    return;
                } else
                    operand_stk.push(opd1 / opd2);
            }
        }
        m_result = operand_stk.top();
        display->setText(QString::number(m_result));
        m_result = 0.0;
        m_operand = 0.0;
        m_state = stateOperator;
        break;
    case stateOperator:
        m_state = stateError;
        break;
    case stateError:
        display->setText("error!");
        break;
    case stateOpenBracket:
        // transit to error state
        display->setText("= syntax error!");
        m_state = stateError;
        break;
    case stateCloseBracket:
        while (!operator_stk.empty()) {
            if (operand_stk.size() < 2) {
                display->setText("syntax error!");
                m_state = stateError;
                return;
            }
            double opd2 = operand_stk.top();
            operand_stk.pop();
            double opd1 = operand_stk.top();
            operand_stk.pop();
            operationType opr = operator_stk.top();
            operator_stk.pop();
            switch (opr) {
            case Plus:
                operand_stk.push(opd1 + opd2);
                break;
            case Minus:
                operand_stk.push(opd1 - opd2);
                break;
            }
        }
        m_result = operand_stk.top();
        display->setText(QString::number(m_result));
        m_result = 0.0;
        m_operand = 0.0;
        m_state = stateOperator;
        break;
    case stateChangeSign:
        operand_stk.push(m_operand);
        while (!operator_stk.empty()) {
            if (operand_stk.size() < 2) {
                display->setText("syntax error!");
                m_state = stateError;
                return;
            }
            double opd2 = operand_stk.top();
            operand_stk.pop();
            double opd1 = operand_stk.top();
            operand_stk.pop();
            operationType opr = operator_stk.top();
            operator_stk.pop();
            switch (opr) {
            case Plus:
                operand_stk.push(opd1 + opd2);
                break;
            case Minus:
                operand_stk.push(opd1 - opd2);
                break;
            }
        }
        m_result = operand_stk.top();
        display->setText(QString::number(m_result));
        m_result = 0.0;
        m_operand = 0.0;
        m_state = stateOperator;
        break;
    }
    return;
}

