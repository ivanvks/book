#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QStandardItemModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setTreeView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTreeView()
{
    QList < QStandardItem * > itemList;

    for ( int i = 0; i < 10 ; ++ i ) {
        QStandardItem * item = new QStandardItem( QString( "item %1" ).arg( i ) );
        int kod = 100;
        item->setData( kod + i, RoleKod );
        item->setData( ( kod + i ) - 1, RoleParent );
        itemList.append( item );
        qDebug() << __PRETTY_FUNCTION__
                 << item->data( Qt::DisplayRole ) << item->data( RoleKod ) << item->data( RoleParent );
    }

    QStandardItemModel * model = new QStandardItemModel();

    foreach ( QStandardItem * parItem, itemList ) {
        foreach ( QStandardItem * item, itemList )
            if ( parItem->data( RoleKod ) == item->data( RoleParent ) ) parItem->appendRow( item );
        if ( parItem->data( RoleParent ) == 99 ) model->invisibleRootItem()->appendRow( parItem );
    }

    ui->treeView->setModel( model );
}
