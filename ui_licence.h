/********************************************************************************
** Form generated from reading UI file 'licence.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LICENCE_H
#define UI_LICENCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Licence
{
public:
    QDialogButtonBox *buttonBox;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *Licence)
    {
        if (Licence->objectName().isEmpty())
            Licence->setObjectName(QString::fromUtf8("Licence"));
        Licence->resize(342, 380);
        buttonBox = new QDialogButtonBox(Licence);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 330, 301, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        textBrowser = new QTextBrowser(Licence);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 321, 311));

        retranslateUi(Licence);
        QObject::connect(buttonBox, SIGNAL(accepted()), Licence, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Licence, SLOT(reject()));

        QMetaObject::connectSlotsByName(Licence);
    } // setupUi

    void retranslateUi(QDialog *Licence)
    {
        Licence->setWindowTitle(QCoreApplication::translate("Licence", "Dialog", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("Licence", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Noto Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">NordVPN Front is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">NordVPN Front  is distributed in the"
                        " hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">You should have received a copy of the GNU General Public License along with GIMP. If not, see: https://www.gnu.org/licenses/</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Licence: public Ui_Licence {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LICENCE_H
