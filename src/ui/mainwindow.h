/*
 * LibreTuner
 * Copyright (C) 2018 Altenius
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QComboBox>
#include <QLayout>
#include <QMainWindow>
#include <QPointer>

#include <filesystem>
#include <unordered_map>

#include "database/links.h"
#include "datalinkswidget.h"
#include "models/tablemodel.h"
#include "ui/windows/diagnosticswidget.h"

class QListView;
class QMdiArea;

class EditorWidget;
class TablesWidget;
class TuneData;
class SidebarWidget;
class GraphWidget;
class DefinitionsWindow;
class ExplorerWidget;
class VehicleInformationWidget;

namespace lt
{
class Tune;
using TunePtr = std::shared_ptr<Tune>;
struct TableDefinition;
} // namespace lt

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = 0);

    // If newPath is true OR the current tune was not loaded from a file, asks
    // the user for a path.
    void saveTune(bool newPath = false);

    // Add path to recent projects. Ensures each path is unique
    void addRecent(const QString & path);

public slots:
    void setTable(const lt::TableDefinition * modTable);
    void openCreateTune();

private slots:
    void on_buttonDownloadRom_clicked();
    void newLogClicked();
    void closeEvent(QCloseEvent * event) override;
    void newProject();
    void openProject();
    void openTune(const lt::TunePtr & tune);

signals:
    void tuneChanged(const lt::Tune * tune);

private:
    bool checkSave();

    void addToRecentMenu(const QString & path);

    QComboBox * comboLogVehicles_;
    QComboBox * comboDatalink_;
    QListView * listLogs_;
    SidebarWidget * sidebar_;
    QMenu * recentMenu_;

    TablesWidget * tables_;
    ExplorerWidget * explorer_;

    QAction * flashCurrentAction_;
    QAction * saveCurrentAction_;

    // Docks
    QDockWidget * logDock_;
    QDockWidget * overviewDock_;
    QDockWidget * loggingDock_;
    QDockWidget * sidebarDock_;
    QDockWidget * tablesDock_;
    QDockWidget * editorDock_;
    QDockWidget * graphDock_;
    QDockWidget * explorerDock_;

    void setupMenu();
    void setupStatusBar();

    void hideAllDocks();
    void restoreDocks();

    void saveSettings();
    void loadSettings();

    void setTune(const lt::TunePtr & tune);

    QDockWidget * createOverviewDock();
    QDockWidget * createLoggingDock();
    QDockWidget * createLogDock();
    QDockWidget * createSidebarDock();
    QDockWidget * createTablesDock();
    QDockWidget * createExplorerDock();

    std::vector<QDockWidget *> docks_;

    lt::TunePtr tune_;

    LinksListModel linksList_;

    DatalinksWidget datalinksWindow_;
    DiagnosticsWidget diagnosticsWindow_;

    QPointer<DefinitionsWindow> definitionsWindow_;
    VehicleInformationWidget * infoWidget_{nullptr};

    QStringList recentProjects_;

    std::unordered_map<std::string, QPointer<QWidget>> views_;
};

#endif // MAINWINDOW_H
