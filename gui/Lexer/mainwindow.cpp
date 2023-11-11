#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "src/dfa.cpp"
#include "src/nfa.cpp"
#include "src/regExp.cpp"
#include "util.h"
#include "src/generateLexer.cpp"
#include <QTableView>
#include <QStandardItemModel>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), regexString("") {
    ui->setupUi(this);
    ui->table->setShowGrid(true);
    ui->table->setGridStyle(Qt::SolidLine);
    ui->table->setSortingEnabled(true);
    this->regexIndex = 0;
    this->regexString = "";
    ui->regText->setPlainText("");
    ui->spinBox->setValue(0);
    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(0);
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::checkEmptyRegex() {
    return this->regexString == "";
}

void MainWindow::on_regApplyB_clicked() {
    this->regexString = ui->regExpInput->toPlainText();
    this->regexVector.clear();
    std::string s = "", singleReg = "";
    if (this->regexString.toStdString().empty()) {
        ui->spinBox->setValue(0);
        ui->spinBox->setMinimum(0);
        ui->spinBox->setMaximum(0);
        return;
    }
    singleReg += "(";
    for (auto c: this->regexString.toStdString()) {
        if (c != '\n') {
            s += c;
            singleReg += c;
        } else {
            this->regexVector.push_back(s);
            s.clear();
            singleReg += ")|(";
        }
    }
    this->regexVector.push_back(s);
    singleReg += ")";
    this->singleReg = QString::fromStdString(singleReg);
    if (ui->checkALL->isChecked()) {
        ui->regText->setPlainText(this->singleReg);
    } else {
        ui->regText->setPlainText(QString::fromStdString(this->regexVector[this->regexIndex]));
    }
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(this->regexVector.size());
    ui->spinBox->setValue(1);
}

void displayNFAInTableView(const std::shared_ptr<NFA> &nfa, QTableView *tableView) {
    int rowCount = nfa->states.size();
    int columnCount = nfa->symbols.size() + 3;  // 1 for state id, 1 for start, 1 for final state

    // Create a standard item model
    QStandardItemModel *model = new QStandardItemModel(rowCount, columnCount, tableView);

    // Set header data
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("State ID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Start")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Final")));

    int column = 3;
    for (char symbol: nfa->symbols) {
        if (symbol == 0) {
            model->setHorizontalHeaderItem(column++, new QStandardItem(QString("ε")));
            continue;
        }
        model->setHorizontalHeaderItem(column++, new QStandardItem(QString(symbol)));
    }

    int row = 0;
    for (const auto &state: nfa->states) {
        // Set state ID
        model->setItem(row, 0, new QStandardItem(QString::number(state->id)));

        // Set start state
        model->setItem(row, 1, new QStandardItem(state == nfa->start_state ? "Yes" : ""));
        // Set final state
        model->setItem(row, 2, new QStandardItem(state->is_final ? "Yes" : ""));

        // Set transition symbols
        column = 3;
        for (char symbol: nfa->symbols) {
            std::string transitions;
            for (const auto &nextState: state->transitions[symbol]) {
                transitions += std::to_string(nextState->id) + ",";
            }
            transitions = transitions.empty() ? "-" : transitions.substr(0, transitions.size() - 1);
            model->setItem(row, column++, new QStandardItem(QString(transitions.c_str())));
        }
        row++;
    }

    // Set the model to the table view
    tableView->setModel(model);
}


void displayDFAInTableView(const std::shared_ptr<DFA> &dfa, QTableView *tableView) {
    int rowCount = dfa->dfa_states.size();
    int columnCount = dfa->symbols.size() + 3;  // 1 for state id, 1 for start, 1 for final state

    // Create a standard item model
    QStandardItemModel *model = new QStandardItemModel(rowCount, columnCount, tableView);

    // Set header data
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("State ID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Start")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Final")));

    int column = 3;
    for (char symbol: dfa->symbols) {
        model->setHorizontalHeaderItem(column++, new QStandardItem(QString(symbol)));
    }

    int row = 0;
    for (const auto &state: dfa->dfa_states) {
        if (state == nullptr)
            continue;
        // Set state ID
        model->setItem(row, 0, new QStandardItem(QString::number(state->id)));

        // Set start state
        model->setItem(row, 1, new QStandardItem(state == dfa->start_state ? "Yes" : ""));
        // Set final state
        model->setItem(row, 2, new QStandardItem(state->is_final ? "Yes" : ""));

        // Set transition symbols
        column = 3;
        for (char symbol: dfa->symbols) {
            if (symbol == 0) {
                model->setHorizontalHeaderItem(column++, new QStandardItem(QString("ε")));
                    continue;
            }
//            if (symbol == 0) {
//                model->setItem(row, column++, new QStandardItem(""));  // Empty cell for ε transitions
//                continue;
//            }

            auto transition = state->transitions.find(symbol);
            std::string transitions;
            if (transition != state->transitions.end() && transition->second != nullptr) {
                    transitions += std::to_string(transition->second->id);
            } else {
                transitions = "-";
            }
            model->setItem(row, column++, new QStandardItem(QString(transitions.c_str())));
        }
        row++;
    }

    // Set the model to the table view
    tableView->setModel(model);
}


