#include "tablewindow.h"



TableWindow::TableWindow(QWidget *parent) : QWidget(parent)
{
    tableWidget = new QTableWidget(this); // Replace with your actual content widget

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);
    setLayout(layout);
}

void TableWindow::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
}

QTextDocument* TableWindow::toQTextDocument(){
    QTextDocument* document = new QTextDocument();

    QTextCursor cursor(document);
    QTextCharFormat yTextFormat = QTextCharFormat();
    yTextFormat.setBackground(QBrush(Qt::gray));
    int cellsPerLine = 10;

    int rowCount = tableWidget->columnCount() / cellsPerLine;
    if (tableWidget->columnCount() % cellsPerLine != 0){
        rowCount+=1;
    }
    rowCount *= 2;
    QTextTable *table = cursor.insertTable(rowCount, cellsPerLine);

    cursor.movePosition(QTextCursor::Start);
    cursor.insertText("Sample Text");

    qDebug() << document->pageSize().width();
    qDebug() << document->documentMargin();

    int flatI = 0;
    for (int i = 0; i < rowCount; i+=2){
        int k = 0;
        while (k < cellsPerLine && flatI < tableWidget->columnCount()){

            const QTableWidgetItem* itemX = tableWidget->item(0, flatI);
            QString data = itemX ? itemX->text() : "";
            auto tableCell = table->cellAt(i, k);
            cursor = tableCell.firstCursorPosition();
            tableCell.setFormat(yTextFormat);
            cursor.insertText(data);

            const QTableWidgetItem* itemY = tableWidget->item(1, flatI);
            data = itemY ? itemY->text() : "";
            if (data == "nan"){
                data = "?";
            }

            tableCell = table->cellAt(i+1, k);
            cursor = tableCell.firstCursorPosition();
            cursor.insertText(data);

            flatI++;
            k++;

        }
    }


    // // Iterate through table data
    // for (int row = 0; row < tableWidget->rowCount(); ++row) {
    //     for (int col = 0; col < tableWidget->columnCount(); ++col) {
    //         const QTableWidgetItem* item = tableWidget->item(row, col);
    //         QString data = item ? item->text() : "";

    //         auto tableCell = table->cellAt(row, col);
    //         cursor = tableCell.firstCursorPosition();
    //         // Add data to QTextDocument
    //         cursor.insertText(data);
    //         // cursor.insertText("  "); // Add space between cells (optional)
    //     }
    //     // cursor.insertBlock(); // Add newline after each row
    // }

    // (Optional) Add table headers
    // for (int col = 0; col < tableWidget->columnCount(); ++col) {
    //     QString headerText = tableWidget->horizontalHeaderItem(col)->text();
    //     cursor.insertText("\n**" + headerText + "**  "); // Bold headers with spaces
    // }

    return document;
}

int estimateRowsNumber(int numOfValues, int cellPerLine){
    int rows = numOfValues / cellPerLine;
    if (numOfValues % cellPerLine != 0){
        rows+=1;
    }
    return rows * 2;
}

// int estimateCellsPerLine(const QTextTable* table, const QTextDocument* document) {
//     QFontMetrics metrics(document->defaultFont());
//     int availableWidth = document->pageSize().width() - document->documentMargin();  // Adjust margins as needed

//     int accumulatedWidth = 0;
//     int cellsPerLine = 0;

//     for (int col = 0; col < table->columns(); ++col) {
//         QString cellText = table->cellAt(0, col)->text();  // Access first row for estimation
//         int cellWidth = metrics.horizontalAdvance();
//         accumulatedWidth += cellWidth;

//         if (accumulatedWidth > availableWidth) {
//             break;
//         }
//         cellsPerLine++;
//     }

//     return cellsPerLine;
// }

// void TableWindow::toQTextDocument(){
//     QTextDocument *doc = new QTextDocument;
//     QTextTableFormat tableFormat = QTextTableFormat();
//     QTextCursor cursor = QTextCursor(doc);
//     QTextCharFormat boldFormat = QTextCharFormat();
//     QTextCharFormat textFormat = QTextCharFormat();
//     QTextCharFormat alternateCellFormat = QTextCharFormat();
//     boldFormat.setFontWeight(400);
//     doc->setDocumentMargin(10);
//     cursor.movePosition(QTextCursor::Start);

//     QTextTable *table = cursor.insertTable(tableWidget->rowCount() + 1, tableWidget->columnCount(), tableFormat);
//     QTextTableCell headerCell = table->cellAt(0, 0);
//     QTextCursor headerCellCursor = headerCell.firstCursorPosition();
//     headerCellCursor.insertText(QObject::tr("Name"), boldFormat);
//     headerCell = table->cellAt(0, 1);
//     headerCellCursor = headerCell.firstCursorPosition();
//     headerCellCursor.insertText(QObject::tr("Value"), boldFormat);

//     tableWidget->size();


//     for(int i = 0; i < properties.size(); i++){
//         // QTextCharFormat cellFormat = i % 2 == 0 ? textFormat : alternateCellFormat;
//         QTextCharFormat cellFormat =  textFormat;
//         QTextTableCell cell = table->cellAt(i + 1, 0);
//         cell.setFormat(cellFormat);
//         QTextCursor cellCursor = cell.firstCursorPosition();
//         cellCursor.insertText(properties.at(i)->name());

//         cell = table->cellAt(i + 1, 1);
//         cell.setFormat(cellFormat);
//         cellCursor = cell.firstCursorPosition();
//         cellCursor.insertText(properties.at(i)->value().toString() + " " + properties.at(i)->unit());
//     }

//     cursor.movePosition(QTextCursor::End);
//     cursor.insertBlock();

//     //Print to PDF
//     QPrinter printer(QPrinter::HighResolution);
//     printer.setOutputFormat(QPrinter::PdfFormat);
//     printer.setOutputFileName(filename);
//     doc->print(&printer);
// }

void TableWindow::setData(QVector<Point> points){

    tableWidget->clear();
    tableWidget->setRowCount(2);
    tableWidget->setColumnCount(points.size());
    int i = 0;
    foreach(Point p, points){
        tableWidget->setItem(0, i, new QTableWidgetItem(QString::number(p.getX())));
        tableWidget->setItem(1, i, new QTableWidgetItem(QString::number(p.getY())));
        i++;
    }

    update();

}
