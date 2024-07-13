#include "widget.h"

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
        digitButtons[i] = createButton(QString::number(i), &Widget::buttonClicked);

    // intitialize the operator buttons
    Button *plusButton = createButton(tr("+"), &Widget::buttonClicked);
    Button *minusButton = createButton(tr("-"), &Widget::buttonClicked);
    Button *multiplyButton = createButton(tr("*"), &Widget::buttonClicked);
    Button *divisionButton = createButton(tr("/"), &Widget::buttonClicked);

    // initialize the bracket buttons
    Button *openBracketButton = createButton(tr("("), &Widget::buttonClicked);
    Button *closeBracketButton = createButton(tr(")"), &Widget::buttonClicked);

    // initialize other function buttons
    Button *clearButton = createButton(tr("C"), &Widget::buttonClicked);
    Button *changeSignButton = createButton(tr("-X"), &Widget::buttonClicked);
    Button *equalSignButton = createButton(tr("="), &Widget::buttonClicked);

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

void Widget::buttonClicked()
{
    Button *clickedButton = qobject_cast<Button*>(sender());
    display->setText(clickedButton->text());
    return;
}