void MainWindow::on_pushB1_clicked() {
    if (this->checkEmptyRegex()) {
        return;
    }
    std::string s = "";
    if (ui->checkALL->isChecked()) {
        s = this->singleReg.toStdString();
    } else {
        s = this->regexVector[this->regexIndex];
    }
    flush();
    auto nfaConvert = stringToRegExp(s)->toNFA();
    const auto &nfa = nfaConvert;
    displayNFAInTableView(nfa, ui->table);
}


void MainWindow::on_pushB2_clicked() {
    if (this->checkEmptyRegex()) {
        return;
    }
    std::string s = "";
    if (ui->checkALL->isChecked()) {
        s = this->singleReg.toStdString();
    } else {
        s = this->regexVector[this->regexIndex];
    }
    flush();
    auto nfaConvert = stringToRegExp(s)->toNFA();
    const auto &nfa = nfaConvert;
    // Convert NFA to DFA
    flush();
    auto dfa = convertToDFA(nfa);
    displayDFAInTableView(dfa, ui->table);
}


void MainWindow::on_pushB3_clicked() {
    if (this->checkEmptyRegex()) {
        return;
    }
    std::string s = "";
    if (ui->checkALL->isChecked()) {
        s = this->singleReg.toStdString();
    } else {
        s = this->regexVector[this->regexIndex];
    }
    flush();
    auto nfaConvert = stringToRegExp(s)->toNFA();
    const auto &nfa = nfaConvert;
    // Convert NFA to DFA
    auto dfa = convertToDFA(nfa);
    flush();
    auto new_dfa = dfa->minimizeDFA();
    displayDFAInTableView(new_dfa, ui->table);
}


void MainWindow::on_pushB4_clicked() {
    if (this->checkEmptyRegex()) {
        return;
    }
    std::string s = "";
    if (ui->checkALL->isChecked()) {
        s = this->singleReg.toStdString();
    } else {
        s = this->regexVector[this->regexIndex];
    }
    flush();
    auto nfaConvert = stringToRegExp(s)->toNFA();
    const auto &nfa = nfaConvert;
    // Convert NFA to DFA
    flush();
    auto dfa = convertToDFA(nfa);
    flush();
    auto new_dfa = dfa->minimizeDFA();

    auto fileCode = generateLexer(new_dfa);
    generateLexerToFile(new_dfa, "hello.cpp");
    ui->textBrowser->setText(QString::fromStdString(fileCode));
}


void MainWindow::on_openB_clicked() {
    QString selectedFilePath = QFileDialog::getOpenFileName(this, "Open a file", "", "All Files (*.*)");
    if (selectedFilePath.isEmpty()) {
        return;
    }
    QFile file(selectedFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    file.close();
    ui->regExpInput->clear();
    ui->regExpInput->setPlainText(text);
}


void MainWindow::on_saveB_clicked() {
    QString selectedFilePath = QFileDialog::getSaveFileName(this, "Save a file", "", "All Files (*.*)");
    if (selectedFilePath.isEmpty()) {
        return;
    }

    QFile file(selectedFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << ui->regExpInput->toPlainText();
    file.close();
}


void MainWindow::on_spinBox_valueChanged(int arg1) {
    this->regexIndex = arg1 - 1;
    if (ui->checkALL->isChecked()) {
        ui->regText->setPlainText(this->singleReg);
    } else {
        ui->regText->setPlainText(QString::fromStdString(this->regexVector[this->regexIndex]));
    }
}


void MainWindow::on_codeGenerate_clicked() {
    QString selectedFilePath = QFileDialog::getSaveFileName(this, "Save a file", "", "All Files (*.*)");
    if (selectedFilePath.isEmpty()) {
        return;
    }

    QFile file(selectedFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    if (this->checkEmptyRegex()) {
        return;
    }

    std::string s = "";
    if (ui->checkALL->isChecked()) {
        s = this->singleReg.toStdString();
    } else {
        s = this->regexVector[this->regexIndex];
    }
    flush();
    auto nfaConvert = stringToRegExp(s)->toNFA();
    const auto &nfa = nfaConvert;
    // Convert NFA to DFA
    flush();
    auto dfa = convertToDFA(nfa);
    flush();
    auto new_dfa = dfa->minimizeDFA();

    auto fileCode = generateLexer(new_dfa);
    ui->textBrowser->setText(QString::fromStdString(fileCode));

    QTextStream out(&file);
    out << QString::fromStdString(fileCode);
    file.close();
}

