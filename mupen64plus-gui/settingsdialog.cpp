#include "settingsdialog.h"
#include "mainwindow.h"
#include "interface/core_commands.h"

#include <QPushButton>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>

void SettingsDialog::handleCoreButton()
{
    QString fileName = QFileDialog::getExistingDirectory(this,
        tr("Locate Core Library"), NULL, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!fileName.isNull()) {
        corePath->setText(fileName);
        w->getSettings()->setValue("coreLibPath", fileName);
    }
}

void SettingsDialog::handlePluginButton()
{
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Locate Plugin Directory"),
                                                         NULL,
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    if (!fileName.isNull()) {
        pluginPath->setText(fileName);
        w->getSettings()->setValue("pluginDirPath", fileName);
	
		w->getSettings()->remove("gfxPlugin");
		w->getSettings()->remove("audioPlugin");
		w->getSettings()->remove("inputPlugin");
		w->getSettings()->remove("rspPlugin");
        w->updatePlugins();
    }
}

void SettingsDialog::handleConfigButton()
{
    QString fileName = QFileDialog::getExistingDirectory(this, tr("Set Config Directory"),
                                                         NULL,
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
    if (!fileName.isNull()) {
        configPath->setText(fileName);
        w->getSettings()->setValue("configDirPath", fileName);
    }
}

void SettingsDialog::handleClearConfigButton()
{
    configPath->setText("");
    w->getSettings()->remove("configDirPath");
}

void SettingsDialog::handleCoreEdit()
{
    w->getSettings()->setValue("coreLibPath", corePath->text());
}

void SettingsDialog::handlePluginEdit()
{
    w->getSettings()->setValue("pluginDirPath", pluginPath->text());
	
	w->getSettings()->remove("gfxPlugin");
	w->getSettings()->remove("audioPlugin");
    w->getSettings()->remove("inputPlugin");
	w->getSettings()->remove("rspPlugin");
    w->updatePlugins();
}

void SettingsDialog::handleConfigEdit()
{
    w->getSettings()->setValue("configDirPath", configPath->text());
}

void SettingsDialog::initStuff()
{
    layout = new QGridLayout(this);

    QLabel *coreLabel = new QLabel("Core Library Path", this);
    corePath = new QLineEdit(this);
    corePath->setText(w->getSettings()->value("coreLibPath").toString());
    QPushButton *coreButton = new QPushButton("Set Path", this);
    connect(coreButton, SIGNAL (released()),this, SLOT (handleCoreButton()));
    connect(corePath, SIGNAL (editingFinished()),this, SLOT (handleCoreEdit()));
    corePath->setStyleSheet("border: 1px solid; padding: 10px");
    layout->addWidget(coreLabel,0,0);
    layout->addWidget(corePath,0,1);
    layout->addWidget(coreButton,0,2);

#ifdef CORE_LIBRARY_PATH
    corePath->setEnabled(false);
    coreButton->setEnabled(false);
#endif

    QLabel *pluginLabel = new QLabel("Plugin Dir Path", this);
    pluginPath = new QLineEdit(this);
    pluginPath->setText(w->getSettings()->value("pluginDirPath").toString());
    QPushButton *pluginButton = new QPushButton("Set Path", this);
    connect(pluginButton, SIGNAL (released()),this, SLOT (handlePluginButton()));
    connect(pluginPath, SIGNAL (editingFinished()),this, SLOT (handlePluginEdit()));
    pluginPath->setStyleSheet("border: 1px solid; padding: 10px");
    layout->addWidget(pluginLabel,1,0);
    layout->addWidget(pluginPath,1,1);
    layout->addWidget(pluginButton,1,2);

#ifdef PLUGIN_DIR_PATH
    pluginPath->setEnabled(false);
    pluginButton->setEnabled(false);
#endif

    QLabel *note = new QLabel("Note: If you change the Config Path, you need to close and re-open mupen64plus-gui before it will take effect.", this);
    QLabel *configLabel = new QLabel("Config Dir Path", this);
    configPath = new QLineEdit(this);
    configPath->setText(w->getSettings()->value("configDirPath").toString());
    QPushButton *configButton = new QPushButton("Set Path", this);
    connect(configButton, SIGNAL (released()),this, SLOT (handleConfigButton()));
    connect(configPath, SIGNAL (editingFinished()),this, SLOT (handleConfigEdit()));
    QPushButton *clearConfigButton = new QPushButton("Clear", this);
    connect(clearConfigButton, SIGNAL (released()),this, SLOT (handleClearConfigButton()));
    configPath->setStyleSheet("border: 1px solid; padding: 10px");
    layout->addWidget(note,2,0,1,-1);
    layout->addWidget(configLabel,3,0);
    layout->addWidget(configPath,3,1);
    layout->addWidget(configButton,3,2);
    layout->addWidget(clearConfigButton,3,3);

#ifdef CONFIG_DIR_PATH
    configPath->setEnabled(false);
    configButton->setEnabled(false);
    clearConfigButton->setEnabled(false);
#endif

    QString pluginPath = w->getSettings()->value("pluginDirPath").toString();
    pluginPath.replace("$APP_PATH$", QCoreApplication::applicationDirPath());
    QDir PluginDir(pluginPath);
    QStringList Filter;
    Filter.append("");
    QStringList current;
	
	QLabel *videoLabel = new QLabel("Video Plugin", this);
    layout->addWidget(videoLabel,5,0);
    QComboBox *videoChoice = new QComboBox(this);
    Filter.replace(0,"mupen64plus-video*");
    current = PluginDir.entryList(Filter);
    videoChoice->addItems(current);
    QString qtVideoPlugin = w->getSettings()->value("gfxPlugin").toString();
    int video_index = videoChoice->findText(qtVideoPlugin);
    if (video_index == -1) {
        videoChoice->addItem(qtVideoPlugin);
        video_index = videoChoice->findText(qtVideoPlugin);
    }
    videoChoice->setCurrentIndex(video_index);
    connect(videoChoice, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated),
        [=](const QString &text) {
            w->getSettings()->setValue("gfxPlugin", text);
            w->updatePlugins();
    });
    layout->addWidget(videoChoice,5,1);
	
	QLabel *audioLabel = new QLabel("Audio Plugin", this);
    layout->addWidget(audioLabel,6,0);
    QComboBox *audioChoice = new QComboBox(this);
    Filter.replace(0,"mupen64plus-audio*");
    current = PluginDir.entryList(Filter);
    audioChoice->addItems(current);
    QString qtAudioPlugin = w->getSettings()->value("audioPlugin").toString();
    int audio_index = audioChoice->findText(qtAudioPlugin);
    if (audio_index == -1) {
        audioChoice->addItem(qtAudioPlugin);
        audio_index = audioChoice->findText(qtAudioPlugin);
    }
    audioChoice->setCurrentIndex(audio_index);
    connect(audioChoice, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated),
        [=](const QString &text) {
            w->getSettings()->setValue("audioPlugin", text);
            w->updatePlugins();
    });
    layout->addWidget(audioChoice,6,1);
	
    QLabel *inputLabel = new QLabel("Input Plugin", this);
    layout->addWidget(inputLabel,7,0);
    QComboBox *inputChoice = new QComboBox(this);
    Filter.replace(0,"mupen64plus-input*");
    current = PluginDir.entryList(Filter);
    inputChoice->addItems(current);
    QString qtInputPlugin = w->getSettings()->value("inputPlugin").toString();
    int my_index = inputChoice->findText(qtInputPlugin);
    if (my_index == -1) {
        inputChoice->addItem(qtInputPlugin);
        my_index = inputChoice->findText(qtInputPlugin);
    }
    inputChoice->setCurrentIndex(my_index);
    connect(inputChoice, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated),
        [=](const QString &text) {
            w->getSettings()->setValue("inputPlugin", text);
            w->updatePlugins();
    });
    layout->addWidget(inputChoice,7,1);
	
	QLabel *rspLabel = new QLabel("RSP Plugin", this);
    layout->addWidget(rspLabel,8,0);
    QComboBox *rspChoice = new QComboBox(this);
    Filter.replace(0,"mupen64plus-rsp*");
    current = PluginDir.entryList(Filter);
    rspChoice->addItems(current);
    QString qtRSPPlugin = w->getSettings()->value("rspPlugin").toString();
    int rsp_index = rspChoice->findText(qtRSPPlugin);
    if (rsp_index == -1) {
        rspChoice->addItem(qtRSPPlugin);
        rsp_index = rspChoice->findText(qtRSPPlugin);
    }
    rspChoice->setCurrentIndex(rsp_index);
    connect(rspChoice, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated),
        [=](const QString &text) {
            w->getSettings()->setValue("rspPlugin", text);
            w->updatePlugins();
    });
    layout->addWidget(rspChoice,8,1);

    setLayout(layout);
}

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    initStuff();
}

void SettingsDialog::closeEvent(QCloseEvent *event)
{
    w->getSettings()->sync();
    int value;
    if (w->getCoreLib())
    {
        (*CoreDoCommand)(M64CMD_CORE_STATE_QUERY, M64CORE_EMU_STATE, &value);
        if (value == M64EMU_STOPPED)
            w->resetCore();
    }
    else
        w->resetCore();

    event->accept();
}
