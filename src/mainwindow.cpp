/*
 * TwistLoad - a Simple Download Manager
 * Copyright (C) 2014  Nathan Osman
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QSize>

#include "dialogs/aboutdialog.h"
#include "dialogs/adddownloaddialog.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupTable();
    setupToolbar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAboutDialog()
{
    AboutDialog(this).exec();
}

void MainWindow::showAddDownloadDialog()
{
    AddDownloadDialog().exec();
}

void MainWindow::setupTable()
{
    ui->downloads->setModel(&model);
    ui->downloads->setColumnWidth(0, 48);
    ui->downloads->setColumnWidth(1, 350);
}

void MainWindow::setupToolbar()
{
    ui->toolBar->setIconSize(QSize(24, 24));

    ui->toolBar->addAction(QIcon::fromTheme("list-add"),
                           tr("Add Download"),
                           this,
                           SLOT(showAddDownloadDialog()));
}
