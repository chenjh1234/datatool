/********************************************************************************
** Form generated from reading UI file 'options.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_DialogOption
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEditTapeBlock;
    QCheckBox *checkBoxCopyBar;
    QCheckBox *checkBoxCopyPrompt;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogOption)
    {
        if (DialogOption->objectName().isEmpty())
            DialogOption->setObjectName(QStringLiteral("DialogOption"));
        DialogOption->resize(400, 199);
        gridLayout = new QGridLayout(DialogOption);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(DialogOption);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEditTapeBlock = new QLineEdit(DialogOption);
        lineEditTapeBlock->setObjectName(QStringLiteral("lineEditTapeBlock"));

        gridLayout->addWidget(lineEditTapeBlock, 0, 1, 1, 1);

        checkBoxCopyBar = new QCheckBox(DialogOption);
        checkBoxCopyBar->setObjectName(QStringLiteral("checkBoxCopyBar"));

        gridLayout->addWidget(checkBoxCopyBar, 1, 0, 1, 2);

        checkBoxCopyPrompt = new QCheckBox(DialogOption);
        checkBoxCopyPrompt->setObjectName(QStringLiteral("checkBoxCopyPrompt"));
        checkBoxCopyPrompt->setChecked(true);

        gridLayout->addWidget(checkBoxCopyPrompt, 2, 0, 1, 2);

        buttonBox = new QDialogButtonBox(DialogOption);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 2);

        checkBoxCopyBar->raise();
        buttonBox->raise();
        lineEditTapeBlock->raise();
        label->raise();
        checkBoxCopyPrompt->raise();

        retranslateUi(DialogOption);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogOption, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogOption, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogOption);
    } // setupUi

    void retranslateUi(QDialog *DialogOption)
    {
        DialogOption->setWindowTitle(QApplication::translate("DialogOption", "Options", 0));
        label->setText(QApplication::translate("DialogOption", "Tape Block", 0));
        lineEditTapeBlock->setText(QApplication::translate("DialogOption", "256000", 0));
        checkBoxCopyBar->setText(QApplication::translate("DialogOption", "Is enable copyToolBar", 0));
        checkBoxCopyPrompt->setText(QApplication::translate("DialogOption", "Is copy prompt", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogOption: public Ui_DialogOption {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
